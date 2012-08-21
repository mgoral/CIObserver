#include <cstddef>
#include <memory>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "Exceptions.hpp"
#include "JobFactory.hpp"
#include "JobManager.hpp"

#include "IJobFactoryMock.hpp"
#include "IJobMock.hpp"
#include "IConnectionFacadeMock.hpp"

using namespace testing;
using namespace ci;
using namespace ci::core;

class JobManagerTests : public Test {
protected:
    virtual void SetUp() {
        testJobFactory.reset(new IJobFactoryMock());
        connectionFacadeMock.reset(new IConnectionFacadeMock());
        url = "http://example.com";
        name = "FooManagerName";
    }

    std::shared_ptr<IJobFactoryMock> testJobFactory;
    std::shared_ptr<IConnectionFacadeMock> connectionFacadeMock;
    Url url;
    Name name;
};

TEST_F(JobManagerTests, CreatingWithDefauls) {
    JobManager manager(connectionFacadeMock, testJobFactory, url);

    ASSERT_EQ(url, manager.getUrl());
}

TEST_F(JobManagerTests, CreatingWithAGivenName) {
    JobManager manager(connectionFacadeMock, testJobFactory, url, name);

    ASSERT_EQ(url, manager.getUrl());
    ASSERT_EQ(name, manager.getName());
}

TEST_F(JobManagerTests, CreatingWithWrongURL) {
    Url wrongUrl = "WrongUrl";

    ASSERT_THROW(JobManager(connectionFacadeMock, testJobFactory, wrongUrl), bad_parameter);
}

TEST_F(JobManagerTests, CheckDefaultManagerSettings) {
    JobManager manager(connectionFacadeMock, testJobFactory, url);

    EXPECT_EQ(url, manager.getName());
    EXPECT_EQ(url, manager.getUrl());
    EXPECT_EQ(Description(), manager.getDescription());
}

TEST_F(JobManagerTests, SetDescription) {
    JobManager manager(connectionFacadeMock, testJobFactory, url);
    Description desc = "Job manager description containing strage Polish characters: ąuęśćź";

    manager.setDescription(desc);
    ASSERT_EQ(desc, manager.getDescription());
}

TEST_F(JobManagerTests, ChangeName) {
    JobManager manager(connectionFacadeMock, testJobFactory, url);
    Name name = "JobManager name";

    manager.setName(name);
    ASSERT_EQ(name, manager.getName());
}

TEST_F(JobManagerTests, GetNonExistingJob) {
    JobManager manager(connectionFacadeMock, testJobFactory, url);
    Url jobUrl = "http://example.com";

    EXPECT_CALL(*testJobFactory, createJob(jobUrl)).WillOnce(Return(new IJobMock()));

    ASSERT_EQ(IJobPtr(), manager.getJob(jobUrl));
}

TEST_F(JobManagerTests, AddJob) {
    // We cannot use mocks here because it would mean that through created constant objects we're indirectly controlling
    // tested methods behaviour
    JobManager::IJobFactoryPtr jobFactory(new JobFactory());
    JobManager manager(connectionFacadeMock, jobFactory, url);

    Url jobUrl = "http://example.com";
    Name jobName = "FooJob";
    JobStatus jobStatus = JOB_OK;

    manager.addJob(jobUrl, jobName, jobStatus);

    ASSERT_EQ(jobUrl, manager.getJob(jobUrl)->getUrl());
}

TEST_F(JobManagerTests, RemoveJob) {
    // We cannot use mocks here because it would mean that through created constant objects we're indirectly controlling
    // tested methods behaviour
    JobManager::IJobFactoryPtr jobFactory(new JobFactory());
    JobManager manager(connectionFacadeMock, jobFactory, url);

    Url jobUrl = "http://example.com";
    Name jobName = "FooJob";
    JobStatus jobStatus = JOB_OK;

    manager.addJob(jobUrl, jobName, jobStatus);
    manager.removeJob(jobUrl);

    ASSERT_EQ(IJobPtr(), manager.getJob(jobUrl));
}

TEST_F(JobManagerTests, UpdateJobThroughAddingIt) {
    // We cannot use mocks here because it would mean that through created constant objects we're indirectly controlling
    // tested methods behaviour
    JobManager::IJobFactoryPtr jobFactory(new JobFactory());
    JobManager manager(connectionFacadeMock, jobFactory, url);

    Url jobUrl = "http://example.com";
    Name jobName = "FooJob";
    JobStatus jobStatus = JOB_OK;
    JobStatus jobNewStatus = JOB_FAILED;

    manager.addJob(jobUrl, jobName, jobStatus);
    ASSERT_EQ(jobUrl, manager.getJob(jobUrl)->getUrl());
    EXPECT_EQ(jobStatus, manager.getJob(jobUrl)->getStatus());

    manager.addJob(jobUrl, jobName, jobNewStatus);
    EXPECT_EQ(jobUrl, manager.getJob(jobUrl)->getUrl());
    EXPECT_EQ(jobNewStatus, manager.getJob(jobUrl)->getStatus());
}

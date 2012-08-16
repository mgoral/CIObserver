#include <cstddef>
#include <memory>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "Exceptions.hpp"
#include "JobFactory.hpp"
#include "JobManager.hpp"

#include "IJobFactoryMock.hpp"
#include "IJobMock.hpp"

using namespace testing;
using namespace ci;
using namespace ci::core;

class JobManagerTests : public Test {
protected:
    virtual void SetUp() {
        testJobFactory.reset(new IJobFactoryMock());
        name = "FooManagerName";
    }

    std::shared_ptr<IJobFactoryMock> testJobFactory;
    Name name;
};

TEST_F(JobManagerTests, CreatingWithAGivenName) {
    JobManager manager(testJobFactory, name);

    ASSERT_EQ(name, manager.getName());
}

TEST_F(JobManagerTests, CreatingWithWrongName) {
    Name wrongName = "";

    ASSERT_THROW(JobManager(testJobFactory, wrongName), bad_parameter);
}

TEST_F(JobManagerTests, CheckDefaultManagerSettings) {
    JobManager manager(testJobFactory, name);

    EXPECT_EQ(name, manager.getName());
    EXPECT_EQ(Description(), manager.getDescription());
}

TEST_F(JobManagerTests, SetDescription) {
    JobManager manager(testJobFactory, name);
    Description desc = "Job manager description containing strange Polish characters: ąuęśćź";

    manager.setDescription(desc);
    ASSERT_EQ(desc, manager.getDescription());
}

TEST_F(JobManagerTests, ChangeName) {
    JobManager manager(testJobFactory, name);
    Name name = "JobManager name";

    manager.setName(name);
    ASSERT_EQ(name, manager.getName());
}

TEST_F(JobManagerTests, GetNonExistingJob) {
    JobManager manager(testJobFactory, name);
    Url jobUrl = "http://example.com";

    EXPECT_CALL(*testJobFactory, createJob(jobUrl)).WillOnce(Return(new IJobMock()));

    ASSERT_EQ(IJobPtr(), manager.getJob(jobUrl));
}

TEST_F(JobManagerTests, AddJob) {
    // We cannot use mocks here because it would mean that through created constant objects we're indirectly controlling
    // tested methods behaviour
    JobManager::IJobFactoryPtr jobFactory(new JobFactory());
    JobManager manager(jobFactory, name);

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
    JobManager manager(jobFactory, name);

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
    JobManager manager(jobFactory, name);

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

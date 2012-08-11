#include <memory>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "Exceptions.hpp"
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
        url = wxT("http://example.com");
        name = wxT("FooManagerName");
    }

    JobManager::IJobFactoryPtr testJobFactory;
    Url url;
    Name name;
};

TEST_F(JobManagerTests, CreatingWithDefauls) {
    JobManager manager(testJobFactory, url);

    ASSERT_EQ(url, manager.getUrl());
}

TEST_F(JobManagerTests, CreatingWithAGivenName) {
    JobManager manager(testJobFactory, url, name);

    ASSERT_EQ(url, manager.getUrl());
    ASSERT_EQ(name, manager.getName());
}

TEST_F(JobManagerTests, CreatingWithWrongURL) {
    Url wrongUrl = wxT("WrongUrl");

    ASSERT_THROW(JobManager(testJobFactory, wrongUrl), bad_parameter);
}

TEST_F(JobManagerTests, CheckDefaultManagerSettings) {
    JobManager manager(testJobFactory, url);

    EXPECT_EQ(url, manager.getName());
    EXPECT_EQ(url, manager.getUrl());
    EXPECT_EQ(Description(), manager.getDescription());
}

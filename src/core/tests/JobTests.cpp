#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "Job.hpp"

using namespace testing;
using namespace ci::core;

class JobTests : public Test {
protected:
    virtual void SetUp() {
        testJobName = wxT("FooJob");
        testDt.Set(10, JobTime::Feb, 2007, 23, 59, 59);
        testUrl = wxT("http://example.com");
    }

    JobName testJobName;
    JobTime testDt;
    Url testUrl;
};

TEST_F(JobTests, CheckJobInitializationWithAllDefaultParameters) {
    Job testJob(testJobName, testUrl);

    ASSERT_TRUE(testJobName.IsSameAs(testJob.getName()));
    ASSERT_TRUE(testUrl.IsSameAs(testJob.getUrl()));
}

TEST_F(JobTests, CheckJobInitializationWithStatus) {
    Job testJob(testJobName, testUrl, JOB_FAILED);

    ASSERT_TRUE(testJobName.IsSameAs(testJob.getName()));
    ASSERT_TRUE(testUrl.IsSameAs(testJob.getUrl()));
    ASSERT_EQ(JOB_FAILED, testJob.getStatus());
}

TEST_F(JobTests, CheckJobInitializationWithStatusAndTime) {
    Job testJob(testJobName, testUrl, JOB_FAILED, testDt);

    ASSERT_TRUE(testJobName.IsSameAs(testJob.getName()));
    ASSERT_TRUE(testUrl.IsSameAs(testJob.getUrl()));
    ASSERT_EQ(JOB_FAILED, testJob.getStatus());
    ASSERT_EQ(testDt, testJob.getTime());
}

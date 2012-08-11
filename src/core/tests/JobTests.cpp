#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "Job.hpp"

using namespace testing;
using namespace ci::core;

class JobTests : public Test {
protected:
    virtual void SetUp() {
        jobName = wxT("FooJob");
        testDt.Set(10, JobTime::Feb, 2007, 23, 59, 59);
        testUrl = wxT("http://example.com");
    }

    Name jobName;
    JobTime testDt;
    Url testUrl;
};

TEST_F(JobTests, JobInitializationWithAllDefaultParameters) {
    Job job(testUrl);

    ASSERT_EQ(testUrl, job.getName());
    ASSERT_EQ(testUrl, job.getUrl());
}

TEST_F(JobTests, JobInitializationWithName) {
    Job job(testUrl, jobName);

    ASSERT_EQ(jobName, job.getName());
    ASSERT_EQ(testUrl, job.getUrl());
}

TEST_F(JobTests, JobInitializationWithStatus) {
    Job job(testUrl, jobName, JOB_FAILED);

    ASSERT_EQ(jobName, job.getName());
    ASSERT_EQ(testUrl, job.getUrl());
    ASSERT_EQ(JOB_FAILED, job.getStatus());
}

TEST_F(JobTests, JobInitializationWithStatusAndTime) {
    Job job(testUrl, jobName, JOB_FAILED, testDt);

    ASSERT_EQ(jobName, job.getName());
    ASSERT_EQ(testUrl, job.getUrl());
    ASSERT_EQ(JOB_FAILED, job.getStatus());
    ASSERT_EQ(testDt, job.getTime());
}

TEST_F(JobTests, Copying) {
    Job job(testUrl, jobName, JOB_OK, testDt);
    JobTime newTime(31, JobTime::Mar, 2008, 22, 58, 57);

    job.setMaxHistorySize(30);
    job.setStatus(JOB_OK, newTime);
    Job secondJob = job;

    ASSERT_EQ(job, secondJob);
    EXPECT_EQ(secondJob.getName(), job.getName());
    EXPECT_EQ(secondJob.getUrl(), job.getUrl());
    EXPECT_EQ(job.getTime(), secondJob.getTime());
    EXPECT_EQ(job.getHistorySize(), secondJob.getHistorySize());
    EXPECT_EQ(job.getMaxHistorySize(), secondJob.getMaxHistorySize());
    ASSERT_EQ(job.getHistoryElement(0), secondJob.getHistoryElement(0));
    EXPECT_EQ(job.getHistoryElement(1), secondJob.getHistoryElement(1));
    EXPECT_EQ(job.getHistoryElement(100), secondJob.getHistoryElement(100));
}

TEST_F(JobTests, SettingCorrectJobStatus) {
    Job job(testUrl, jobName, JOB_FAILED, testDt);
    JobTime newTime(31, JobTime::Mar, 2008, 22, 58, 57);
    job.setStatus(JOB_OK, newTime);

    ASSERT_EQ(JOB_OK, job.getStatus());
    ASSERT_EQ(newTime, job.getTime());
}

TEST_F(JobTests, SettingIncorrectJobStatus) {
    Job job(testUrl, jobName, JOB_FAILED, testDt);
    JobTime newTime(31, JobTime::Mar, 2005, 22, 58, 57);
    job.setStatus(JOB_OK, newTime);

    ASSERT_EQ(JOB_FAILED, job.getStatus());
    ASSERT_EQ(testDt, job.getTime());
}

TEST_F(JobTests, DefaultMaxHistorySize) {
    Job job(testUrl, jobName);

    ASSERT_EQ(job.getMaxHistorySize(), defaultHistorySize);
}

TEST_F(JobTests, ChangingMaxHistorySize) {
    Job job(testUrl, jobName);
    size_t firstExpectedMaxSize = 3;
    size_t secondExpectedMaxSize = 7;
    size_t thirdExpectedMaxSize = 0;

    job.setMaxHistorySize(firstExpectedMaxSize);
    ASSERT_EQ(job.getMaxHistorySize(), firstExpectedMaxSize);

    job.setMaxHistorySize(secondExpectedMaxSize);
    ASSERT_EQ(job.getMaxHistorySize(), secondExpectedMaxSize);

    job.setMaxHistorySize(thirdExpectedMaxSize);
    ASSERT_EQ(job.getMaxHistorySize(), thirdExpectedMaxSize);
}

TEST_F(JobTests, HistorySizeAfterNotChangingJobStatus) {
    Job job(testUrl, jobName, JOB_FAILED, testDt);
    job.setStatus(JOB_FAILED);
    size_t expectedSize = 0;

    ASSERT_EQ(job.getHistorySize(), expectedSize);
}

TEST_F(JobTests, HistoryAfterChangingJobTwice) {
    // elements are stored in chronological order. First is the earliest, second is older and
    // last one is the oldest
    Job job(testUrl, jobName, JOB_FAILED, testDt); // JOB_FAILED, []

    JobTime firstTime(31, JobTime::Mar, 2009, 22, 58, 57);
    JobTime secondTime(31, JobTime::Mar, 2010, 22, 58, 57);

    job.setStatus(JOB_OK, firstTime);       // JOB_OK,      [JOB_FAILED]
    job.setStatus(JOB_UNKNOWN, secondTime); // JOB_UNKNOWN, [JOB_OK, JOB_FAILED]

    size_t expectedSize = 2;
    HistoryElement firstHistoryElement(firstTime, JOB_OK);
    HistoryElement secondHistoryElement(testDt, JOB_FAILED);

    ASSERT_EQ(job.getHistorySize(), expectedSize);
    EXPECT_EQ(job.getHistoryElement(0), firstHistoryElement);
    EXPECT_EQ(job.getHistoryElement(1), secondHistoryElement);
}

TEST_F(JobTests, GettingNonExistantHistoryElement) {
    Job job(testUrl, jobName, JOB_FAILED, testDt); // JOB_FAILED, []

    ASSERT_EQ(job.getHistoryElement(0), HistoryElement());
    ASSERT_EQ(job.getHistoryElement(5), HistoryElement());
}

TEST_F(JobTests, HistoryOverflow) {
    Job job(testUrl, jobName, JOB_FAILED, testDt);

    size_t maxSize = 3;
    job.setMaxHistorySize(maxSize);
    ASSERT_EQ(job.getMaxHistorySize(), maxSize);

    JobTime firstTime(31, JobTime::Mar, 2009, 22, 58, 57);
    JobTime secondTime(31, JobTime::Mar, 2010, 22, 58, 57);
    JobTime thirdTime(31, JobTime::Mar, 2011, 22, 58, 57);
    JobTime fourthTime(31, JobTime::Mar, 2012, 22, 58, 57);

    job.setStatus(JOB_OK, firstTime);
    job.setStatus(JOB_UNKNOWN, secondTime);
    job.setStatus(JOB_FAILED, thirdTime);
    job.setStatus(JOB_OK, fourthTime);

    HistoryElement firstHistoryElement(thirdTime, JOB_FAILED);
    HistoryElement secondHistoryElement(secondTime, JOB_UNKNOWN);
    HistoryElement thirdHistoryElement(firstTime, JOB_OK);

    ASSERT_EQ(job.getHistorySize(), maxSize);
    EXPECT_EQ(job.getHistoryElement(0), firstHistoryElement);
    EXPECT_EQ(job.getHistoryElement(1), secondHistoryElement);
    EXPECT_EQ(job.getHistoryElement(2), thirdHistoryElement);
    EXPECT_EQ(job.getHistoryElement(3), HistoryElement());
}

TEST_F(JobTests, ChangingHistorySizeWhenHistoryIsNotEmpty) {
    /*
     * This testcase consist of several use cases:
     * 1) changing history size to higher value than number of stored items
     * 2) changing history size to lower value than number of stored items
     * 3) changing history size to 0
     * 4) changing history size to higher value than 0. New history items should be properly added
     */

    Job job(testUrl, jobName, JOB_FAILED, testDt);

    size_t maxSize = 5;
    job.setMaxHistorySize(maxSize);
    ASSERT_EQ(job.getMaxHistorySize(), maxSize);

    JobTime firstTime(31, JobTime::Mar, 2009, 22, 58, 57);
    JobTime secondTime(31, JobTime::Mar, 2010, 22, 58, 57);
    JobTime thirdTime(31, JobTime::Mar, 2011, 22, 58, 57);
    JobTime fourthTime(31, JobTime::Mar, 2012, 22, 58, 57);
    JobTime fifthTime(31, JobTime::Mar, 2013, 22, 58, 57);

    HistoryElement firstHistoryElement(thirdTime, JOB_FAILED);
    HistoryElement secondHistoryElement(secondTime, JOB_UNKNOWN);
    HistoryElement thirdHistoryElement(firstTime, JOB_OK);
    HistoryElement fourthHistoryElement(testDt, JOB_FAILED);
    HistoryElement newFirstHistoryElement(fourthTime, JOB_OK);

    job.setStatus(JOB_OK, firstTime);
    job.setStatus(JOB_UNKNOWN, secondTime);
    job.setStatus(JOB_FAILED, thirdTime);
    job.setStatus(JOB_OK, fourthTime);

    maxSize = 8;
    size_t expectedSize = 4;
    job.setMaxHistorySize(maxSize);
    ASSERT_EQ(job.getMaxHistorySize(), maxSize);
    ASSERT_EQ(job.getHistorySize(), expectedSize);
    // First four items are saved
    EXPECT_EQ(job.getHistoryElement(0), firstHistoryElement);
    EXPECT_EQ(job.getHistoryElement(1), secondHistoryElement);
    EXPECT_EQ(job.getHistoryElement(2), thirdHistoryElement);
    EXPECT_EQ(job.getHistoryElement(3), fourthHistoryElement);
    // The rest should be empty
    for(int i = 4; i < 8; ++i) {
        EXPECT_EQ(job.getHistoryElement(i), HistoryElement());
    }

    maxSize = 3;
    expectedSize = 3;
    job.setMaxHistorySize(maxSize);
    ASSERT_EQ(job.getMaxHistorySize(), maxSize);
    ASSERT_EQ(job.getHistorySize(), expectedSize);
    // Now max history size is 3 so only 3 latest items should be stored
    EXPECT_EQ(job.getHistoryElement(0), firstHistoryElement);
    EXPECT_EQ(job.getHistoryElement(1), secondHistoryElement);
    EXPECT_EQ(job.getHistoryElement(2), thirdHistoryElement);
    for(int i = 3; i < 8; ++i) {
        EXPECT_EQ(job.getHistoryElement(i), HistoryElement());
    }

    maxSize = 0;    // Clears history
    expectedSize = 0;
    job.setMaxHistorySize(maxSize);
    ASSERT_EQ(job.getMaxHistorySize(), maxSize);
    ASSERT_EQ(job.getHistorySize(), expectedSize);
    // No history item should be left
    for(int i = 0; i < 8; ++i) {
        EXPECT_EQ(job.getHistoryElement(i), HistoryElement());
    }

    //Check that current status is untouched
    EXPECT_EQ(JOB_OK, job.getStatus());
    EXPECT_EQ(fourthTime, job.getTime());

    // Start adding new history elements
    maxSize = 2;
    expectedSize = 1;
    job.setMaxHistorySize(maxSize);

    job.setStatus(JOB_FAILED, fifthTime);   // previous is JOB_OK

    ASSERT_EQ(job.getMaxHistorySize(), maxSize);
    ASSERT_EQ(job.getHistorySize(), expectedSize);

    EXPECT_EQ(job.getHistoryElement(0), newFirstHistoryElement);
    for(int i = 1; i < 8; ++i) {
        EXPECT_EQ(job.getHistoryElement(i), HistoryElement());
    }
}

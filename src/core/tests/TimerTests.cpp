#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <memory>
#include <Poco/Thread.h>

#include "IJobManagerMock.hpp"

#include "Timer.hpp"

using namespace testing;
using namespace ci;
using namespace ci::core;

class TimerTests : public Test {
protected:
    virtual void SetUp() {
        jobManagerMock.reset(new NiceMock<IJobManagerMock>());
        defaultInterval = 30;
        managerName = "ManagerMock";

        ON_CALL(*jobManagerMock, getName()).WillByDefault(ReturnRef(managerName));
    }

    std::shared_ptr<IJobManagerMock> jobManagerMock;
    Interval defaultInterval;
    Name managerName;
};

TEST_F(TimerTests, CheckNotStartingConstructor) {
    Timer timer(jobManagerMock);
    EXPECT_CALL(*jobManagerMock, notify(_)).Times(0);

    Poco::Thread::sleep(200);
}

TEST_F(TimerTests, CheckStartingConstructor) {
    Timer timer(jobManagerMock, defaultInterval);
    EXPECT_CALL(*jobManagerMock, notify(_)).Times(AtLeast(10));

    Poco::Thread::sleep(320);
}

TEST_F(TimerTests, SetInterval) {
    Interval newInterval = 42;
    Timer timer(jobManagerMock);
    EXPECT_CALL(*jobManagerMock, notify(_)).Times(0);

    timer.setInterval(newInterval);
    ASSERT_EQ(newInterval, timer.getInterval());

    Poco::Thread::sleep(100);
}

TEST_F(TimerTests, SetIntervalWhileTimerIsRunning) {
    Interval newInterval = 42;
    Timer timer(jobManagerMock, defaultInterval);
    EXPECT_CALL(*jobManagerMock, notify(_)).Times(AtLeast(1));

    EXPECT_EQ(defaultInterval, timer.getInterval());

    Poco::Thread::sleep(50);

    timer.setInterval(newInterval);
    EXPECT_EQ(newInterval, timer.getInterval());

}

TEST_F(TimerTests, CheckManualStartingWithDefaultInterval) {
    Timer timer(jobManagerMock);
    EXPECT_CALL(*jobManagerMock, notify(_)).Times(0);

    timer.start();
    EXPECT_FALSE(timer.isRunning());

    Poco::Thread::sleep(200);
}

TEST_F(TimerTests, CheckSettingIntervalAndManualStarting) {
    Timer timer(jobManagerMock);
    timer.setInterval(50);
    EXPECT_CALL(*jobManagerMock, notify(_)).Times(AtLeast(6));

    EXPECT_FALSE(timer.isRunning());
    timer.start();
    EXPECT_TRUE(timer.isRunning());

    Poco::Thread::sleep(320);
}

TEST_F(TimerTests, ManualTimerStop) {
    Timer timer(jobManagerMock, defaultInterval);
    EXPECT_CALL(*jobManagerMock, notify(_)).Times(AtLeast(2));

    EXPECT_TRUE(timer.isRunning());

    Poco::Thread::sleep(70);

    timer.stop();
    EXPECT_FALSE(timer.isRunning());
    EXPECT_CALL(*jobManagerMock, notify(_)).Times(0);
    Poco::Thread::sleep(200);
}


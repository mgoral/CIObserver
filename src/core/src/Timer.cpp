#include "Timer.hpp"
#include "JobManager.hpp"
#include "JobFactory.hpp"

namespace ci {

namespace core {

Timer::Timer(ITimerObserverPtr observer)
: running(false), observer(observer), timer(0, 0), logger(Poco::Logger::get("CI.Core.Timer")) {}

Timer::Timer(ITimerObserverPtr observer, Interval interval)
: observer(observer), timer(0, interval), logger(Poco::Logger::get("CI.Core.Timer")) {
    poco_information(logger, "Start!");
    timer.start(Poco::TimerCallback<ITimerObserver>(*observer, &ITimerObserver::notify));
    running = true;
}

Timer::~Timer() {}

ITimerObserverPtr Timer::getObserver() const {
    return observer;
}

bool Timer::isRunning() const {
    return running;
}

void Timer::setInterval(Interval interval) {
    timer.restart(interval);
}

void Timer::start() {
    if(!running) {
        poco_information(logger, "Start!");
        timer.start(Poco::TimerCallback<ITimerObserver>(*observer, &ITimerObserver::notify));
    }

}

void Timer::stop() {
    if(running) {
        timer.stop();
    }
}

} // namespace core

} // namespace ci


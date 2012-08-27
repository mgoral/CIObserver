#include <Poco/Format.h>

#include "Timer.hpp"
#include "JobManager.hpp"
#include "JobFactory.hpp"

namespace ci {

namespace core {

Timer::Timer(ITimerObserverPtr observer)
: running(false), observer(observer), timer(0, 0), logger(Poco::Logger::get("CI.Core.Timer")) {}

Timer::Timer(ITimerObserverPtr observer, Interval interval)
: observer(observer), timer(30, interval), logger(Poco::Logger::get("CI.Core.Timer")) {
    timer.start(Poco::TimerCallback<ITimerObserver>(*observer, &ITimerObserver::notify));
    running = true;
    poco_information(logger, Poco::format(_("Started notifying observer '%s' with interval %u."),
        observer->getName().raw(), interval));
}

Timer::~Timer() {}

Interval Timer::getInterval() const {
    return timer.getPeriodicInterval();
}

ITimerObserverPtr Timer::getObserver() const {
    return observer;
}

bool Timer::isRunning() const {
    return running;
}

void Timer::setInterval(Interval interval) {
    if(running) {
        timer.restart(interval);
    }
    else {
        timer.setPeriodicInterval(interval);
    }
    poco_debug(logger, Poco::format(_("Changed interval for observer '%s' to %u."),
        observer->getName().raw(), interval));
}

void Timer::start() {
    if(!running &&  0 < getInterval()) {
        timer.start(Poco::TimerCallback<ITimerObserver>(*observer, &ITimerObserver::notify));
        running = true;
        poco_information(logger, Poco::format(_("Started notifying observer '%s' with interval %u."),
            observer->getName().raw(), getInterval()));
    }
}

void Timer::stop() {
    if(running) {
        timer.stop();
        running = false;
        poco_information(logger, Poco::format(_("Stopped notifying observer '%s'."), observer->getName().raw()));
    }
}

} // namespace core

} // namespace ci


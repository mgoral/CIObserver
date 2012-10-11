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
    poco_information(logger, Poco::format(_("Started notifying observers with interval %u."), interval));
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
    poco_debug(logger, Poco::format(_("Changed interval for observers to %u."), interval));
}

void Timer::start() {
    if(!running &&  0 < getInterval()) {
        timer.start(Poco::TimerCallback<ITimerObserver>(*observer, &ITimerObserver::notify));
        running = true;
        poco_information(logger, Poco::format(_("Started notifying observers with interval %u."), getInterval()));
    }
}

void Timer::stop() {
    if(running) {
        timer.stop();
        running = false;
        poco_information(logger, _("Stopped notifying observers."));
    }
}

} // namespace core

} // namespace ci


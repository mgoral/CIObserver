#ifndef TIMER_HPP
#define TIMER_HPP

#include <Poco/Timer.h>
#include <Poco/Logger.h>

#include "ITimer.hpp"

namespace ci {

namespace core {

class Timer : public ITimer {
private:
    bool running;
    ITimerObserverPtr observer;
    Poco::Timer timer;
    Poco::Logger& logger;

public:
    /*
     * @brief Constructor. Initialize observer but don't start timer.
     */
    Timer(ITimerObserverPtr observer);

    /*
     * @brief Constructor. Initialize observer and start timer with a given interval.
     */
    Timer(ITimerObserverPtr observer, Interval interval);

    /*
     * @brief Timer destructor
     */
    ~Timer();

    ITimerObserverPtr getObserver() const;
    bool isRunning() const;
    void setInterval(Interval interval);
    void start();
    void stop();
};

} // namespace core

} // namespace ci

#endif


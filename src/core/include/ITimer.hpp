#ifndef ITIMER_HPP
#define TIMER_HPP

#include <memory>

#include "GlobalDefs.hpp"
#include "ITimerObserver.hpp"

namespace ci {

namespace core {

typedef std::shared_ptr<ITimerObserver> ITimerObserverPtr;
typedef u32 Interval;

/*
 * @brief Class that manages time-checks for a given ITimerObserver.
 * ITimerObserverPtr is passed to ITimer ctor. Every given interval, timer notifies its' observer so it could make
 * appropriate actions. Observer is available to the outside world through getObserver() method.
 */
class ITimer {
public:
    virtual ~ITimer() {}

    /*
     * @brief Returns current notification interval.
     */
    virtual Interval getInterval() const = 0;

    /*
     * @brief Return stored manager.
     */
    virtual ITimerObserverPtr getObserver() const = 0;

    /*
     * @brief Check if timer is ticking.
     */
    virtual bool isRunning() const = 0;

    /*
     * @brief Change timer interval.
     * Note that changing it to 0 will stop the timer.
     */
    virtual void setInterval(Interval interval) = 0;

    /*
     * @brief Explicitly start the timer.
     */
    virtual void start() = 0;

    /*
     * @brief Explicitly stop the timer.
     */
    virtual void stop() = 0;

    bool operator <(const ITimer& other) const {
        // FIXME: change this function name from operator< to another
        return getObserver() < other.getObserver();
    }
};

} // namespace core

} // namespace ci

#endif


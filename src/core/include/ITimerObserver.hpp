#ifndef ITIMEROBSERVER_HPP
#define ITIMEROBSERVER_HPP

#include <Poco/Timer.h>

namespace ci {

namespace core {

/*
 * @brief Base class for all Poco::Timer observers.
 */
class ITimerObserver {
public:
    /*
     * @brief Returns observer identifier
     */
    virtual const Name& getName() const = 0;

    /*
     * @brief Poco::Timer callback function.
     */
    virtual void notify(Poco::Timer& timer) = 0;
};

} // namespace core

} // namespace ci

#endif



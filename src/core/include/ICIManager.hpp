#ifndef ICIMANAGER_HPP
#define ICIMANAGER_HPP

#include "GlobalDefs.hpp"
#include "ITimerObserver.hpp"
#include "IJobManager.hpp"

namespace ci {

namespace core {

/**
 * @brief: Class that manages the list of JobManagers; in other words, CI instances that are observed by a user.
 */
class ICIManager : public ITimerObserver {
public:
    virtual ~ICIManager() {}

    /**
     * @brief Adds a new observer to the list of observers. It'll be notified with the others.
     */
    virtual bool addManager(IJobManagerPtr observer) = 0;

    /**
     * @brief Return an observer stored on a given position.
     */
    virtual IJobManagerPtr getManager(u32 id) const = 0;

    /**
     * @brief Return ID of observer with a given name.
     * @return ID of observer or -1 if no observer found.
     */
    virtual s32 getManagerId(Name& observerName) const = 0;

    /**
     * @brief Remove an observer with a given ID from the list of observers.
     */
    virtual bool removeManager(u32 id) = 0;
};

} // namespace core

} // namespace ci

#endif


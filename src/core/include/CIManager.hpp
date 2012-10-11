#ifndef CIMANAGER_HPP
#define CIMANAGER_HPP

#include <vector>
#include <Poco/Timer.h>
#include <Poco/Logger.h>

#include "ICIManager.hpp"

namespace ci {

namespace core {

typedef std::vector<IJobManagerPtr> JobManagers;

class CIManager : public ICIManager {
private:
    Poco::Logger& logger;
    JobManagers managers;

public:
    CIManager();
    CIManager(const JobManagers& observers);
    ~CIManager();

    bool addManager(IJobManagerPtr observer);
    IJobManagerPtr getManager(u32 id) const;
    s32 getManagerId(Name& observerName) const;
    bool removeManager(u32 id);

    void notify(Poco::Timer& timer);
};

} // namespace core

} // namespace ci

#endif


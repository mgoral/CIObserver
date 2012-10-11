#include <algorithm>
#include <Poco/Format.h>

#include "CIManager.hpp"

namespace ci {

namespace core {

bool CIManager::addManager(IJobManagerPtr observer) {
    if(managers.end() == std::find(managers.begin(), managers.end(), observer)) {
        managers.push_back(observer);
        return true;
    }
    return false;
}

IJobManagerPtr CIManager::getManager(u32 id) const {
    if(managers.size() > id) {
        return managers.at(id);
    }
    return IJobManagerPtr();
}

s32 CIManager::getManagerId(Name& observerName) const {
    for(u32 i = 0; i < managers.size(); ++i) {
        if(observerName == managers.at(i)->getName()) {
            return i;
        }
    }
    return FOUND_INCORRECT;
}

bool CIManager::removeManager(u32 id) {
    if(managers.size() > id) {
        managers.erase(managers.begin() + id);
        return true;
    }
    return false;
}

void CIManager::notify(Poco::Timer& timer) {
    JobManagers::const_iterator iter;
    for(iter = managers.begin(); iter != managers.end(); ++iter) {
        (*iter)->update();
    }
}


} // namespace core

} // namespace ci

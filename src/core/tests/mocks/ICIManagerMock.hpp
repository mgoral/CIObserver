#ifndef ICIMANAGERMOCK_HPP
#define ICIMANAGERMOCK_HPP

#include <Poco/Timer.h>
#include "ICIManager.hpp"

namespace ci {
namespace core {

class ICIManagerMock : public ICIManager {
public:
    MOCK_METHOD1(addManager,
        bool(IJobManagerPtr observer));
    MOCK_CONST_METHOD1(getManager,
        IJobManagerPtr(u32 id));
    MOCK_CONST_METHOD1(getManagerId,
        s32(Name& observerName));
    MOCK_METHOD1(removeManager,
        bool(u32 id));
    MOCK_METHOD1(notify,
        void(Poco::Timer& timer));
};

}  // namespace core
}  // namespace ci

#endif


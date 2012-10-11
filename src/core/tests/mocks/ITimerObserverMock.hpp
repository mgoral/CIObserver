#ifndef ITIMEROBSERVERMOCK_HPP
#define ITIMEROBSERVERMOCK_HPP

#include <Poco/Timer.h>
#include "ITimerObserver.hpp"

namespace ci {
namespace core {

class ITimerObserverMock : public ITimerObserver {
public:
    MOCK_METHOD1(notify,
        void(Poco::Timer& timer));
};

}  // namespace core
}  // namespace ci

#endif


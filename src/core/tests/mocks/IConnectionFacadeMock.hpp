#ifndef ICONNECTIONFACADEMOCK_HPP
#define ICONNECTIONFACADEMOCK_HPP

#include "IConnectionFacade.hpp"

namespace ci {
namespace core {

class IConnectionFacadeMock : public IConnectionFacade {
public:
    MOCK_METHOD1(open,
        std::istream*(const Url& url));
};

}  // namespace core
}  // namespace ci

#endif


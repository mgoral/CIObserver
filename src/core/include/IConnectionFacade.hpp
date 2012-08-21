#ifndef ICONNECTIONFACADE_HPP
#define ICONNECTIONFACADE_HPP

#include <istream>

#include "GlobalDefs.hpp"

namespace ci {

namespace core {

class IConnectionFacade {
public:
    virtual std::istream* open(const Url& url) = 0;
};

} // namespace core

} // namespace ci

#endif


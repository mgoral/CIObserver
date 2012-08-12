#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <stdexcept>
#include <string>

#include "GlobalDefs.hpp"

namespace ci {

class bad_parameter : public std::invalid_argument {
public:
    explicit bad_parameter()
        : std::invalid_argument(_("invalid parameter")) {}
    explicit bad_parameter(const std::string& message)
        : std::invalid_argument(message) {}
};

} // namespace ci

#endif


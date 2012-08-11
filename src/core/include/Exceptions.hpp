#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <stdexcept>
#include <wx/string.h>
#include <string>

namespace ci {

class bad_parameter : public std::invalid_argument {
public:
    explicit bad_parameter()
        : std::invalid_argument("invalid parameter") {}
    explicit bad_parameter(const wxString& message)
        : std::invalid_argument(std::string(message.mb_str())) {}
};

} // namespace ci

#endif


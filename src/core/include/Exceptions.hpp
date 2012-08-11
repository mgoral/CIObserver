#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <stdexcept>
#include <wx/string.h>
#include <string>

namespace ci {

class bad_parameter : public std::invalid_argument {
public:
    explicit BadParameter()
        : std::runtime_error("Incorrect parameter given.");
    explicit BadParameter(const wxString& message)
        : std::runtime_error(std::string(message.mb_str())) {};
};

} // namespace ci

#endif


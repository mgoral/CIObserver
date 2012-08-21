#ifndef CONNECTIONFACADE_HPP
#define CONNECTIONFACADE_HPP

#include <istream>
#include <Poco/Logger.h>
#include <Poco/URI.h>
#include <Poco/Net/HTTPSession.h>
#include <Poco/Net/HTTPStreamFactory.h>
#include <Poco/Net/HTTPSStreamFactory.h>

#include "GlobalDefs.hpp"

namespace ci {

namespace core {

class ConnectionFacade {
private:
    static bool isInitialized;
    Poco::Logger& logger;
    Poco::Net::HTTPStreamFactory http;
    Poco::Net::HTTPSStreamFactory https;

    void initialize();

public:
    ConnectionFacade();
    ConnectionFacade(const std::string& proxyHost, Poco::UInt16 proxyPort = Poco::Net::HTTPSession::HTTP_PORT);

    // TODO: available since Poco 1.4.3. Currently Debian Unstable included 1.3.6 so it's commented out
    // ConnectionFacade(const std::string& proxyHost, Poco::UInt16 proxyPort, const std::string& proxyUsername,
    //    const std::string& proxyPassword);

    std::istream* open(const Url& url);
};

} // namespace core

} // namespace ci

#endif


#include <iostream>
#include <Poco/Format.h>
#include "Poco/URIStreamOpener.h"

#include "ConnectionFacade.hpp"
#include "Exceptions.hpp"

namespace ci {

namespace core {

bool ConnectionFacade::isInitialized = false;

ConnectionFacade::ConnectionFacade() : logger(Poco::Logger::get("CI.Core.ConnectionFacade")) {
    initialize();
}

ConnectionFacade::ConnectionFacade(const std::string& proxyHost, Poco::UInt16 proxyPort)
: logger(Poco::Logger::get("CI.Core.ConnectionFacade")), http(proxyHost, proxyPort), https(proxyHost, proxyPort) {
    initialize();
}

void ConnectionFacade::initialize() {
    if(false == isInitialized) {
        Poco::Net::HTTPStreamFactory::registerFactory();
        Poco::Net::HTTPSStreamFactory::registerFactory();

        isInitialized = true;
    }
}

// TODO: see comments in header
// ConnectionFacade::ConnectionFacade(const std::string& proxyHost, Poco::UInt16 proxyPort,
//    const std::string& proxyUsername, const std::string& proxyPassword)
// : logger(Poco::Logger::get("CI.Core.ConnectionFacade")), http(proxyHost, proxyPort, proxyUsername, proxyPassword),
//   https(proxyHost, proxyPort, proxyUsername, proxyPassword) {}

std::istream* ConnectionFacade::open(const Url& url) {
	Poco::URI uri(url);
    return Poco::URIStreamOpener::defaultOpener().open(uri);
}

} // namespace core

} // namespace ci


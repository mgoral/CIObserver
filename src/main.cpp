#include <Poco/AutoPtr.h>
#include <Poco/Logger.h>
#include <Poco/ConsoleChannel.h>
#include <Poco/FormattingChannel.h>
#include <Poco/PatternFormatter.h>

#include <Poco/SharedPtr.h>
#include <Poco/Net/InvalidCertificateHandler.h>
#include <Poco/Net/Context.h>
#include <Poco/Net/SSLManager.h>
#include <Poco/Net/ConsoleCertificateHandler.h>

#include <string>
#include <iostream>
#include <memory>

#include "Timer.hpp"
#include "JobManager.hpp"
#include "ConnectionFacade.hpp"
#include "JobFactory.hpp"

#include <Poco/Thread.h>

#include "GlobalDefs.hpp"


int main(int argc, char** argv) {
    // Initialize logging
    Poco::AutoPtr<Poco::ConsoleChannel> channel(new Poco::ConsoleChannel());
    Poco::AutoPtr<Poco::PatternFormatter> formatter(new Poco::PatternFormatter);
    formatter->setProperty("pattern", "%Y-%m-%d %H:%M:%S [%I/%q] [%s] : %t");
    Poco::AutoPtr<Poco::FormattingChannel> formattingChannel(new Poco::FormattingChannel(formatter, channel));
    Poco::Logger::root().setChannel(formattingChannel);
    //Poco::Logger::root().setLevel("debug");

    // Initialize SSL
    Poco::SharedPtr<Poco::Net::InvalidCertificateHandler> pInvalidCertHandler =
        new Poco::Net::ConsoleCertificateHandler(false);
    Poco::Net::Context::Ptr pContext = new Poco::Net::Context(Poco::Net::Context::CLIENT_USE, "", "", "",
        Poco::Net::Context::VERIFY_NONE, 9, true, "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");
    Poco::Net::SSLManager::instance().initializeClient(0, pInvalidCertHandler, pContext);

    return 0;
}


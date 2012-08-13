#include <Poco/AutoPtr.h>
#include <Poco/Logger.h>
#include <Poco/ConsoleChannel.h>

using Poco::Logger;
using Poco::ConsoleChannel;

int main() {
    Poco::AutoPtr<Poco::ConsoleChannel> channel(new Poco::ConsoleChannel());
    Poco::Logger::root().setChannel(channel); // ConsoleChannel as default doesn't seem to work...

    return 0;
}


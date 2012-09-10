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

#include "CIObserverApp.hpp"
#include "MainWindow.hpp"

namespace ci {

CIObserverApp::CIObserverApp(Glib::RefPtr<Gtk::Application> gtkApp) : initialized(false), appLogger(Poco::Logger::get("CI.Application.Main")), gtkApp(gtkApp) {}

void CIObserverApp::initialize(Poco::Util::Application& self) {
    loadConfiguration();
    Poco::Util::Application::initialize(self);

    // Initialize logging
    Poco::AutoPtr<Poco::ConsoleChannel> channel(new Poco::ConsoleChannel());
    Poco::AutoPtr<Poco::PatternFormatter> formatter(new Poco::PatternFormatter);
    formatter->setProperty("pattern", "%Y-%m-%d %H:%M:%S [%I/%q] [%s] : %t");
    Poco::AutoPtr<Poco::FormattingChannel> formattingChannel(new Poco::FormattingChannel(formatter, channel));
    Poco::Logger::root().setChannel(formattingChannel);
    //Poco::Logger::root().setLevel("debug");

    setLogger(appLogger);

    // Initialize SSL
    Poco::SharedPtr<Poco::Net::InvalidCertificateHandler> pInvalidCertHandler =
        new Poco::Net::ConsoleCertificateHandler(false);
    Poco::Net::Context::Ptr pContext = new Poco::Net::Context(Poco::Net::Context::CLIENT_USE, "", "", "",
        Poco::Net::Context::VERIFY_NONE, 9, true, "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");
    Poco::Net::SSLManager::instance().initializeClient(0, pInvalidCertHandler, pContext);

    // GTK
    refBuilder = Gtk::Builder::create();

    initialized = true;
}

void CIObserverApp::uninitialize(){
    // TODO
    Poco::Util::Application::uninitialize();
    initialized = false;
}

void CIObserverApp::reinitialize(Poco::Util::Application& self) {
    if(true == initialized)
        Poco::Util::Application::reinitialize(self);
    else
        initialize(self);
}

void CIObserverApp::defineOptions(Poco::Util::OptionSet& options) {
    // TODO
}

void CIObserverApp::handleOption(const std::string& name, const std::string& value) {
    // TODO
}

Path CIObserverApp::getFullPath(const Path& filePath) const {
    return config().getString("application.dir") + filePath;
}

int CIObserverApp::main(const std::vector<std::string>& args) {
    if(false == initialized) {
        poco_error(appLogger, _("Internal error (software bug): CIObserver is not initialized!"));
        return EXIT_CONFIG;
    }

    try {
        refBuilder->add_from_file(getFullPath("data/ui/mainWindow.ui"));
    }
    catch(const Glib::FileError& ex) {
        poco_error(appLogger, std::string(ex.what()));
        return EXIT_SOFTWARE;
    }
    catch(const Glib::MarkupError& ex) {
        poco_error(appLogger, std::string(ex.what()));
        return EXIT_SOFTWARE;
    }
    catch(const Gtk::BuilderError& ex) {
        poco_error(appLogger, std::string(ex.what()));
        return EXIT_SOFTWARE;
    }

    ci::gui::MainWindow* mainWindow = NULL;
    refBuilder->get_widget_derived("CIMainWindow", mainWindow);

    int retCode = gtkApp->run(*mainWindow);
    if(0 != retCode)
        return EXIT_SOFTWARE;
    return EXIT_OK;
}

} // namespace ci


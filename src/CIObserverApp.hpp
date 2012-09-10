#ifndef CIOBSERVERAPP_HPP
#define CIOBSERVERAPP_HPP

#include <string>
#include <vector>
#include <Poco/Util/Application.h>
#include <Poco/Util/OptionSet.h>
#include <Poco/Logger.h>
#include <gtkmm.h>

#include "GlobalDefs.hpp"

namespace ci {

class CIObserverApp : public Poco::Util::Application {
private:
    bool initialized;
    Poco::Logger& appLogger;
    Path installationPath;

    Glib::RefPtr<Gtk::Application> gtkApp;
    Glib::RefPtr<Gtk::Builder> refBuilder;

public:
    CIObserverApp( Glib::RefPtr<Gtk::Application> gtkApp);

    void initialize(Poco::Util::Application& self);
    void uninitialize();
    void reinitialize(Poco::Util::Application& self);
    void defineOptions(Poco::Util::OptionSet& options);
    void handleOption(const std::string& name, const std::string& value);
    int main(const std::vector<std::string>& args);

    /**
     * @return A full path to a given file. Full path consist of a CIObserver installation path and a given
     * filepath.
     */
    Path getFullPath(const Path& filePath) const;
};

} // namespace ci

#endif


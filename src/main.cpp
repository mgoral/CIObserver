#include "CIObserverApp.hpp"

int main(int argc, char** argv) {

    // HACK: this has to be here (outside of CIObserverApp) to properly parse GTK commandline args and not to mage
    // awkward tricks with &std::vector::front(), silly run(window, 0 NULL) which doesn't assert and so on... Yeah, here
    // gtkmm sucks... Or maybe using two classes for an Application iface (Poco and GTK) sucks? Who knows... --mgoral
    Glib::RefPtr<Gtk::Application> gtkApp = Gtk::Application::create(argc, argv, Glib::ustring("org.CIObserver"));
    ci::CIObserverApp app(gtkApp);

    try {
        app.init(argc, argv);
    }
    catch (Poco::Exception& exc) {
        app.logger().log(exc);
        return Poco::Util::Application::EXIT_CONFIG;
    }
    return app.run();
}


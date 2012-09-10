#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <gtkmm.h>
#include <Poco/Logger.h>

namespace ci {

namespace gui {

class MainWindow : public Gtk::Window {
private:
    Poco::Logger& logger;

public:
    MainWindow(BaseObjectType* object, const Glib::RefPtr<Gtk::Builder>& builder);
};

} // namespace gui

} // namespace ci

#endif


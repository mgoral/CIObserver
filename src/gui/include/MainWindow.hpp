#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <gtkmm.h>
#include <Poco/Logger.h>

#include "GlobalDefs.hpp"

namespace ci {

namespace gui {

class MainWindow : public Gtk::Window {
private:
    Poco::Logger& logger;

protected:
    Glib::RefPtr<Gtk::Builder> refBuilder;

    // Widgets
    Gtk::Button* buttonAdd;
    Gtk::Button* buttonEdit;
    Gtk::Button* buttonRemove;

    // Signal handlers
    void editCI(const Name& ciName);
    void removeCI();
    void quit();

public:
    MainWindow(BaseObjectType* object, const Glib::RefPtr<Gtk::Builder>& builder);
};

} // namespace gui

} // namespace ci

#endif


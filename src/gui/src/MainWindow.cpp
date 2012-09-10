#include "MainWindow.hpp"

namespace ci {

namespace gui {

MainWindow::MainWindow(BaseObjectType* object, const Glib::RefPtr<Gtk::Builder>& builder)
: Gtk::Window(object), logger(Poco::Logger::get("CI.GUI.MainWindow")) {
    // TODO: initialization code goes here... --mgoral
}

} // namespace gui

} // namespace ci

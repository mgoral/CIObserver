#include "JobEditDialog.hpp"

namespace ci {

namespace gui {

JobEditDialog::JobEditDialog(BaseObjectType* object, const Glib::RefPtr<Gtk::Builder>& builder)
: Gtk::Dialog(object), logger(Poco::Logger::get("CI.GUI.MainWindow")) {
    // TODO: initialization code goes here... --mgoral
}

} // namespace gui

} // namespace ci

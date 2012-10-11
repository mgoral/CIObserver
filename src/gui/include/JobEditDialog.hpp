#ifndef JOBEDITDIALOG_HPP
#define JOBEDITDIALOG_HPP

#include <gtkmm.h>
#include <Poco/Logger.h>

namespace ci {

namespace gui {

class JobEditDialog : public Gtk::Dialog {
private:
    Poco::Logger& logger;

public:
    JobEditDialog(BaseObjectType* object, const Glib::RefPtr<Gtk::Builder>& builder);
};

} // namespace gui

} // namespace ci

#endif


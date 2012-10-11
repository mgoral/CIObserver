#include "MainWindow.hpp"

namespace ci {

namespace gui {

MainWindow::MainWindow(BaseObjectType* object, const Glib::RefPtr<Gtk::Builder>& builder)
: Gtk::Window(object), logger(Poco::Logger::get("CI.GUI.MainWindow")), refBuilder(builder),
buttonAdd(0), buttonEdit(0), buttonRemove(0){

    refBuilder->get_widget("btnCIAdd", buttonAdd);
    refBuilder->get_widget("btnCIEdit", buttonEdit);
    refBuilder->get_widget("btnCIRemove", buttonRemove);

    if(buttonAdd)
        buttonAdd->signal_clicked().connect(sigc::bind<Name>(
            sigc::mem_fun(*this, &MainWindow::editCI), "AddCI"));

    //m_pButton->signal_clicked().connect( sigc::mem_fun(*this, &DerivedDialog::on_button_quit) );
    //m_button1.signal_clicked().connect( sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &HelloWorld::on_button_clicked), "button 1") );

}

void MainWindow::editCI(const Name& buttonName) {
    Gtk::Dialog* editor = 0;
    if("AddCI" == buttonName) {
        refBuilder->get_widget("CIEdit", editor);
        editor->show();
    }
}

void MainWindow::removeCI() {

}

void MainWindow::quit() {

}

} // namespace gui

} // namespace ci

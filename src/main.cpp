#include <gtkmm.h>

#include "gui/GUI.h"

int main(int argc, char *argv[]) {
    Gtk::Main gtk(argc, argv);
    sag::GUI gui;
    gtk.run(gui);
    
    return 0;
}

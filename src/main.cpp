#include <gtkmm.h>

#include "gui/GUI.h"
//#include "formulas/Quadratic.h"
//#include "rendering/PixbufRenderer.h"
//#include "generation/SimpleGenerator.h"

using namespace std;
using namespace sag;

int main(int argc, char *argv[]) {
    Gtk::Main gtk(argc, argv);
    GUI gui;
    gtk.run(gui);
    
//    Quadratic f;
//    PixbufRenderer r(512, 512);
//    SimpleGenerator g(f, r, 50000);
//    
//    g.run();
//    r.render();
//    
//    r.getOutput()->save("test.png", "png");
//    
//    r.resize(256,256);
//
//    g.run();
//    r.render();
//    
//    r.getOutput()->save("test-resized.png", "png");
    
    return 0;
}

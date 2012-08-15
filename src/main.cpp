#include <iostream>
#include <gtkmm.h>

#include "formulas/Quadratic.h"
#include "generation/SimpleGenerator.h"
#include "rendering/PixbufRenderer.h"

using namespace std;
using namespace sag;

class ImageWindow : public Gtk::Window {
public:
    ImageWindow(Glib::RefPtr<Gdk::Pixbuf> pb): img(pb) {
        set_default_size(pb->get_width(), pb->get_height());
        
        add(img);
        img.show();
    }
    virtual ~ImageWindow() {}
    
private:
    Gtk::Image img;
};

int main(int argc, char *argv[]) {
    Gtk::Main app(argc, argv);
    
    // The formula (with randomized parameters)
    Quadratic formula;
    
    // The renderer
    PixbufRenderer renderer(512, 512);
    ImageWindow window(renderer.getOutput());
    
    // The generator
    SimpleGenerator generator(formula, renderer, 1, false);
    
    // BOOM
    generator.run();
    renderer.render();
    
    app.run(window);
	return 0;
}

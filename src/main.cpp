#include <iostream>
#include <gtkmm.h>

#include "formulas/Quadratic.h"
#include "generation/SimpleGenerator.h"
#include "rendering/PixbufRenderer.h"

using namespace std;
using namespace sag;

class ImageWindow : public Gtk::Window {
public:
    ImageWindow(Glib::RefPtr<Gdk::Pixbuf> pb): pb(pb), img(pb) {
        set_default_size(pb->get_width(), pb->get_height());
        
        evbox.add(img);
    
        evbox.set_events(Gdk::BUTTON_PRESS_MASK);
        
        add(evbox);
        
        show_all_children();
    }
    virtual ~ImageWindow() {}
    
    void refresh() {
        img.clear();
        img.set(pb);
    }
    
    Glib::SignalProxy1<bool, GdkEventButton*> signal_button_pressed() {
        return evbox.signal_button_press_event();
    }
    
private:
    Glib::RefPtr<Gdk::Pixbuf> pb;
    Gtk::EventBox evbox;
    Gtk::Image img;
};

class Application {
    // The formula (with randomized parameters)
    Quadratic formula;
    
    // The renderer
    PixbufRenderer renderer;
    ImageWindow window;
    
    // The generator
    SimpleGenerator generator;
public:
    Application(): renderer(512, 512), window(renderer.getOutput()), generator(formula, renderer, 100000, false) {}
    
    void run() {
        window.signal_button_pressed().connect( sigc::mem_fun(*this, &Application::on_button_pressed) );
        
        generator.run();
        renderer.render();
    }
    
    inline ImageWindow& getWindow() { return window; }
private:
    bool on_button_pressed(GdkEventButton* btn) {        
        if (btn->button != 1) return false;
        
        generator.reset();
        generator.run();
        renderer.render();
        window.refresh();
        return true;
    }
};

int main(int argc, char *argv[]) {
    Gtk::Main gtk(argc, argv);
   
    Application app;
    app.run();
    
    gtk.run(app.getWindow());

    return 0;
}

#include "gui/ChooserWindow.h"

#include "formulas/DeJong.h"

namespace sag {
    ChooserWindow::ChooserWindow(): renderer(512, 512), view(renderer) {
        // Setup the window
        Gdk::Geometry hints;
        hints.min_width = 256;
        hints.min_height = 256;
        set_geometry_hints(*this, hints, Gdk::HINT_MIN_SIZE);
        set_default_size(512, 512);
        
        // Setup the generating stuff
        formula = new DeJong();
        generator = new SimpleGenerator(*formula, renderer, 10000);
        
        view.add_events(Gdk::BUTTON_PRESS_MASK);
        view.signal_button_press_event().connect(sigc::mem_fun(*this, &ChooserWindow::on_image_click));
        
        add(view);
        
        show_all_children();
    }
    
    ChooserWindow::~ChooserWindow() {
        delete generator;
        delete formula;
    }
    
    void ChooserWindow::on_show() {
        Gtk::Window::on_show();
        generator->run();
        renderer.render();
    }
    
    void ChooserWindow::on_size_allocate(Gtk::Allocation& alloc) {
        Gtk::Window::on_size_allocate(alloc);
        
        renderer.resize(alloc.get_width(), alloc.get_height());
        generator->run();
        renderer.render();
    }
    
    bool ChooserWindow::on_image_click(GdkEventButton* evt) {
        if (evt->button != 1) return false;
        
        renderer.clear();
        generator->reset();
        generator->run();
        renderer.render();
        view.get_window()->invalidate(false);
        return true;
    }
}
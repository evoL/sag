#include "gui/ChooserWindow.h"

namespace sag {
    ChooserWindow::ChooserWindow():
        box(false, 0),
        table(COLS, ROWS, true),
        button("PIERDUT!"),
        views(COLS*ROWS)
    {
        // Window setup
        Gdk::Geometry hints;
        hints.min_width = 1000;
        hints.min_height = 600;
        hints.max_width = 1000;
        hints.max_height = 600;
        set_geometry_hints(*this, hints, Gdk::HINT_MIN_SIZE | Gdk::HINT_MAX_SIZE);
        set_default_size(1000, 600);
        set_resizable(false);
        
        // Box setup
        add(box);
        
        // Button setup
        button.set_size_request(400, -1);
        
        button.signal_clicked().connect(sigc::mem_fun(*this, &ChooserWindow::on_button_clicked));
        
        box.pack_end(button, Gtk::PACK_SHRINK);
    
        // Table setup
        box.pack_start(table);
        
        int i = 0;
        int x, y;
        for (auto it = views.begin(); it < views.end(); it++) {
            x = i / ROWS;
            y = i % ROWS;
            
            (*it) = new StandaloneAttractorView(200,200);
            table.attach(**it, x, x+1, y, y+1);
            
            i++;
        }
        
        show_all_children();
    }
    
    ChooserWindow::~ChooserWindow() {
        for (auto it = views.begin(); it < views.end(); it++) {
            table.remove(**it);
            delete *it;
            *it = nullptr;
        }
    }
    
    void ChooserWindow::on_button_clicked() {
        for (auto it = views.begin(); it < views.end(); it++) {
            (**it).reset();
//            (**it).get_window()->invalidate(false);
        }
        table.get_window()->invalidate(true);
    }
}
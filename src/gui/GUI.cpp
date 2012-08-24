#include "gui/GUI.h"

#include <gtkmm/messagedialog.h>
#include <sstream>

namespace sag {
    GUI::GUI(): chooser(this) {
        // Window setup
        Gdk::Geometry hints;
        hints.min_width = WIDTH;
        hints.min_height = HEIGHT;
        hints.max_width = WIDTH;
        hints.max_height = HEIGHT;
        set_geometry_hints(*this, hints, Gdk::HINT_MIN_SIZE | Gdk::HINT_MAX_SIZE);
        set_default_size(WIDTH, HEIGHT);
        set_resizable(false);
        
        add(chooser);
        
        chooser.show();
    }
    
    GUI::ChooserView::ChooserView(GUI* gui):
        Gtk::HBox(false, 0),
        gui(gui),
        table(COLS, ROWS, true),
        panel(false, 0),
        views(COLS*ROWS)
    {
        // Table setup
        pack_start(table);
        
        int i = 0;
        int x, y;
        for (auto it = views.begin(); it < views.end(); it++) {
            x = i / ROWS;
            y = i % ROWS;
            
            (*it) = new StandaloneAttractorView(HEIGHT/COLS, HEIGHT/ROWS, AttractorView::ALL_EVENTS);
            (*it)->signal_button_press_event().connect(sigc::bind<StandaloneAttractorView*>(sigc::mem_fun(*this, &ChooserView::onImageClick), *it));
            table.attach(**it, x, x+1, y, y+1);
            
            i++;
        }
        
        // Panel setup
        panel.set_size_request(WIDTH-HEIGHT, -1);
        pack_end(panel, Gtk::PACK_SHRINK);
        
        title.set_markup("<span size=\"large\" weight=\"bold\">Choose an attractor</span>");
        title.set_padding(10, 10);
        panel.pack_start(title, Gtk::PACK_SHRINK);
        
        randomizeButton.set_label("Generate more");
        randomizeButton.set_size_request(-1, 80);
        randomizeButton.set_border_width(5);
        randomizeButton.signal_clicked().connect(sigc::mem_fun(*this, &ChooserView::randomizeAttractors));
        panel.pack_start(randomizeButton, Gtk::PACK_SHRINK);
        
        loadButton.set_label("Load from file");
        loadButton.set_size_request(-1, 80);
        loadButton.set_border_width(5);
        loadButton.signal_clicked().connect(sigc::mem_fun(*this, &ChooserView::loadAttractor));
        panel.pack_start(loadButton, Gtk::PACK_SHRINK);
        
        show_all_children();
    }
    
    GUI::ChooserView::~ChooserView() {
        for (auto it = views.begin(); it < views.end(); it++) {
            table.remove(**it);
            delete *it;
            *it = nullptr;
        }
    }
    
    void GUI::ChooserView::randomizeAttractors() {
        for (auto it = views.begin(); it < views.end(); it++) {
            (**it).reset();
        }
        table.get_window()->invalidate(true);
    }
    
    void GUI::ChooserView::loadAttractor() {
        Gtk::MessageDialog dialog(*gui, "Not implemented yet");
        dialog.set_secondary_text("Please wait for the developers or implement this yourself. :)");
        
        dialog.run();
    }
    
    bool GUI::ChooserView::onImageClick(GdkEventButton* evt, StandaloneAttractorView* view) {
        const Formula *f = view->getFormula();
        
        Gtk::MessageDialog dialog(*gui, "You've clicked a " + f->name());
        
        std::stringstream ss;
        ss.precision(18);
        ss << "AttraGen-compatible data:" << std::endl << std::endl;
        ss << f->name() << std::endl
           << f->getStartPoint().x << std::endl
           << f->getStartPoint().y << std::endl;
        
        for (auto it = f->getParameters().begin(); it < f->getParameters().end(); it++) {
            ss << *it << std::endl;
        }
        
        dialog.set_secondary_text(ss.str());
        dialog.run();
        
        return true;
    }
}
#ifndef SAG_CHOOSERWINDOW
#define SAG_CHOOSERWINDOW

#include <gtkmm/window.h>
#include <gtkmm/table.h>
#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/button.h>
#include <vector>

#include "gui/StandaloneAttractorView.h"

namespace sag {
    class ChooserWindow : public Gtk::Window {
    public:
        ChooserWindow();
        virtual ~ChooserWindow();
        
    protected:
    private:
        static const int WIDTH = 900;
        static const int HEIGHT = 600;
        static const int ROWS = 3;
        static const int COLS = 3;
        
        Gtk::HBox box;
        Gtk::Table table;
        Gtk::VBox panel;
        Gtk::Label title;
        Gtk::Button randomizeButton, loadButton;
        std::vector<StandaloneAttractorView*> views;
        
        void randomizeAttractors();
        void loadAttractor();
        bool onImageClick(GdkEventButton* evt, StandaloneAttractorView* view);
    };
}

#endif
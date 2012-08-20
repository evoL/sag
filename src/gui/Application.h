#ifndef SAG_APPLICATION_H
#define SAG_APPLICATION_H

#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include "gui/ChooserWindow.h"

namespace sag {
    class Application {
    public:
        void run();
        inline Gtk::Window& getWindow() { return window; }
    private:
        class TestWindow : public Gtk::Window {
        public:
            TestWindow(): button("Test Window") {
                add(button);
                show_all_children();
            }
            virtual ~TestWindow() {}
        protected:
            Gtk::Button button;
        };
        
        ChooserWindow window;
    };
}

#endif
#ifndef SAG_CHOOSERWINDOW
#define SAG_CHOOSERWINDOW

#include <gtkmm/window.h>
#include "formulas/Formula.h"
#include "rendering/PixbufRenderer.h"
#include "generation/SimpleGenerator.h"
#include "gui/AttractorView.h"

namespace sag {
    class ChooserWindow : public Gtk::Window {
    public:
        ChooserWindow();
        virtual ~ChooserWindow();
        
    protected:
        virtual void on_show();
        virtual void on_size_allocate(Gtk::Allocation& alloc);
        
    private:
        Formula *formula;
        PixbufRenderer renderer;
        SimpleGenerator *generator;
        AttractorView view;
        
        bool on_image_click(GdkEventButton* evt);
    };
}

#endif
#ifndef SAG_ATTRACTORVIEW
#define SAG_ATTRACTORVIEW

#include <gtkmm/drawingarea.h>
#include <gdkmm/pixbuf.h>
#include "generation/Generator.h"
#include "rendering/PixbufRenderer.h"

namespace sag {
    class AttractorView : public Gtk::DrawingArea {
    public:
        AttractorView(PixbufRenderer& r):
            Gtk::DrawingArea(),
            renderer(&r) {}
        virtual ~AttractorView() {}
        
        inline PixbufRenderer& getRenderer() { return *renderer; }
    protected:
        PixbufRenderer *renderer;
        
        virtual bool on_expose_event(GdkEventExpose* event);
    };
}

#endif

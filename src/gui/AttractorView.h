#ifndef SAG_ATTRACTORVIEW
#define SAG_ATTRACTORVIEW

#include <gtkmm/drawingarea.h>
#include <gdkmm/pixbuf.h>
#include "rendering/PixbufRenderer.h"

namespace sag {
    class AttractorView : public Gtk::DrawingArea {
    public:
        enum Events {
            NO_EVENT = 0,
            HOVER_EVENT = 1 << 0,
            MOUSEBUTTON_EVENT = 1 << 1,
            ALL_EVENTS = 3
        };
        
        AttractorView(PixbufRenderer& r, Events evts = NO_EVENT);
        virtual ~AttractorView() {}
        
        inline void setHovered(bool hovered) { isMouseOver = hovered; }
        
        inline PixbufRenderer& getRenderer() { return *renderer; }
    protected:
        PixbufRenderer *renderer;
        Events events;
        bool isMouseOver;
        
        virtual bool on_expose_event(GdkEventExpose* event);
        virtual bool on_enter_notify_event(GdkEventCrossing* event);
        virtual bool on_leave_notify_event(GdkEventCrossing* event);
        
        
    };
}

#endif

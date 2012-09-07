#ifndef SAG_ATTRACTORVIEW
#define SAG_ATTRACTORVIEW

#include <gtkmm/drawingarea.h>
#include <gdkmm/pixbuf.h>
#include "rendering/PixbufRenderer.h"

namespace sag {
    /**
     * @brief Displays an attractor.
     */
    class AttractorView : public Gtk::DrawingArea {
    public:
        /**
         * @brief The events the AttractorView can respond to.
         */
        enum Events {
            NO_EVENT          = 0,
            HOVER_EVENT       = 1 << 0,
            MOUSEBUTTON_EVENT = 1 << 1,
            DRAG_EVENT        = 1 << 2,
            SCROLL_EVENT      = 1 << 3,
            ALL_EVENTS        = 15
        };
        
        /**
         * @brief Constructs an AttractorView using the specified renderer.
         *
         * @param r The PixbufRenderer to use.
         * @param evts Events that the view should respond to.
         */
        AttractorView(PixbufRenderer& r, Events evts = NO_EVENT);
        virtual ~AttractorView() {}
        
        /**
         * @brief Sets whether the view is hovered by the mouse.
         *
         * @param hovered True or false.
         */
        inline void setHovered(bool hovered) { isMouseOver = hovered; }
        
        /**
         * @brief Gets the renderer.
         *
         * @returns The PixbufRenderer.
         */
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

#include "gui/AttractorView.h"

namespace sag {
    AttractorView::AttractorView(PixbufRenderer& r, Events evts):
        Gtk::DrawingArea(),
        renderer(&r),
        events(evts)
    {
        Gdk::EventMask mask;
        if (events != NO_EVENT) {
            if (events & HOVER_EVENT) mask |= Gdk::ENTER_NOTIFY_MASK | Gdk::LEAVE_NOTIFY_MASK;
            if (events & MOUSEBUTTON_EVENT) mask |= Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK;
            add_events(mask);
        }
        isMouseOver = false;
    }
    
    bool AttractorView::on_expose_event(GdkEventExpose* event) {
        auto img = renderer->getOutput();
        
        img->render_to_drawable(get_window(), get_style()->get_black_gc(), 0, 0, 0, 0, img->get_width(), img->get_height(), Gdk::RGB_DITHER_NONE, 0, 0);
        return true;
    }
    
    bool AttractorView::on_enter_notify_event(GdkEventCrossing* event) {
        if (Gtk::DrawingArea::on_enter_notify_event(event)) return true;
        
        isMouseOver = true;
        return true;
    }
    
    bool AttractorView::on_leave_notify_event(GdkEventCrossing* event) {
        if (Gtk::DrawingArea::on_leave_notify_event(event)) return true;
        
        isMouseOver = false;
        return true;
    }
}
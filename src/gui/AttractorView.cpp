#include "gui/AttractorView.h"

namespace sag {
    bool AttractorView::on_expose_event(GdkEventExpose* event) {        
        auto img = renderer->getOutput();
        
        img->render_to_drawable(get_window(), get_style()->get_black_gc(), 0, 0, 0, 0, img->get_width(), img->get_height(), Gdk::RGB_DITHER_NONE, 0, 0);
        return true;
    }
}
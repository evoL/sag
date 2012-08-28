#include "gui/StandaloneAttractorView.h"

#include <gdkmm/cursor.h>
#include "utils/Random.h"
#include "formulas/all.h"

namespace sag {
    StandaloneAttractorView::StandaloneAttractorView(int w, int h, Events evts):
        AttractorView(*(new PixbufRenderer(w, h)), evts),
        formula(nullptr),
        generator(nullptr)
    {
        // Drawing setup
        randomize();
        generator->run();
		renderer->wait();
        renderer->render();
    }
    
    StandaloneAttractorView::~StandaloneAttractorView() {
        delete generator;
        delete formula;
        delete renderer;
    }
    
    void StandaloneAttractorView::randomize() {
        // The most naive approach to formula randomization
        // TODO: figure out how to improve this
        
        if (formula != nullptr) delete formula;
        
        int rnd = Random<int>::getGlobal().inRange(0, FORMULA_NAMES.size()-1);
        
        formula = createFormula(FORMULA_NAMES[rnd]);
        // TODO: create a facility for managing user defined formulas
        
        if (generator != nullptr) delete generator;
        
        generator = new SimpleGenerator(*formula, *renderer, ITERATIONS);
    }
    
    void StandaloneAttractorView::reset() {
        renderer->clear();
        randomize();
        generator->run();
		renderer->wait();
        renderer->render();
    }
    
    bool StandaloneAttractorView::on_expose_event(GdkEventExpose* event) {
        AttractorView::on_expose_event(event);
        
        auto window = get_window();
        if (window) {
            // Draw text on top of the attractor
            auto layout = create_pango_layout("");
            layout->set_markup("<span foreground=\"#666\" size=\"small\">" + formula->name() + "</span>");
            
            window->draw_layout(get_style()->get_text_gc(Gtk::STATE_NORMAL), 5, 5, layout);
            
            // The mouseover effect
            if (isMouseOver) {
                Cairo::RefPtr<Cairo::Context> cr = window->create_cairo_context();
                cr->rectangle(event->area.x, event->area.y, event->area.width, event->area.height);
                cr->clip();
                
                cr->set_source_rgb(1, 1, 1);
                cairo_set_operator(cr->cobj(), CAIRO_OPERATOR_OVERLAY);
                cr->rectangle(0, 0, get_width(), get_height());
                cr->fill();
                
                cr->set_source_rgba(1, 1, 1, 0.1);
                cr->set_operator(Cairo::OPERATOR_OVER);
                cr->rectangle(0, 0, get_width(), get_height());
                cr->fill();
            }
        }
        
        return true;
    }
    
    bool StandaloneAttractorView::on_enter_notify_event(GdkEventCrossing* event) {
        AttractorView::on_enter_notify_event(event);
        
        auto window = get_window();

        Gdk::Cursor hand(Gdk::HAND2);
        window->set_cursor(hand);
        
        window->invalidate(false);
        return true;
    }
    bool StandaloneAttractorView::on_leave_notify_event(GdkEventCrossing* event) {
        AttractorView::on_leave_notify_event(event);
        
        auto window = get_window();
        
        window->set_cursor();
        window->invalidate(false);
        return true;
    }
}

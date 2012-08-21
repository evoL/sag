#include "gui/StandaloneAttractorView.h"

#include "utils/Random.h"
#include "formulas/DeJong.h"
#include "formulas/Quadratic.h"

namespace sag {
    StandaloneAttractorView::StandaloneAttractorView(int w, int h):
        AttractorView(*(new PixbufRenderer(w, h))),
        formula(nullptr),
        generator(nullptr)
    {
        randomize();
        generator->run();
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
        
        int rnd = Random<int>::get().inRange(0, FORMULA_COUNT-1);
        
        switch (rnd) {
            case 0:
                formula = new DeJong();
                formulaName = "DeJong";
                break;
            case 1:
                formula = new Quadratic();
                formulaName = "Quadratic";
                break;
        }
        
        if (generator != nullptr) delete generator;
        
        generator = new SimpleGenerator(*formula, *renderer, ITERATIONS);
    }
    
    void StandaloneAttractorView::reset() {
        renderer->clear();
        randomize();
        generator->run();
        renderer->render();
    }
    
    bool StandaloneAttractorView::on_expose_event(GdkEventExpose* event) {
        AttractorView::on_expose_event(event);
        
        auto layout = create_pango_layout("");
        layout->set_markup("<span foreground=\"#666\" size=\"small\">" + formulaName + "</span>");
        
        get_window()->draw_layout(get_style()->get_text_gc(Gtk::STATE_NORMAL), 5, 5, layout);
        
        return true;
    }
}
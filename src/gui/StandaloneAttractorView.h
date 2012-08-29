#ifndef SAG_STANDALONEATTRACTORVIEW_H
#define SAG_STANDALONEATTRACTORVIEW_H

#include "gui/AttractorView.h"
#include "generation/SimpleGenerator.h"
#include "formulas/Formula.h"
#include <string>

namespace sag {
    class StandaloneAttractorView : public AttractorView {
    public:
        StandaloneAttractorView(int w, int h, Events evts = NO_EVENT);
        virtual ~StandaloneAttractorView();
        
        void randomize();
        void reset();
        
        inline const Formula* getFormula() { return formula; }
    protected:
        virtual bool on_expose_event(GdkEventExpose* event);
        virtual bool on_enter_notify_event(GdkEventCrossing* event);
        virtual bool on_leave_notify_event(GdkEventCrossing* event);
    
    private:
        static const int ITERATIONS = 10000;
        
        Formula *formula;
        SimpleGenerator *generator;
    };
}

#endif

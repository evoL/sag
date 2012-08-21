#ifndef SAG_STANDALONEATTRACTORVIEW_H
#define SAG_STANDALONEATTRACTORVIEW_H

#include "gui/AttractorView.h"
#include "generation/SimpleGenerator.h"
#include "formulas/Formula.h"
#include <string>

namespace sag {
    class StandaloneAttractorView : public AttractorView {
    public:
        StandaloneAttractorView(int w, int h);
        virtual ~StandaloneAttractorView();
        
        void randomize();
        void reset();
        
        std::string formulaName;
    protected:
        virtual bool on_expose_event(GdkEventExpose* event);
    
    private:
        static const int FORMULA_COUNT = 2;
        static const int ITERATIONS = 10000;
        
        Formula *formula;
        SimpleGenerator *generator;
    };
}

#endif
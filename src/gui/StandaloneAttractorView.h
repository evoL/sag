#ifndef SAG_STANDALONEATTRACTORVIEW_H
#define SAG_STANDALONEATTRACTORVIEW_H

#include "gui/AttractorView.h"
#include "generation/SimpleGenerator.h"
#include "formulas/Formula.h"
#include <string>

namespace sag {
    /**
     * @brief Displays an attractor using an internal generator and renderer.
     */
    class StandaloneAttractorView : public AttractorView {
    public:
        /**
         * @brief Constructs a view.
         *
         * @param w Width of the view.
         * @param h Height of the view.
         * @param evts Events to respond to.
         */
        StandaloneAttractorView(int w, int h, Events evts = NO_EVENT);
        virtual ~StandaloneAttractorView();
        
        /**
         * @param Randomizes the displayed attractor.
         */
        void randomize();
        
        /**
         * @param Randomizes the displayed attractor and displays it.
         */
        void reset();
        
        
        /**
         * @brief Returns the Formula that's being used.
         *
         * @returns Pointer to the formula.
         */
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

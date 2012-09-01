#ifndef SAG_ATTRACTOREDITOR_H
#define SAG_ATTRACTOREDITOR_H

#include "gui/AttractorView.h"
#include "rendering/PixbufRenderer.h"
#include <thread>
#include <atomic>
#include <glibmm/dispatcher.h>

namespace sag {
    class AttractorEditor : public AttractorView {
    public:        
        AttractorEditor(PixbufRenderer &r);
        virtual ~AttractorEditor() {}
        
        void start();
        void stop();
        
        Glib::Dispatcher onTick;
    private:
        void redraw();
        void invalidate();

        std::thread refresher;
        std::atomic<bool> drawing;
    };
}

#endif
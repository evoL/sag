#include "gui/AttractorEditor.h"

#if defined(HAS_BOOST) && THREAD_NAMESPACE == boost
#  include <boost/chrono.hpp>
#else
#  include <chrono>
#endif

namespace sag {
    AttractorEditor::AttractorEditor(PixbufRenderer &r):
        AttractorView(r, AttractorView::ALL_EVENTS),
        drawing(false)
    {
        onTick.connect(sigc::mem_fun(*this, &AttractorEditor::invalidate));
    }
    
    void AttractorEditor::start() {
        if (drawing) return;
        
        drawing = true;
        refresher = THREAD_NAMESPACE::thread(&AttractorEditor::redraw, this);
    }
    
    void AttractorEditor::stop() {
        if (!drawing) return;
        
        drawing = false;
        if (refresher.joinable()) refresher.join();
    }
    
    void AttractorEditor::redraw() {
        while (drawing) {
            renderer->render();
            onTick();
            THREAD_NAMESPACE::this_thread::sleep_for(THREAD_NAMESPACE::chrono::milliseconds(16));
        }
    }
    
    void AttractorEditor::invalidate() {
        auto window = get_window();
        if (window) window->invalidate(false);
    }
}

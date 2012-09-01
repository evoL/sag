#include "gui/AttractorEditor.h"

#include <chrono>

namespace sag {
    AttractorEditor::AttractorEditor(PixbufRenderer &r):
        AttractorView(r, AttractorView::ALL_EVENTS)
    {
        onTick.connect(sigc::mem_fun(*this, &AttractorEditor::invalidate));
    }
    
    void AttractorEditor::start() {
        drawing = true;
        refresher = std::thread(&AttractorEditor::redraw, this);
    }
    
    void AttractorEditor::stop() {
        drawing = false;
        if (refresher.joinable()) refresher.join();
    }
    
    void AttractorEditor::redraw() {
        while (drawing) {
            renderer->render();
            onTick();
            std::this_thread::sleep_for(std::chrono::milliseconds(16));
        }
    }
    
    void AttractorEditor::invalidate() {
        auto window = get_window();
        if (window) window->invalidate(false);
    }
}

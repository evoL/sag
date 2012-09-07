#ifndef SAG_ATTRACTOREDITOR_H
#define SAG_ATTRACTOREDITOR_H

#include "gui/AttractorView.h"
#include "rendering/PixbufRenderer.h"
#include <thread>
#include <atomic>
#include <glibmm/dispatcher.h>

namespace sag {
    /**
     * @brief Displays an attractor and refreshes it quite often.
     */
    class AttractorEditor : public AttractorView {
    public:
        /**
         * @brief Constructs the object.
         *
         * @param r The renderer.
         */
        AttractorEditor(PixbufRenderer &r);
        virtual ~AttractorEditor() {} ///< The destructor.
        
        /**
         * @brief Starts refreshing the view.
         */
        void start();
        
        /**
         * @brief Stops refreshing the view.
         */
        void stop();
        
        /**
         * @brief Checks whether the view is refreshing.
         *
         * @returns True or false.
         */
        inline bool isRunning() { return drawing; }
        
        Glib::Dispatcher onTick;
    private:
        void redraw();
        void invalidate();

        std::thread refresher;
        std::atomic<bool> drawing;
    };
}

#endif
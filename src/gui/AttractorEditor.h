#ifndef SAG_ATTRACTOREDITOR_H
#define SAG_ATTRACTOREDITOR_H

#include "gui/AttractorView.h"
#include "rendering/PixbufRenderer.h"
#include <glibmm/dispatcher.h>

#if defined(HAS_BOOST) && THREAD_NAMESPACE == boost
#  include <boost/thread.hpp>
#else
#  include <thread>
#endif

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

        THREAD_NAMESPACE::thread refresher;
        bool drawing;
    };
}

#endif
#ifndef SAG_SINGLE_THREADED_GENERATOR_H
#define SAG_SINGLE_THREADED_GENERATOR_H

#include "generation/Generator.h"
#include "utils/Particle.h"
#include <vector>
#include <string>

#if defined(HAS_BOOST) && THREAD_NAMESPACE == boost
#  include <boost/thread.hpp>
#else
#  include <thread>
#endif

namespace sag {
    /**
     * @brief A Generator that works on a separate thread.
     */
	class SingleThreadedGenerator : public Generator {
	public:
        SingleThreadedGenerator(Formula& f, Renderer& r, int iter, bool if3D=false): Generator(f, r, iter, if3D) {}
		virtual ~SingleThreadedGenerator();
		
		std::string serialize() const;

		void run();
        
	private:
        THREAD_NAMESPACE::thread thread;
        
		void iterate(std::vector<Particle> v);
	};
}

#endif

#ifndef NO_THREADED_GENERATOR

#ifndef SAG_THREADED_GENERATOR_H
#define SAG_THREADED_GENERATOR_H

#include "generation/Generator.h"
#include <vector>

#if defined(HAS_BOOST) && THREAD_NAMESPACE == boost
#  include <boost/thread.hpp>
#else
#  include <thread>
#endif

namespace sag {
    /**
     * @brief A Generator that creates a thread for every particle that exists at the same time.
     */
	class ThreadedGenerator : public Generator {
	public:
        ThreadedGenerator(Formula& f, Renderer& r, int iter, bool if3D=false): Generator(f, r, iter, if3D) {}
		~ThreadedGenerator();

		void run();
	
	private:
		std::vector<THREAD_NAMESPACE::thread> threads;
		THREAD_NAMESPACE::thread threadController;

		void iterate(Particle &p, int n);
		
		void controlThreads();
	};
}

#endif

#endif

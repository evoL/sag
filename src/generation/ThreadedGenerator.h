#ifndef NO_THREADED_GENERATOR

#ifndef SAG_THREADED_GENERATOR_H
#define SAG_THREADED_GENERATOR_H

#include "generation/Generator.h"
#include <vector>
#include <thread>

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
		std::vector<std::thread> threads;
		std::thread threadController;

		void iterate(Particle &p, int n);
		
		void controlThreads();
	};
}

#endif

#endif

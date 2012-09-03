#ifndef SAG_SINGLE_THREADED_GENERATOR_H
#define SAG_SINGLE_THREADED_GENERATOR_H

#include "generation/Generator.h"
#include <vector>
#include <thread>
#include <string>
#include "utils/Particle.h"

namespace sag {
	class SingleThreadedGenerator : public Generator {
	public:
        SingleThreadedGenerator(Formula& f, Renderer& r, int iter, bool if3D=false): Generator(f, r, iter, if3D) {}
		virtual ~SingleThreadedGenerator();
		
		std::string serialize() const;

		void run();
        
	private:
        std::thread thread;
        
		void iterate(std::vector<Particle> v);
	};
}

#endif

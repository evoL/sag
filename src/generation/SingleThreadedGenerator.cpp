#include "generation/SingleThreadedGenerator.h"
#include <sstream> 


namespace sag {
    SingleThreadedGenerator::~SingleThreadedGenerator() {
        thread.join();
    }
    
	std::string SingleThreadedGenerator::serialize() const {
		std::stringstream ss;
		ss << "<generator>" << std::endl;
		ss << "<class>SingleThreadedGenerator</class>" << std::endl;
		ss << "<particleCount>" << particleCount << "</particleCount>" << std::endl;
		ss << "<iterations>" << iterations << "</iterations>" << std::endl;
		ss << "</generator>" << std::endl;
		
		return ss.str();
	}
	
	void SingleThreadedGenerator::run() {
        running = true;
		renderer->startReceiving();
		
		std::vector<Particle> initials;
		initials.resize(particleCount);
        
        // The initial point is always the starting point
        initials[0] = formula->getStartPoint();
        sendParticle(initials[0]);
        
        // The rest are random
		for (int i=1; i<particleCount; i++) {
			initials[i] = bounds.getRandomVector(if3D);
			sendParticle(initials[i]);
		}
		
		thread = std::thread(&SingleThreadedGenerator::iterate, this, initials);
	}
	
	void SingleThreadedGenerator::iterate(std::vector<Particle> v) {
		int i = iterations;
        while (running && ((iterations == UNLIMITED_ITERATIONS) || (i >= 0))) {
            for (auto it = v.begin(); it < v.end(); it++) {
				it->moveTo( formula->step(it->getPosition()) );
				sendParticle(*it);
				if (!running) break;
			}
            --i;
        }
        
        running = false;
        renderer->finishReceiving();
	}
}

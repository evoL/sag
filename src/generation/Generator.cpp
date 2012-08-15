#include <vector>
#include "rendering/Renderer.h"
#include "utils/Bounds.h"
#include "utils/Vector.h"
#include "generation/Generator.h"

namespace sag {
	Generator::Generator(Formula& f, Renderer& r, int pc, bool if3D): formula(&f), particleCount(pc), if3D(if3D), renderer(&r) {
        formula->prepare();
        
		setBounds();
        
		renderer->setBounds(bounds);
		renderer->setParticleCount(pc);
	}

	void Generator::sendParticle(Vector<number>& p) {
		renderer->enqueueParticle(p);
	}

	void Generator::setBounds() {
		std::vector<Vector<number>> particles;

		particles.resize(ITERS);
//		particles[0] = Bounds<number>(0.5).getRandomVector(if3D);
        particles[0] = formula->getStartPoint();

		for (int i=1; i<ITERS; i++)
			particles[i] = formula->step(particles[i-1]);

		bounds = Bounds<number>(particles);
	}
}

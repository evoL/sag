#include <vector>
#include <cmath>
#include "utils/types.h"
#include "utils/Random.h"
#include "utils/Vector.h"
#include "utils/Bounds.h"
#include "formulas/Formula.h"

namespace sag {
    void Formula::prepare() {
        if (parameters.empty()) randomParameters();
    }
    
	void Formula::randomParameters() {
        int pc = paramCount();
        parameters.resize(pc);
        
		do {
			for (int i=0; i < pc; i++)
				parameters[i] = Random<number>::get().inRange(getDistribution()->getRange(i));

		} while (!verifyParams(parameters));
	}

	bool Formula::verifyParams(const std::vector<number>& params) {
		// Detection bases on inspection the behavior of two nearby particles over time.

		Bounds<number> bounds(0.5);

		// Here are the particles:

//		Vector<number> v1 = bounds.getRandomVector(is3D());
        Vector<number> v1 = startPoint;

		Vector<number> ve(v1.x + Random<number>::get().inRange(-0.5, 0.5) / 1000,
						  v1.y + Random<number>::get().inRange(-0.5, 0.5) / 1000,
						  (is3D()) ? v1.z + Random<number>::get().inRange(-0.5, 0.5) / 1000 : 0);

		// We measure first the distance between them.

		Vector<number> d(v1.x - ve.x, v1.y - ve.y, v1.z - ve.z);
		number startdistance = sqrt(d.x*d.x + d.y*d.y);
		number distance;

		// These are boundaries of system in which the particles are.

		Vector<number> vmin(1e32, 1e32, 1e32);
		Vector<number> vmax(-1e32, -1e32, -1e32);

		// The Lyapunov exponent - we'll be calculating this.

		number lyapunov = 0;

		Vector<number> p, ep;
		for (int i = MAXITER; i>=0; i--) {
			// Move the first particle
			p = step(v1, params);

			// Enlarge boundaries if needed
			if (p.x < vmin.x) vmin.x = p.x;
			if (p.y < vmin.y) vmin.y = p.y;
			if (p.z < vmin.z) vmin.z = p.z;
			if (p.x > vmax.x) vmax.x = p.x;
			if (p.y > vmax.y) vmax.y = p.y;
			if (p.z > vmax.z) vmax.z = p.z;

			//Discard if the system blows up to the universe
			if ((vmin.x < -1e10) || (vmin.y < -1e10) ||
				(vmax.x > 1e10) || (vmax.y > 1e10) ||
                (is3D() && (vmax.z > 1e10 || vmin.z < -1e10)))
				return false;

			//Calculate how far the particle moved and discard if it's too slow
			d.x = p.x - v1.x;
			d.y = p.y - v1.y;
			d.z = p.z - v1.z;
			if ((fabs(d.x) < 1e-10) && (fabs(d.y) < 1e-10) && (fabs(d.z) < 1e-10))
				return false;

			// Start doing things after 1000 iterations of warmup
			if (i < MAXITER-1000) {
				// Move the second particle
				ep = step(ve, params);

				// Calculate the distance
				d.x = p.x - ep.x;
				d.y = p.y - ep.y;
				d.z = p.z - ep.z;
				distance = sqrt(d.x*d.x + d.y*d.y + d.z*d.z);


				// Calculate the Lyapunov exponent
				lyapunov += log(fabs(distance / startdistance));

				// Adjust the distance of the second particle to the first distance
				ve.x = p.x + startdistance * d.x / distance;
				ve.y = p.y + startdistance * d.y / distance;
				ve.z = p.z + startdistance * d.z / distance;
			}

			// Update the particle position
			v1.x = p.x;
			v1.y = p.y;
			v1.z = p.z;
		}

		// The Lyapunov exponent determines the behavior of the attractor.
		// If it's between -10 and 10 then the attractor is neutrally stable.
		// If it's negative then it's periodic.
		// Otherwise it's chaotic, therefore nice.
		//
		// The condition below simplifies everything.
		return (lyapunov >= 10);
	}
    
    Vector<number> Formula::step(const Vector<number>& prev) {
        return step(prev, parameters);
    }
}

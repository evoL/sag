#ifndef SAG_GENERATOR_H
#define SAG_GENERATOR_H

#include "utils/types.h"
#include "formulas/Formula.h"
#include "rendering/Renderer.h"
#include "utils/Bounds.h"

namespace sag {
	class Generator {
	public:
		virtual ~Generator();
		virtual void run();
	protected:
		Formula *formula;
		Renderer *renderer;
		Bounds<number> *bounds;
	};
}

#endif

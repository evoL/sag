#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include <string>
#include <formulas/Formula.h>
#include <generation/Generator.h>
#include <rendering/Renderer.h>

namespace sag {
	std::string serialize(Generator& g, Formula& f, Renderer& r, std::string name);
	
	void unserialize(std::string rawXML, Generator& g, Formula& f, Renderer& r);
}

#endif
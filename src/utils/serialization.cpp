#include "utils/serialization.h"
#include <sstream>

namespace sag {
	std::string serialize(Generator& g, Formula& f, Renderer& r, std::string name) {
		std::string bounds = g.getBounds().serialize();
		std::string generator = g.serialize();
		std::string formula = f.serialize();
		std::string renderer = r.serialize();
		bool is3D = g.is3D();
		
		
		std::stringstream ss;
		ss << "<?xml version=\"1.0\" encoding=\"utf-8\"?>" << std::endl;
		ss << "<settings>" << std::endl;
		ss << "<name>" << name << "</name>" << std::endl;
		ss << "<is3D>" << (is3D?"true":"false") << "</is3D>" << std::endl;
		ss << bounds;
		ss << generator;
		ss << renderer;
		ss << "</settings>" << std::endl;
		
		return ss.str();
	}
	
	//void unserialize(std::string rawXML, Generator& g, Formula& f, Renderer& r);
}

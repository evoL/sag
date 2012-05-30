#include "Formula.h"

namespace sag {
    /*Formula::Formula() {};
    
    Formula::Formula(int count, number params[]) { 
        setParameters(count, params);
    }
    
    Formula::Formula(std::vector<number> params) {
        setParameters(params);
    }*/
    
    void Formula::setParameters(int count, number params[]) {
        std::vector<number> v;
        v.reserve(count);
        
        for (int i=0; i<count; i++) {
            v.push_back(params[i]);
        }
        
        setParameters(v);
    }
    
    void Formula::setParameters(std::vector<number>& params) {        
        int size = params.size();
        
        if (size < paramCount)
            throw ParameterLengthException("Not enough parameters");
        
        parameters = params;
        parameters.resize(paramCount);
    }
    
    void Formula::prepare() {
        // Every formula is a good formula
        
        // TODO: correct the above assumption
    }
}
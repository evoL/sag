#include <iostream>
#include <string>

#include "generation/Particle.h"

using namespace std;
using namespace sag;

int main() {
    Particle p(1,2);

    cout << (string) p << endl;
    
    p.position.add(-5, 5);
    cout << "With added [-5, 5]: " << (string) p << endl;
    
    return 0;
}
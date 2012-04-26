#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

#include "generation/Particle.h"

using namespace std;
using namespace sag;

int main() {
    srand(time(NULL));
    
    Bounds b(-10,10, -10, 10);
    
    Particle p = Particle::getRandom(b);

    cout << (string) p << endl;
    
    p.position.add(-5, 5);
    cout << "With added [-5, 5]: " << (string) p << endl;
    
    return 0;
}
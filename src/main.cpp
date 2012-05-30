#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

#include "generation/Particle.h"
#include "formulas/Quadratic.h"

using namespace std;
using namespace sag;

int main() {
    srand(time(NULL));
    
    Bounds b(-2, 2, -2, 2);
    
    Particle p = Particle::getRandom(b);
    cout << "Initial " << (string) p << endl;
    Vector pos = p.position;
    
    number params[] = {
        -0.8453104826115183,
        -0.9475605238386438,
        -0.4382520433507433,
        0.4106006668573623,
        -0.28562839597833234,
        1.5965588703719562,
        0.6026147275565434,
        0.8036958156097804,
        -1.4690112404625988,
        -1.1582145880802814,
        -0.1819068407177551,
        1.205723356744108
    };
    
    Quadratic f;
    f.setParameters(12, params);
    
    cout << "Applying Quadratic 5 times:" << endl;
    for (int i=1; i<=5; i++) {
        pos = f.step(pos);
        cout << "Step " << i << ": " << (string) pos << endl;
    }
        
    return 0;
}
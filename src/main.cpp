#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

#include <gtk/gtk.h>

#include "generation/SimpleGenerator.h"
#include "formulas/Quadratic.h"
#include "imaging/PixbufImage.h"

using namespace std;
using namespace sag;

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    
    ///////////////////////////////
    
    Bounds b(-2, 2, -2, 2);
    
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
    
    SimpleGenerator gen;
    gen.setFormula(f);
    gen.setBounds(b);
    
    cout << "Applying Quadratic 5 times to 1 particle:" << endl;
    for (int i=1; i<=5; i++) {
        gen.step();
        cout << "Step " << i << ": " << (string) const_cast<Vector&>((gen.getParticles())[0].position) << endl;
    }
    
    // Image saving test
    
    PixbufImage img(256, 256);
    img.toFile("test.png");

    return 0;
}
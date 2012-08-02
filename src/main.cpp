#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

#include <gtk/gtk.h>

#include "generation/SimpleGenerator.h"
#include "generation/Grid.h"
#include "formulas/Quadratic.h"
#include "imaging/PixbufImage.h"

using namespace std;
using namespace sag;

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    
    ///////////////////////////////
    
    Bounds<number> b(-2, 2, -2, 2);
    Bounds<int> b2(0, 512, 0, 512);
    
    Vector<number> v1 = b.getRandomVector();
    cout << "Random vector from bounds b1: " << (string) v1 << endl;
    
    Vector<int> v2 = b.convert(v1, b2);
    cout << "Converted to bounds b2: " << (string) v2 << endl;
    
    cout << endl;
    
    ///////////////////////////////
    
    number params[] = {
        0.205589,
        -0.02852,
        -0.686951,
        0.20502,
        0.537249,
        1.549,
        -0.244359,
        0.540024,
        -0.513432,
        0.147886,
        -1.39347, 
        -0.15918
    };
    
    Quadratic f;
    f.setParameters(12, params);
    
    SimpleGenerator gen;
    gen.setFormula(f);
    
    Grid grid(512, 512);
        
    for (int i=0; i<200000; i++) {
        gen.step();
        Vector<int> cnv = b.convert(const_cast<Vector<number>&>(gen.getParticles()[0].position), grid.size);
        grid.add(cnv.x, cnv.y, 3);
    }
    
    /////////////////////////////////////
    
    PixbufImage img(512, 512);
    img.drawGrid(grid);
    img.toFile("test.png");
    
    cout << endl << "Expect an image in test.png..." << endl;

    return 0;
}
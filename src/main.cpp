#include <iostream>
#include <gtkmm.h>
#include "imaging/PixbufImage.h"

using namespace std;

int main(int argc, char *argv[]) {
    Gtk::Main app(argc, argv);
    
    sag::PixbufImage pb(512, 512);
    pb.setPixel(128, 128, 0, 128, 255);
    pb.toFile("test.png");
    
    Gtk::Window window;
    app.run(window);
	return 0;
}

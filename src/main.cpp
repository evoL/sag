#include <iostream>
#include <gtkmm.h>
#include "imaging/PixbufImage.h"

using namespace std;

class ImageWindow : public Gtk::Window {
public:
    ImageWindow(sag::PixbufImage& pb): img(pb.getPixbuf()) {
        set_default_size(pb.getWidth(), pb.getHeight());
        
        add(img);
        img.show();
    }
    virtual ~ImageWindow() {}
    
private:
    Gtk::Image img;
};

int main(int argc, char *argv[]) {
    Gtk::Main app(argc, argv);
    
    sag::PixbufImage pb(512, 512);
    pb.setPixel(128, 128, 255, 255, 255);
    ImageWindow window(pb);
    
    pb.setPixel(192, 192, 255, 255, 0);
    
    app.run(window);
	return 0;
}

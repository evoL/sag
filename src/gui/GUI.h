#ifndef SAG_GUI_H
#define SAG_GUI_H

#include <gtkmm/window.h>
#include <gtkmm/table.h>
#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/button.h>
#include <vector>

#include "gui/StandaloneAttractorView.h"

namespace sag {
    class GUI : public Gtk::Window {
    public:
        GUI();
        virtual ~GUI() {}
        
        void showChooser();
        void showEditor();
        
    protected:
    private:
        static const int WIDTH = 900;
        static const int HEIGHT = 600;
        
        class ChooserView : public Gtk::HBox {
        public:
            ChooserView(GUI* gui);
            virtual ~ChooserView();
        private:
            static const int ROWS = 3;
            static const int COLS = 3;
            
            GUI* gui;
            
            Gtk::Table table;
            Gtk::VBox panel;
            Gtk::Label title;
            Gtk::Button randomizeButton, loadButton;
            std::vector<StandaloneAttractorView*> views;
            
            void randomizeAttractors();
            void loadAttractor();
            bool onImageClick(GdkEventButton* evt, StandaloneAttractorView* view);
        };
        
        class EditorView : public Gtk::HBox {
        public:
            EditorView(GUI* gui);
            virtual ~EditorView() {}
            
//            void setFormula(Formula* f);
        private:
            GUI* gui;
            
            Formula *formula;
            Generator *generator;
            PixbufRenderer renderer;
            
            AttractorView view;
            Gtk::VBox panel;
            Gtk::Label title;
            Gtk::Button returnButton;
        };
        
        ChooserView chooser;
        EditorView editor;
    };
}

#endif
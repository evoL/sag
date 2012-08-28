#ifndef SAG_GUI_H
#define SAG_GUI_H

#include <gtkmm.h>
#include <vector>
#include "gui/StandaloneAttractorView.h"

namespace sag {
    class GUI : public Gtk::Window {
    public:
        GUI();
        virtual ~GUI() {}
        
        void showChooser();
        void showEditor();
        void showEditor(const Formula* f);
        
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
            virtual ~EditorView();
            
            void setFormula(const Formula* f);
            void updateView();
        private:
            static const int MAX_PARTICLECOUNT = 1000;
            
            class FormulaColumns : public Gtk::TreeModelColumnRecord {
            public:
                FormulaColumns() { add(formula); }
                Gtk::TreeModelColumn<Glib::ustring> formula;
            };
            
            class ParameterColumns : public Gtk::TreeModelColumnRecord {
            public:
                ParameterColumns() { add(param); }
                Gtk::TreeModelColumn<number> param;
            };
            
            GUI* gui;
            
            Formula *formula;
            Generator *generator;
            PixbufRenderer renderer;
            
            AttractorView view;
            Gtk::VBox panel;
            Gtk::Label title;
            Gtk::Button returnButton;
            Gtk::Expander shapeExpander, appearanceExpander;
            Gtk::Table shapeTable, appearanceTable;
            
            Gtk::Label formulaLabel, particleCountLabel;
            Gtk::ComboBox formulaBox;
            FormulaColumns formulaColumns;
            Glib::RefPtr<Gtk::ListStore> formulaModel;
            Gtk::Adjustment particleCountAdjustment;
            Gtk::SpinButton particleCountEntry;
            Gtk::TreeView parameterView;
            ParameterColumns parameterColumns;
            
            void createGenerator();
            void createFormulaModel();
        };
        
        ChooserView chooser;
        EditorView editor;
    };
}

#endif
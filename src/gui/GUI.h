#ifndef SAG_GUI_H
#define SAG_GUI_H

#include <gtkmm.h>
#include <vector>
#include "utils/Range.h"
#include "gui/StandaloneAttractorView.h"
#include "gui/AttractorEditor.h"
#include "generation/Generator.h"
#include "formulas/Formula.h"
#include "rendering/PixbufRenderer.h"

namespace sag {
    class GUI : public Gtk::Window {
    public:
        struct CustomFormula {
            std::string name;
            std::vector<std::string> formulas;
            std::vector<Range<number>> distribution;
        };
        
        GUI();
        virtual ~GUI() {}
        
        void showChooser();
        void showEditor();
        void showEditor(const Formula* f);
        
    protected:
    private:
        static const int WIDTH = 900;
        static const int HEIGHT = 600;
        
        class FormulaEditor : public Gtk::Window {
        public:
            FormulaEditor();
            virtual ~FormulaEditor() {}
            
            void setCustomFormula(CustomFormula& f);
            
            inline sigc::signal<void, CustomFormula&> signal_saved_data() {
                return signalSavedData;
            }
            inline sigc::signal<void> signal_canceled() {
                return signalCanceled;
            }
            
        protected:
            bool on_window_delete_event(GdkEventAny*);
            
        private:
            class DistributionColumns : public Gtk::TreeModelColumnRecord {
            public:
                DistributionColumns() { add(index); add(min); add(max); }
                Gtk::TreeModelColumn<int> index;
                Gtk::TreeModelColumn<number> min, max;
            };
            
            sigc::signal<void, CustomFormula&> signalSavedData;
            sigc::signal<void> signalCanceled;
            
            Gtk::VBox content;
            Gtk::Table texts;
            Gtk::Label nameLabel, xLabel, yLabel, countLabel;
            Gtk::Entry nameEntry, xEntry, yEntry;
            Gtk::SpinButton countEntry;
            Gtk::Adjustment countAdjustment;
            
            DistributionColumns dstrColumns;
            Gtk::ScrolledWindow dstrScrollWindow;
            Glib::RefPtr<Gtk::ListStore> dstrModel;
            Gtk::TreeView dstrView;
            
            Gtk::HButtonBox actions;
            Gtk::Button cancelButton, okButton;
            
            void onSave();
            void onCancel();
            void onCountChanged();
        };
        
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
            
            void editFormula(const Formula* f);
            void startUpdating();
            void stopUpdating();
        private:
            class FormulaColumns : public Gtk::TreeModelColumnRecord {
            public:
                FormulaColumns() { add(formula); }
                Gtk::TreeModelColumn<Glib::ustring> formula;
            };
            
            class ParameterColumns : public Gtk::TreeModelColumnRecord {
            public:
                ParameterColumns() { add(param); add(adjustment); }
                Gtk::TreeModelColumn<number> param;
                Gtk::TreeModelColumn<Gtk::Adjustment*> adjustment;
            };
            
            bool automatedChange;
            
            GUI* gui;
            
            Formula *formula;
            Generator *generator;
            PixbufRenderer renderer;
            
            GUI::FormulaEditor editor;
            GUI::CustomFormula customFormula;
            
            AttractorEditor view;
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
            
            Gtk::Button editFormulaButton;
            
            Gtk::ScrolledWindow parameterViewWindow;
            Gtk::TreeView parameterView;
            ParameterColumns parameterColumns;
            Gtk::CellRendererSpin parameterRenderer;
            Gtk::TreeViewColumn parameterColumn;
            Glib::RefPtr<Gtk::ListStore> parameterModel;
            
            Gtk::Label iterationsLabel;
            Gtk::Adjustment iterationsAdjustment;
            Gtk::SpinButton iterationsEntry;
            Gtk::ToggleButton infiniteIterationsButton;
            
            Gtk::Adjustment ttlAdjustment;
            Gtk::Label ttlLabel;
            Gtk::SpinButton ttlEntry;
            Gtk::ToggleButton immortalParticleButton;
            
            Gtk::Label colorLabel;
            Gtk::ColorButton colorButton;
            
            Gtk::Adjustment colorShiftAdjustment;
            Gtk::Label colorShiftLabel;
            Gtk::HScale colorShiftScale;
            
            Gtk::HBox progressBox;
            Gtk::ProgressBar progress;
            Gtk::Button abortButton;

            void setFormula(Formula* Ref);
            
            void createGenerator();
            void createFormulaModel();
            void updateFormulaBox();
            void updateParameterModel();
            
            void onEditFormulaClick();
            
            void onUpdateCustomFormula(CustomFormula& cf);
            void onSetCustomFormula();
            
            void onChangeFormula();
            void onChangeParticleCount();
            void onChangeIterations();
            void onChangeTTL();
            
            void onChangeColor();
            void onChangeColorShift();
            
            void onProgress();
            void onAbortClick();
            
            void parameterColumnCellData(Gtk::CellRenderer* renderer, const Gtk::TreeModel::iterator& iter);
            void onParameterEditFinish(const Glib::ustring& path_string, const Glib::ustring& new_text);
        };
                
        ChooserView chooser;
        EditorView editor;
    };
}

#endif

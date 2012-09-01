#include "gui/GUI.h"

#include <algorithm>
#include <limits>
#include <sstream>
#include <gtkmm/messagedialog.h>
#include "formulas/all.h"

#ifdef NO_THREADED_GENERATOR

#include "generation/SingleThreadedGenerator.h"
#define THREADED_GENERATOR_IMPL SingleThreadedGenerator

#else

#include "generation/ThreadedGenerator.h"
#define THREADED_GENERATOR_IMPL ThreadedGenerator

#endif

namespace sag {
    GUI::GUI(): chooser(this), editor(this) {
        set_title("Pierdut HD 3D");
        
        Gdk::Geometry hints;
        hints.min_width = WIDTH;
        hints.min_height = HEIGHT;
        hints.max_width = WIDTH;
        hints.max_height = HEIGHT;
        set_geometry_hints(*this, hints, Gdk::HINT_MIN_SIZE | Gdk::HINT_MAX_SIZE);
        set_default_size(WIDTH, HEIGHT);
        set_resizable(false);
        
        add(chooser);
        
        chooser.show();
    }
    
    void GUI::showChooser() {
        remove();
        add(chooser);
        chooser.show();
    }
    
    void GUI::showEditor() {
        remove();
        add(editor);
        editor.updateView();
        editor.show();
    }
    
    void GUI::showEditor(const Formula* f) {
        editor.setFormula(f);
        showEditor();
    }
    
    ////////////////////////////////////////////////////////////////////
    
    GUI::ChooserView::ChooserView(GUI* gui):
        Gtk::HBox(false, 0),
        gui(gui),
        table(COLS, ROWS, true),
        panel(false, 0),
        views(COLS*ROWS)
    {
        // Table setup
        pack_start(table);
        
        int i = 0;
        int x, y;
        for (auto it = views.begin(); it < views.end(); it++) {
            x = i / ROWS;
            y = i % ROWS;
            
            (*it) = new StandaloneAttractorView(HEIGHT/COLS, HEIGHT/ROWS, AttractorView::ALL_EVENTS);
            (*it)->signal_button_press_event().connect(sigc::bind<StandaloneAttractorView*>(sigc::mem_fun(*this, &ChooserView::onImageClick), *it));
            table.attach(**it, x, x+1, y, y+1);
            
            i++;
        }
        
        // Panel setup
        panel.set_size_request(WIDTH-HEIGHT, -1);
        pack_end(panel, Gtk::PACK_SHRINK);
        
        title.set_markup("<span size=\"large\" weight=\"bold\">Choose an attractor</span>");
        title.set_padding(10, 10);
        panel.pack_start(title, Gtk::PACK_SHRINK);
        
        randomizeButton.set_label("Generate more");
        randomizeButton.set_size_request(-1, 80);
        randomizeButton.set_border_width(5);
        randomizeButton.signal_clicked().connect(sigc::mem_fun(*this, &ChooserView::randomizeAttractors));
        panel.pack_start(randomizeButton, Gtk::PACK_SHRINK);
        
        loadButton.set_label("Load from file");
        loadButton.set_size_request(-1, 80);
        loadButton.set_border_width(5);
        loadButton.signal_clicked().connect(sigc::mem_fun(*this, &ChooserView::loadAttractor));
        panel.pack_start(loadButton, Gtk::PACK_SHRINK);
        
        show_all_children();
    }
    
    GUI::ChooserView::~ChooserView() {
        for (auto it = views.begin(); it < views.end(); it++) {
            table.remove(**it);
            delete *it;
            *it = nullptr;
        }
    }
    
    void GUI::ChooserView::randomizeAttractors() {
        for (auto it = views.begin(); it < views.end(); it++) {
            (**it).reset();
        }
        table.get_window()->invalidate(true);
    }
    
    void GUI::ChooserView::loadAttractor() {
        Gtk::MessageDialog dialog(*gui, "Not implemented yet");
        dialog.set_secondary_text("Please wait for the developers or implement this yourself. :)");
        
        dialog.run();
    }
    
    bool GUI::ChooserView::onImageClick(GdkEventButton* evt, StandaloneAttractorView* view) {
        view->setHovered(false);
        
        const Formula *f = view->getFormula();
//
//        Gtk::MessageDialog dialog(*gui, "You've clicked a " + f->name());
//        
//        std::stringstream ss;
//        ss.precision(18);
//        ss << "AttraGen-compatible data:" << std::endl << std::endl;
//        ss << f->name() << std::endl
//           << f->getStartPoint().x << std::endl
//           << f->getStartPoint().y << std::endl;
//        
//        for (auto it = f->getParameters().begin(); it < f->getParameters().end(); it++) {
//            ss << *it << std::endl;
//        }
//        
//        dialog.set_secondary_text(ss.str());
//        dialog.run();
        
        
        gui->showEditor(f);
        
        return true;
    }
    
    ////////////////////////////////////////////////////////////////////
    
    GUI::EditorView::EditorView(GUI* gui):
        gui(gui),
        formula(nullptr),
        generator(nullptr),
        renderer(HEIGHT, HEIGHT),
        view(renderer),
        shapeTable(3, 3, false),
        appearanceTable(3, 3, false),
        particleCountAdjustment(1, 1, std::numeric_limits<int>::max()),
        iterationsAdjustment(1000000, 1, std::numeric_limits<int>::max(), 100, 10000)
    {
        pack_start(view);
        
        panel.set_size_request(WIDTH-HEIGHT, -1);
        pack_end(panel, Gtk::PACK_SHRINK);
        
        title.set_markup("<span size=\"large\" weight=\"bold\">Customize your attractor</span>");
        title.set_padding(10, 10);
        panel.pack_start(title, Gtk::PACK_SHRINK);
        
        //////////////////////////////////////////////////////
        
        shapeExpander.set_label("Shape");
        shapeExpander.set_expanded(true);
        panel.pack_start(shapeExpander, Gtk::PACK_SHRINK);
        
        shapeTable.set_border_width(5);
        shapeTable.set_row_spacings(5);
        shapeExpander.add(shapeTable);
        
        formulaLabel.set_text("Formula");
        formulaLabel.set_alignment(Gtk::ALIGN_LEFT);
        shapeTable.attach(formulaLabel, 0, 1, 0, 1);
        
        createFormulaModel();
        formulaBox.set_model(formulaModel);
        formulaBox.pack_start(formulaColumns.formula);
        shapeTable.attach(formulaBox, 1, 3, 0, 1);
        
        particleCountLabel.set_text("Particle count");
        particleCountLabel.set_alignment(Gtk::ALIGN_LEFT);
        shapeTable.attach(particleCountLabel, 0, 2, 1, 2);
        
        particleCountEntry.set_adjustment(particleCountAdjustment);
        shapeTable.attach(particleCountEntry, 2, 3, 1, 2);
        
        parameterViewWindow.set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_AUTOMATIC);
        parameterViewWindow.set_size_request(-1, 110);
        shapeTable.attach(parameterViewWindow, 0, 3, 2, 3);
        
        parameterModel = Gtk::ListStore::create(parameterColumns);
        parameterView.set_model(parameterModel);
        parameterView.append_column("Parameters", parameterColumns.param);
        parameterViewWindow.add(parameterView);
        
        //////////////////////////////////////////////////////
        
        appearanceExpander.set_label("Appearance");
        appearanceExpander.set_expanded(true);
        panel.pack_start(appearanceExpander, Gtk::PACK_SHRINK); 
        
        appearanceTable.set_border_width(5);
        appearanceTable.set_row_spacings(5);
        appearanceExpander.add(appearanceTable);
        
        iterationsLabel.set_text("Iteration count");
        iterationsLabel.set_alignment(Gtk::ALIGN_LEFT);
        appearanceTable.attach(iterationsLabel, 0, 1, 0, 1);
        
        iterationsEntry.set_adjustment(iterationsAdjustment);
        appearanceTable.attach(iterationsEntry, 1, 2, 0, 1);
        
        infiniteIterationsButton.set_label("∞");
        appearanceTable.attach(infiniteIterationsButton, 2, 3, 0, 1);
        
        returnButton.set_label("Choose a different attractor");
        returnButton.set_border_width(5);
        returnButton.set_size_request(-1, 80);
        returnButton.signal_clicked().connect(sigc::mem_fun(*gui, &GUI::showChooser));
        panel.pack_end(returnButton, Gtk::PACK_SHRINK);
        
        show_all_children();
    }
    
    GUI::EditorView::~EditorView() {
        delete generator;
        generator = nullptr;
        delete formula;
        formula = nullptr;
    }
    
    void GUI::EditorView::setFormula(const Formula* f) {
        // Create a local copy of the formula
    	delete generator;
		generator = nullptr;
		delete formula;
		formula = nullptr;
        
        formula = f->clone();
        createGenerator();
        
        auto iterator = std::find(FORMULA_NAMES.begin(), FORMULA_NAMES.end(), f->name());
        formulaBox.set_active(iterator - FORMULA_NAMES.begin());
        
        updateParameterModel();
    }
    
    void GUI::EditorView::updateView() {        
        renderer.clear();
        generator->run();
		renderer.wait();
        renderer.render();
        
        auto window = view.get_window();
        if (window) window->invalidate(false);
    }
    
    void GUI::EditorView::createGenerator() {
        //generator = new SimpleGenerator(*formula, renderer, 1000000);
        generator = new THREADED_GENERATOR_IMPL(*formula, renderer, 1000000);
    }
    
    void GUI::EditorView::createFormulaModel() {
        formulaModel = Gtk::ListStore::create(formulaColumns);
        
        for (auto it = FORMULA_NAMES.begin(); it < FORMULA_NAMES.end(); it++) {
            Gtk::TreeModel::Row row = *(formulaModel->append());
            row[formulaColumns.formula] = *it;
        }
    }
    
    void GUI::EditorView::updateParameterModel() {
        for (auto it = formula->getParameters().begin(); it < formula->getParameters().end(); it++) {
            Gtk::TreeModel::Row row = (*parameterModel->append());
            row[parameterColumns.param] = *it;
        }
    }
}

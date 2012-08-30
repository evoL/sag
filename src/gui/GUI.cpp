#include "gui/GUI.h"

#include <algorithm>
#include <limits>
#include <sstream>
#include <gtkmm/messagedialog.h>
#include "formulas/all.h"

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
        editor.editFormula(f);
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
        automatedChange(false),
        gui(gui),
        formula(nullptr),
        generator(nullptr),
        renderer(HEIGHT, HEIGHT),
        view(renderer),
        shapeTable(3, 3, false),
        appearanceTable(3, 3, false),
        particleCountAdjustment(1, 1, std::numeric_limits<int>::max()),
        parameterAdjustment(0, std::numeric_limits<float>::min(), std::numeric_limits<float>::max(), 1e-6, 1e-3),
        iterationsAdjustment(10000, 1, std::numeric_limits<int>::max(), 100, 10000)
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
        formulaBox.signal_changed().connect(sigc::mem_fun(*this, &EditorView::onChangeFormula));
        shapeTable.attach(formulaBox, 1, 3, 0, 1);
        
        particleCountLabel.set_text("Particle count");
        particleCountLabel.set_alignment(Gtk::ALIGN_LEFT);
        shapeTable.attach(particleCountLabel, 0, 2, 1, 2);
        
        particleCountEntry.set_adjustment(particleCountAdjustment);
        particleCountEntry.set_numeric(true);
        particleCountEntry.signal_value_changed().connect(sigc::mem_fun(*this, &EditorView::onChangeParticleCount));
        shapeTable.attach(particleCountEntry, 2, 3, 1, 2);
        
        parameterViewWindow.set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_AUTOMATIC);
        parameterViewWindow.set_size_request(-1, 110);
        shapeTable.attach(parameterViewWindow, 0, 3, 2, 3);
        
        parameterModel = Gtk::ListStore::create(parameterColumns);
        parameterView.set_model(parameterModel);
        
        parameterColumn.set_title("Parameters");
        parameterColumn.pack_start(parameterRenderer);
        parameterColumn.set_cell_data_func(parameterRenderer, sigc::mem_fun(*this, &EditorView::parameterColumnCellData));
        parameterView.append_column(parameterColumn);
        
        parameterRenderer.property_adjustment() = &parameterAdjustment;
        parameterRenderer.property_editable() = true;
        parameterRenderer.property_digits() = 18;
        
        parameterRenderer.signal_editing_started().connect(sigc::mem_fun(*this, &EditorView::onParameterEditStart));
        parameterRenderer.signal_edited().connect(sigc::mem_fun(*this, &EditorView::onParameterEditFinish));
        
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
        iterationsEntry.set_numeric(true);
        iterationsEntry.signal_value_changed().connect(sigc::mem_fun(*this, &EditorView::onChangeIterations));
        appearanceTable.attach(iterationsEntry, 1, 2, 0, 1);
        
        infiniteIterationsButton.set_label("∞");
        infiniteIterationsButton.signal_toggled().connect(sigc::mem_fun(*this, &EditorView::onChangeIterations));
        appearanceTable.attach(infiniteIterationsButton, 2, 3, 0, 1);
        
        returnButton.set_label("Choose a different attractor");
        returnButton.set_border_width(5);
        returnButton.set_size_request(-1, 80);
        returnButton.signal_clicked().connect(sigc::mem_fun(*gui, &GUI::showChooser));
        panel.pack_end(returnButton, Gtk::PACK_SHRINK);
        
        show_all_children();
    }
    
    GUI::EditorView::~EditorView() {
        if (generator != nullptr) delete generator;
        if (formula != nullptr) delete formula;
    }
    
    void GUI::EditorView::editFormula(const Formula* f) {
        automatedChange = true;
        setFormula(f->clone());
        updateFormulaBox();
        automatedChange = false;
    }
    
    void GUI::EditorView::setFormula(Formula* f) {
        // Create a local copy of the formula
        if (generator != nullptr) delete generator;
        if (formula != nullptr) delete formula;
        
        formula = f;
        createGenerator();
        updateParameterModel();
    }
    
    void GUI::EditorView::updateView() {        
        renderer.clear();
        generator->run();
        renderer.render();
        
        auto window = view.get_window();
        if (window) window->invalidate(false);
    }
    
    void GUI::EditorView::createGenerator() {
        int iters = infiniteIterationsButton.get_active() ? Generator::UNLIMITED_ITERATIONS : iterationsEntry.get_value_as_int();
        
        generator = new SimpleGenerator(*formula, renderer, iters);
    }
    
    void GUI::EditorView::createFormulaModel() {
        formulaModel = Gtk::ListStore::create(formulaColumns);
        
        for (auto it = FORMULA_NAMES.begin(); it < FORMULA_NAMES.end(); it++) {
            Gtk::TreeModel::Row row = *(formulaModel->append());
            row[formulaColumns.formula] = *it;
        }
    }
    
    void GUI::EditorView::updateFormulaBox() {
        auto iterator = std::find(FORMULA_NAMES.begin(), FORMULA_NAMES.end(), formula->name());
        formulaBox.set_active(iterator - FORMULA_NAMES.begin());
    }
    
    void GUI::EditorView::updateParameterModel() {
        parameterModel->clear();
        int index = 0;
        for (auto it = formula->getParameters().begin(); it < formula->getParameters().end(); it++) {
            Gtk::TreeModel::Row row = (*parameterModel->append());
            row[parameterColumns.param] = *it;
            
            index++;
        }
    }
    
    void GUI::EditorView::onChangeFormula() {
        if (automatedChange) return;
        
        auto it = formulaBox.get_active();
        if (!it) return;
        
        auto row = *it;
        if (!row) return;
        
        Formula *f = createFormula(row.get_value(formulaColumns.formula));
        setFormula(f);
        updateView();
    }
    
    void GUI::EditorView::onChangeParticleCount() {
        generator->setParticleCount(particleCountEntry.get_value_as_int());
        updateView();
    }
    
    void GUI::EditorView::onChangeIterations() {
        if (generator != nullptr) delete generator;
        createGenerator();
        updateView();
    }
    
    void GUI::EditorView::parameterColumnCellData(Gtk::CellRenderer* renderer, const Gtk::TreeModel::iterator& iter) {
        if (!iter) return;
        
        Gtk::TreeModel::Row row = *iter;
        
        Glib::ustring result;
        std::stringstream ss;
        ss.precision(18);
        ss << row[parameterColumns.param];
        ss >> result;
        
        parameterRenderer.property_text() = result;
    }
    
    void GUI::EditorView::onParameterEditStart(Gtk::CellEditable* cell_editable, const Glib::ustring& path_string) {
//        Gtk::SpinButton* entry = dynamic_cast<Gtk::SpinButton*>(cell_editable);
//        
//        Gtk::TreePath path(path_string);
//        Gtk::TreeModel::iterator iter = parameterModel->get_iter(path);
//        if (!iter) return;
//        Gtk::TreeModel::Row row = *iter;
//        
//        entry->set_value(row[parameterColumns.param]);
    }
    
    void GUI::EditorView::onParameterEditFinish(const Glib::ustring& path_string, const Glib::ustring& new_text) {
        Gtk::TreePath path(path_string);
        
        number value = atof(new_text.c_str());
        
        // Validate the value
        int index = *(path.begin());
        auto range = formula->getDistribution().getRange(index);
        
        if (range.contains(value)) {
            // Update the field
            Gtk::TreeModel::iterator iter = parameterModel->get_iter(path);
            if (!iter) return;
            
            Gtk::TreeModel::Row row = *iter;
            row[parameterColumns.param] = value;
            
            // Update the parameter
            auto params = formula->getParameters();
            params[index] = value;
            Formula *f = createFormula(formula->name(), params);
            setFormula(f);
            updateView();
        } else {
            // Display an error
            std::stringstream ss;
            ss << "The value of this parameter must be between ";
            ss << range.min();
            ss << " and ";
            ss << range.max();
            ss << ".";
            
            Glib::ustring msg;
            ss >> msg;
            
            Gtk::MessageDialog dialog(*gui, msg, false, Gtk::MESSAGE_ERROR);
            dialog.run();
        }
    }
}
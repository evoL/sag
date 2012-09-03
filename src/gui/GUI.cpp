#include "gui/GUI.h"

#include <algorithm>
#include <limits>
#include <sstream>
#include <gtkmm/messagedialog.h>
#include "formulas/all.h"
#include "formulas/UserDefined.h"

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
        editor.stopUpdating();
        
        remove();
        add(chooser);
        chooser.show();
    }
    
    void GUI::showEditor() {
        remove();
        add(editor);
        editor.show();
        editor.startUpdating();
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
        iterationsAdjustment(1000000, 1, std::numeric_limits<int>::max(), 100, 10000)
    {
        editor.signal_saved_data().connect(sigc::mem_fun(*this, &EditorView::onUpdateCustomFormula));
        editor.signal_canceled().connect(sigc::mem_fun(*this, &EditorView::onSetCustomFormula));
        
        customFormula.name = "Clifford";
        customFormula.formulas.push_back("sin(p0 * y) + p2 * cos(p0 * x)");
        customFormula.formulas.push_back("sin(p1 * x) + p3 * cos(p1 * y)");
        customFormula.distribution = std::vector<Range<number>>(4, Range<number>(-2, 2));
        
        //////////////////////////////////////////////////////
        
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
        shapeTable.attach(formulaBox, 1, 2, 0, 1);
        
        editFormulaButton.set_label("Edit");
        editFormulaButton.set_sensitive(false);
        editFormulaButton.signal_clicked().connect(sigc::mem_fun(*this, &EditorView::onEditFormulaClick));
        shapeTable.attach(editFormulaButton, 2, 3, 0, 1);
        
        particleCountLabel.set_text("Particle count");
        particleCountLabel.set_alignment(Gtk::ALIGN_LEFT);
        shapeTable.attach(particleCountLabel, 0, 1, 1, 2);
        
        particleCountEntry.set_adjustment(particleCountAdjustment);
        particleCountEntry.set_numeric(true);
        particleCountEntry.signal_value_changed().connect(sigc::mem_fun(*this, &EditorView::onChangeParticleCount));
        shapeTable.attach(particleCountEntry, 1, 3, 1, 2);
        
        parameterViewWindow.set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_AUTOMATIC);
        parameterViewWindow.set_size_request(-1, 110);
        shapeTable.attach(parameterViewWindow, 0, 3, 2, 3);
        
        parameterModel = Gtk::ListStore::create(parameterColumns);
        parameterView.set_model(parameterModel);
        
        parameterColumn.set_title("Parameters");
        parameterColumn.pack_start(parameterRenderer);
        parameterColumn.set_cell_data_func(parameterRenderer, sigc::mem_fun(*this, &EditorView::parameterColumnCellData));
        parameterColumn.add_attribute(parameterRenderer.property_adjustment(), parameterColumns.adjustment);
        parameterView.append_column(parameterColumn);
        
        parameterRenderer.property_editable() = true;
        parameterRenderer.property_digits() = 18;
        
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
        
        ///////////////////////////////////////////////////////
        
        progressBox.set_border_width(5);
        progressBox.set_spacing(5);
        panel.pack_end(progressBox, Gtk::PACK_SHRINK);

        view.onTick.connect(sigc::mem_fun(*this, &EditorView::onProgress));
        progressBox.pack_start(progress);

        abortButton.set_label("Abort");
        abortButton.signal_clicked().connect(sigc::mem_fun(*this, &EditorView::onAbortClick));
        progressBox.pack_end(abortButton, Gtk::PACK_SHRINK);

        ///////////////////////////////////////////////////////

        returnButton.set_label("Choose a different attractor");
        returnButton.set_border_width(5);
        returnButton.set_size_request(-1, 80);
        returnButton.signal_clicked().connect(sigc::mem_fun(*gui, &GUI::showChooser));
        panel.pack_end(returnButton, Gtk::PACK_SHRINK);
        
        ///////////////////////////////////////////////////////

        show_all_children();
    }
    
    GUI::EditorView::~EditorView() {
        stopUpdating();
        
        delete generator;
        generator = nullptr;
        delete formula;
        formula = nullptr;
    }
    
    void GUI::EditorView::editFormula(const Formula* f) {
        automatedChange = true;
        setFormula(f->clone());
        updateFormulaBox();
        automatedChange = false;
    }
    
    void GUI::EditorView::startUpdating() {
        generator->run();
        view.start();
    }
    
    void GUI::EditorView::stopUpdating() {
        if (generator != nullptr) generator->abort();
        view.stop();
        renderer.abort();
        renderer.clear();
    }
    
    void GUI::EditorView::setFormula(Formula* f) {
        // Create a local copy of the formula
    	delete generator;
		generator = nullptr;
		delete formula;
		formula = nullptr;
        
        formula = f;
        createGenerator();
        updateParameterModel();
    }
    
    void GUI::EditorView::createGenerator() {
        int iters = infiniteIterationsButton.get_active() ? Generator::UNLIMITED_ITERATIONS : iterationsEntry.get_value_as_int();
        
        generator = new THREADED_GENERATOR_IMPL(*formula, renderer, iters);
    }
    
    void GUI::EditorView::createFormulaModel() {
        formulaModel = Gtk::ListStore::create(formulaColumns);
        
        for (auto it = FORMULA_NAMES.begin(); it < FORMULA_NAMES.end(); it++) {
            Gtk::TreeModel::Row row = *(formulaModel->append());
            row[formulaColumns.formula] = *it;
        }
        
        Gtk::TreeModel::Row lastRow = *(formulaModel->append());
        lastRow[formulaColumns.formula] = "Custom (Clifford)";
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
            row[parameterColumns.adjustment] = Gtk::manage(new Gtk::Adjustment(0, formula->getDistribution().min(index), formula->getDistribution().max(index), 1e-4, 1e-2));
            
            index++;
        }
    }
    
    void GUI::EditorView::onEditFormulaClick() {
        editor.show();
    }
    
    void GUI::EditorView::onUpdateCustomFormula(CustomFormula& cf) {
        customFormula = cf;
        onSetCustomFormula();
        
        automatedChange = true;

        // Update the GUI
        Gtk::TreeModel::Row lastRow = *(formulaModel->children().rbegin());
        lastRow[formulaColumns.formula] = "Custom (" + customFormula.name + ")";
        
        updateParameterModel();
        
        automatedChange = false;
    }
    
    void GUI::EditorView::onSetCustomFormula() {
        // Set the formula
        UserDefined* f = new UserDefined();
        CustomDistribution dstr(customFormula.distribution);
        f->set(customFormula.formulas, customFormula.distribution.size(), dstr, customFormula.name);
        setFormula(f);
        
        startUpdating();
    }
    
    void GUI::EditorView::onChangeFormula() {
        if (automatedChange) return;
        
        auto it = formulaBox.get_active();
        if (!it) return;
        
        auto row = *it;
        if (!row) return;
        
        stopUpdating();
        
        std::string name = row.get_value(formulaColumns.formula);
        
        int offset = name.find("Custom");
        Formula *f;
        if ((offset != std::string::npos) && (offset == 0)) {
            // Custom formula
            editFormulaButton.set_sensitive(true);
            editor.setCustomFormula(customFormula);
            editor.show();
        } else {
            editFormulaButton.set_sensitive(false);
            f = createFormula(name);
            setFormula(f);
            startUpdating();
        }
    }
    
    void GUI::EditorView::onChangeParticleCount() {
    	stopUpdating();
        generator->setParticleCount(particleCountEntry.get_value_as_int());
        startUpdating();
    }
    
    void GUI::EditorView::onChangeIterations() {
    	stopUpdating();
        if (generator != nullptr) delete generator;
        createGenerator();
        startUpdating();
    }
    
    void GUI::EditorView::onProgress() {
    	if (infiniteIterationsButton.get_active()) {
    		progress.pulse();
    	} else {
    		double iterations = iterationsEntry.get_value();
    		int particles = particleCountEntry.get_value_as_int();
    		int received = renderer.getReceivedParticleCount();

    		progress.set_fraction(received/(iterations*particles));
    	}
    }

    void GUI::EditorView::onAbortClick() {
    	generator->abort();
    	view.stop();
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
            
            stopUpdating();

            // Update the parameter
            auto params = formula->getParameters();
            params[index] = value;
            Formula *f = createFormula(formula->name(), params);
            setFormula(f);
            
            startUpdating();
        }
    }
    
    GUI::FormulaEditor::FormulaEditor():
        texts(4, 2),
        countAdjustment(0, 0, std::numeric_limits<int>::max(), 1, 10),
        cancelButton(Gtk::Stock::CANCEL),
        okButton(Gtk::Stock::OK)
    {
        set_title("Formula Editor");
        set_size_request(500, 300);
        set_modal();
        
        content.set_border_width(10);
        content.set_spacing(5);
        add(content);
        
        texts.set_row_spacings(5);
        content.pack_start(texts, Gtk::PACK_SHRINK);
        
        nameLabel.set_alignment(Gtk::ALIGN_LEFT);
        nameLabel.set_text("Name");
        texts.attach(nameLabel, 0, 1, 0, 1);
        
        texts.attach(nameEntry, 1, 2, 0, 1);
        
        xLabel.set_alignment(Gtk::ALIGN_LEFT);
        xLabel.set_text("X");
        texts.attach(xLabel, 0, 1, 1, 2);
        
        texts.attach(xEntry, 1, 2, 1, 2);
        
        yLabel.set_alignment(Gtk::ALIGN_LEFT);
        yLabel.set_text("Y");
        texts.attach(yLabel, 0, 1, 2, 3);
        
        texts.attach(yEntry, 1, 2, 2, 3);
        
        countLabel.set_alignment(Gtk::ALIGN_LEFT);
        countLabel.set_text("Parameter count");
        texts.attach(countLabel, 0, 1, 3, 4);
        
        countEntry.set_adjustment(countAdjustment);
        countEntry.set_numeric(true);
        countEntry.signal_value_changed().connect(sigc::mem_fun(*this, &FormulaEditor::onCountChanged));
        texts.attach(countEntry, 1, 2, 3, 4);
        
        dstrScrollWindow.set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_AUTOMATIC);
        content.pack_start(dstrScrollWindow);
        
        dstrModel = Gtk::ListStore::create(dstrColumns);
        dstrView.set_model(dstrModel);
        dstrView.append_column_numeric("Parameter", dstrColumns.index, "%d");
        dstrView.append_column_numeric_editable("Minimum", dstrColumns.min, "%.4f");
        dstrView.append_column_numeric_editable("Maximum", dstrColumns.max, "%.4f");
        
        dstrScrollWindow.add(dstrView);
        
        actions.set_spacing(5);
        cancelButton.signal_clicked().connect(sigc::mem_fun(*this, &FormulaEditor::onCancel));
        actions.pack_start(cancelButton);
        okButton.signal_clicked().connect(sigc::mem_fun(*this, &FormulaEditor::onSave));
        actions.pack_end(okButton);
        
        content.pack_start(actions, Gtk::PACK_SHRINK);
        
        ////////////////////////////////////////////////////////////
        
        show_all_children();
    }
    
    void GUI::FormulaEditor::setCustomFormula(CustomFormula& f) {
        nameEntry.set_text(f.name);
        xEntry.set_text(f.formulas[0]);
        yEntry.set_text(f.formulas[1]);
        countEntry.set_value(f.distribution.size());
        
        Gtk::TreeModel::Children children = dstrModel->children();
        int i = 0;
        for (auto it = children.begin(); it != children.end(); it++) {
            Gtk::TreeModel::Row row = *it;
            row[dstrColumns.min] = f.distribution[i].min();
            row[dstrColumns.max] = f.distribution[i].max();
            i++;
        }
    }
    
    void GUI::FormulaEditor::onSave() {
        CustomFormula data;
        data.name = nameEntry.get_text();
        data.formulas.push_back(xEntry.get_text());
        data.formulas.push_back(yEntry.get_text());
        
        Gtk::TreeModel::Children children = dstrModel->children();
        for (auto it = children.begin(); it != children.end(); it++) {
            Gtk::TreeModel::Row row = *it;
            data.distribution.push_back(Range<number>(row[dstrColumns.min], row[dstrColumns.max]));
        }
        
        signalSavedData.emit(data);
        hide();
    }
    
    void GUI::FormulaEditor::onCancel() {
        signalCanceled.emit();
        hide();
    }
    
    bool GUI::FormulaEditor::on_window_delete_event(GdkEventAny*) {
        signalCanceled.emit();
        return true;
    }
    
    void GUI::FormulaEditor::onCountChanged() {
        Gtk::TreeModel::Children children = dstrModel->children();
        
        int count = countEntry.get_value_as_int();
        if (count < children.size()) {
            // Delete if too many rows
            
            // Select the rows
            auto selection = dstrView.get_selection();
            Gtk::TreePath start( std::to_string( count - 1) );
            Gtk::TreePath end( std::to_string(children.size() - 1) );
            selection->select(start, end);
            
            // Make references from selection
            std::list<Gtk::TreePath> paths = selection->get_selected_rows();
            std::list<Gtk::TreeRowReference> rows;
            for (auto pathit = paths.begin(); pathit != paths.end(); pathit++) {
                rows.push_back(Gtk::TreeRowReference(dstrModel, *pathit));
            }
            
            // Erase the rows
            for (auto it = rows.begin(); it != rows.end(); it++) {
                Gtk::TreeModel::iterator treeit = dstrModel->get_iter(it->get_path());
                dstrModel->erase(treeit);
            }
            
        } else if (count > children.size()) {
            // Append necessary rows
            int howMany = count - children.size();
            
            for (int i = 1; i <= howMany; i++) {
                Gtk::TreeModel::Row row = *(dstrModel->append());
                row[dstrColumns.index] = i;
                row[dstrColumns.min] = -2;
                row[dstrColumns.max] = 2;
            }
        }
    }
}

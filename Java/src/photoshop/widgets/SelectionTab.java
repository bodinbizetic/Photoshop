package photoshop.widgets;

import photoshop.exceptions.NameAlreadyExists;
import photoshop.project.Project;
import photoshop.project.ProjectSaver;
import photoshop.selection.MouseRectangleSelection;
import photoshop.selection.Rectangle;
import photoshop.selection.Selection;

import javax.swing.*;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.TransformerException;
import java.awt.*;
import java.io.File;
import java.util.LinkedList;
import java.util.List;
import java.util.stream.Stream;

public class SelectionTab extends JPanel {

    private final DrawingPanel drawingPanel;
    private JList<Selection> all_selections;
    private JList<Rectangle> all_rectangles;
    private Checkbox cbActive;
    private JTextField tfNameField;
    private Project project;

    private MouseRectangleSelection mouseRectangleSelection;
    public SelectionTab(DrawingPanel drawingPanel) {
        setLayout(new GridLayout(2, 1));

        this.drawingPanel = drawingPanel;
        mouseRectangleSelection = new MouseRectangleSelection(drawingPanel, this);
        drawingPanel.addMouseListener(mouseRectangleSelection);
        drawingPanel.addMouseMotionListener(mouseRectangleSelection);

        addUpperPanel();
        addLowerPanel();
    }

    private void addLowerPanel() {
        JPanel lowerPanel = new JPanel();
        lowerPanel.setLayout(new FlowLayout());
        all_rectangles = new JList<>();
        all_rectangles.setModel(new DefaultListModel<>());
        JScrollPane scrollPane = new JScrollPane();
        scrollPane.setViewportView(all_rectangles);

        Button add = new Button("Add");
        add.addActionListener(e -> addMouseSelected());
        Button clear = new Button("Clear");
        clear.addActionListener(e -> clearSelectedRectangles());

        lowerPanel.add(scrollPane);
        lowerPanel.add(add);
        lowerPanel.add(clear);

        add(lowerPanel);
    }

    private void clearSelectedRectangles() {
        DefaultListModel model = (DefaultListModel) all_rectangles.getModel();
        model.clear();
    }

    private void addMouseSelected() {
        Rectangle rectangle = mouseRectangleSelection.getRectangle();
        if(rectangle.getWidth() == 0 && rectangle.getHeight() == 0)
            return;
        mouseRectangleSelection.reset();
        addRectangle(rectangle);
        updateDrawingPanel();
    }

    private void addRectangle(Rectangle rectangle) {
        DefaultListModel model = (DefaultListModel) all_rectangles.getModel();
        model.addElement(rectangle);
    }

    private void addUpperPanel() {
        JPanel upperPanel = new JPanel();
        addJList(upperPanel);
        addSelectionControls(upperPanel);
        add(upperPanel);
    }

    private void addSelectionControls(JPanel upperPanel) {
        JPanel controls = new JPanel();
        controls.setLayout(new FlowLayout());

        Label name = new Label("Selection name: ");
        tfNameField = new JTextField();
        Button create = new Button("Create");
        create.addActionListener(e -> addNewSelection());
        Button delete = new Button("Delete");
        delete.addActionListener(e -> deleteSelection());
        cbActive = new Checkbox("active");
        cbActive.addItemListener(e -> {
            if(all_selections.getSelectedValue() == null)
                return;
            all_selections.getSelectedValue().setActive(cbActive.getState());
            updateDrawingPanel();
        });
        tfNameField.setPreferredSize(new Dimension(100, 20));

        controls.add(name);
        controls.add(tfNameField);
        controls.add(create);
        controls.add(delete);
        controls.add(cbActive);

        upperPanel.add(controls);
    }
    private void deleteSelection() {
        Selection selection = all_selections.getSelectedValue();
        if(selection == null)
            return;
        project.removeSelection(selection);
        loadSelectionList();
        updateDrawingPanel();
    }
    private void addNewSelection() {
        try {
            String name = tfNameField.getText();
            checkNameExists(name);

            List<Rectangle> recList = new LinkedList<>();
            DefaultListModel model = (DefaultListModel) all_rectangles.getModel();
            Stream.of(model.toArray()).forEach(rectangle -> recList.add((Rectangle) rectangle));
            Selection newSelection = new Selection(name, "selections" + File.separator + name + ".sel", recList, true);
            project.addSelection(newSelection);

            clearSelectedRectangles();
            loadSelectionList();
            updateDrawingPanel();
        } catch (NameAlreadyExists e) {
            JOptionPane.showMessageDialog(this, e.getMessage());
        }
    }

    private void checkNameExists(String name) throws NameAlreadyExists {
        boolean match = project.getAll_Selections().stream().anyMatch(sel -> sel.getName().equals(name));
        if(match)
            throw new NameAlreadyExists(name);
    }

    private void addJList(JPanel upperPanel) {
        upperPanel.setLayout(new GridLayout(1, 2));
        all_selections = new JList<>();
        all_selections.setModel(new DefaultListModel<>());
        all_selections.addListSelectionListener(e -> updateSelectionList());
        JScrollPane scrollPane = new JScrollPane();
        scrollPane.setViewportView(all_selections);
        upperPanel.add(scrollPane);
    }

    private void updateSelectionList() {
        Selection selected = all_selections.getSelectedValue();
        if(selected == null)
            return;
        cbActive.setState(selected.isActive());
    }

    private void updateDrawingPanel() {
        drawingPanel.clearSelection();
        drawingPanel.clearRectangles();
        project.getAll_Selections().stream().filter(sel -> sel.isActive()).forEach(selection -> drawingPanel.addSelection(selection));
        for(int i = 0, sz = all_rectangles.getModel().getSize(); i<sz; i++)
            drawingPanel.addRectangle(all_rectangles.getModel().getElementAt(i));

        drawingPanel.repaint();
    }

    public void loadProject(Project project) {
        this.project = project;
        loadSelectionList();
        mouseRectangleSelection.reset();
        updateDrawingPanel();
    }

    private void loadSelectionList() {
        List<Selection> selections = project.getAll_Selections();
        DefaultListModel model = (DefaultListModel) all_selections.getModel();
        model.clear();
        selections.forEach(sel -> model.addElement(sel));
        all_selections.repaint();
    }
}

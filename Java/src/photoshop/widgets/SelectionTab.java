package photoshop.widgets;

import photoshop.project.Project;
import photoshop.selection.Selection;

import javax.swing.*;
import java.awt.*;
import java.util.List;

public class SelectionTab extends JPanel {

    private JList<Selection> all_selections;
    private JList<Selection> all_rectangles;
    private Checkbox cbActive;
    private JTextField tfNameField;
    private Project project;

    public SelectionTab(DrawingPanel drawingPanel) {
        setLayout(new GridLayout(2, 1));

        addUpperPanel();
        addLowerPanel();
    }

    private void addLowerPanel() {
        JPanel lowerPanel = new JPanel();
        lowerPanel.setLayout(new FlowLayout());
        all_rectangles = new JList<>();
        JScrollPane scrollPane = new JScrollPane();
        scrollPane.setViewportView(all_rectangles);
        lowerPanel.add(scrollPane);
        add(lowerPanel);
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
        Button delete = new Button("Delete");
        cbActive = new Checkbox("active");

        tfNameField.setPreferredSize(new Dimension(100, 20));

        controls.add(name);
        controls.add(tfNameField);
        controls.add(create);
        controls.add(delete);
        controls.add(cbActive);

        upperPanel.add(controls);
    }

    private void addJList(JPanel upperPanel) {
        upperPanel.setLayout(new GridLayout(1, 2));
        all_selections = new JList<>();
        all_selections.setModel(new DefaultListModel<>());
        JScrollPane scrollPane = new JScrollPane();
        scrollPane.setViewportView(all_selections);
        upperPanel.add(scrollPane);
    }

    public void loadProject(Project project) {
        this.project = project;
        loadSelectionList();
    }

    private void loadSelectionList() {
        List<Selection> selections = project.getAll_Selections();
        DefaultListModel model = (DefaultListModel) all_selections.getModel();
        model.clear();
        selections.forEach(sel -> model.addElement(sel));
        all_selections.repaint();
    }
}

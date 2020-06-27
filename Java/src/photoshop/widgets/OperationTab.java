package photoshop.widgets;

import photoshop.operations.Operation;

import javax.swing.*;
import javax.swing.border.CompoundBorder;
import javax.swing.border.EmptyBorder;
import java.awt.*;

public class OperationTab extends JPanel {

    private JList<Operation> all_operations;
    private JList<Operation> createList;
    private JSpinner parametarSpinner;
    private TextField operationName;
    public OperationTab() {
        setLayout(new GridLayout(2, 1));

        addOperationPickerPanel();
        addOperationCreaterPanel();
    }

    private void addOperationCreaterPanel() {
        JPanel creationPanel = new JPanel();
        creationPanel.setLayout(new GridLayout(1, 2));

        addOperationCreaterPanelLeft(creationPanel);
        addOperationCreaterPanelRight(creationPanel);
        add(creationPanel);
    }

    private void addOperationCreaterPanelRight(JPanel creationPanel) {
        JPanel right = new JPanel();
        Button create = new Button("Create");
        operationName = new TextField();
        operationName.setPreferredSize(new Dimension(100, 20));
        Button remove = new Button("Clear");

        right.add(new Label("Name: "));
        right.add(operationName);
        right.add(create);
        right.add(remove);
        creationPanel.add(right);
    }

    private void addOperationCreaterPanelLeft(JPanel creationPanel) {
        JPanel listPanel = new JPanel();
        listPanel.setLayout(new GridLayout(1, 1));
        createList = new JList<>();
        createList.setBorder(BorderFactory.createLineBorder(Color.BLACK));
        listPanel.add(createList);
        listPanel.setBorder(new EmptyBorder(10, 10, 10, 10));
        creationPanel.add(listPanel);
    }

    private void addOperationPickerPanel() {
        JPanel operationsPanel = new JPanel();
        operationsPanel.setBorder(BorderFactory.createRaisedBevelBorder());
        operationsPanel.setLayout(new GridLayout(1, 2));

        addOperationPickerPanelLeft(operationsPanel);
        addOperationPickerPanelRight(operationsPanel);

        add(operationsPanel);
    }

    private void addOperationPickerPanelLeft(JPanel operations) {
        JPanel right = new JPanel();
        right.setBorder(new EmptyBorder(10, 10, 10, 10));
        right.setLayout(new BorderLayout());
        all_operations = new JList<>();
        all_operations.setBorder(BorderFactory.createLineBorder(Color.BLACK));
        right.add(all_operations);
        operations.add(right);
    }

    private void addOperationPickerPanelRight(JPanel operations) {
        JPanel center = new JPanel();
//        center.setBorder(new EmptyBorder(100, 0, 0, 0));
        center.setLayout(new BorderLayout());
        JPanel rightPart = new JPanel();
        rightPart.setLayout(new FlowLayout());
        Label label = new Label("Arg:");
        parametarSpinner = new JSpinner();
        parametarSpinner.setPreferredSize(new Dimension(60, 20));
        Button use = new Button("Use");
        Button add = new Button("Add");
        Button delete = new Button("Delete");

        rightPart.add(label);
        rightPart.add(parametarSpinner);
        rightPart.add(use);
        rightPart.add(add);
        rightPart.add(delete);
        center.add(BorderLayout.CENTER, rightPart);
        operations.add(center);
    }
}

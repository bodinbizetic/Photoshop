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
    public OperationTab() {
        setLayout(new GridLayout(2, 1));

        addOperationPickerPanel();
//        addOperationCreaterPanel();
    }

    private void addOperationCreaterPanel() {
        JPanel operations = new JPanel();
        operations.setLayout(new GridLayout(1, 2));
        createList = new JList<>();

        operations.add(createList);
        add(createList);
    }

    private void addOperationPickerPanel() {
        JPanel operations = new JPanel();
        operations.setBorder(BorderFactory.createRaisedBevelBorder());
        operations.setLayout(new GridLayout(1, 2));

        addOperationPickerPanelRight(operations);
        addOperationPickerPanelLeft(operations);

        add(operations);
    }

    private void addOperationPickerPanelRight(JPanel operations) {
        JPanel right = new JPanel();
        right.setBorder(new EmptyBorder(10, 10, 10, 10));
        all_operations = new JList<>();
        all_operations.setPreferredSize(new Dimension(120, 280));
        all_operations.setBorder(BorderFactory.createLineBorder(Color.BLACK));
        right.add(all_operations);
        operations.add(right);
    }

    private void addOperationPickerPanelLeft(JPanel operations) {
        JPanel center = new JPanel();
        center.setBorder(new EmptyBorder(100, 0, 0, 0));
        center.setLayout(new BorderLayout());
        JPanel leftPart = new JPanel();
        leftPart.setLayout(new FlowLayout());
        Label label = new Label("Arg: ");
        parametarSpinner = new JSpinner();
        parametarSpinner.setPreferredSize(new Dimension(60, 20));
        Button use = new Button("Use");
        Button add = new Button("Add");
        Button delete = new Button("Delete");

        leftPart.add(label);
        leftPart.add(parametarSpinner);
        leftPart.add(use);
        leftPart.add(add);
        leftPart.add(delete);
        center.add(leftPart, BorderLayout.CENTER);
        operations.add(center);
    }
}

package photoshop.widgets;

import photoshop.PhotoshopExec;
import photoshop.exceptions.ProjectNotLoaded;
import photoshop.operations.DiadicOperation;
import photoshop.operations.MonadicOperation;
import photoshop.operations.Operation;
import photoshop.project.Project;

import javax.swing.*;
import javax.swing.border.EmptyBorder;
import java.awt.*;
import java.util.stream.Stream;

public class OperationTab extends JPanel {

    private final DrawingPanel drawingPanel;
    private JList<Operation> all_operations;
    private JList<Operation> createList;
    private JSpinner parametarSpinner;
    private TextField operationName;
    private Project project;

    private Operation[] default_operations;
    public OperationTab(DrawingPanel drawingPanel) {
        this.drawingPanel = drawingPanel;
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
        JScrollPane scrollPane = new JScrollPane();
        scrollPane.setViewportView(all_operations);
        right.add(scrollPane);
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

        use.addActionListener(e -> {
            if(all_operations.getSelectedIndex() < default_operations.length)
                all_operations.getSelectedValue().setParam();

            new UseOperationHandler(all_operations.getSelectedValue()).start();
        });

        rightPart.add(label);
        rightPart.add(parametarSpinner);
        rightPart.add(use);
        rightPart.add(add);
        rightPart.add(delete);
        center.add(BorderLayout.CENTER, rightPart);
        operations.add(center);
    }

    public void loadProject(Project project) {
        this.project = project;

        loadOperations();
    }

    private void loadOperations() {
        all_operations.setModel(new DefaultListModel<>());
        addDefaultOperations();
        addProjectOperationToList();
    }

    private void addDefaultOperations() {
        default_operations = initDefaultOperations();
        DefaultListModel listModel = (DefaultListModel) all_operations.getModel();
        Stream.of(default_operations).forEach(listModel::addElement);
        all_operations.setModel(listModel);
    }

    private Operation[] initDefaultOperations() {
        Operation[] op = new Operation[15];
        op[0] = new DiadicOperation("add", "", () -> (int) parametarSpinner.getValue());
        op[1] = new DiadicOperation("sub", "", () -> (int) parametarSpinner.getValue());
        op[2] = new DiadicOperation("div", "", () -> (int) parametarSpinner.getValue());
        op[3] = new DiadicOperation("mul", "", () -> (int) parametarSpinner.getValue());
        op[4] = new DiadicOperation("rdiv", "", () -> (int) parametarSpinner.getValue());
        op[5] = new DiadicOperation("rsub", "", () -> (int) parametarSpinner.getValue());
        op[6] = new DiadicOperation("pow", "", () -> (int) parametarSpinner.getValue());
        op[7] = new DiadicOperation("max", "", () -> (int) parametarSpinner.getValue());
        op[8] = new DiadicOperation("min", "", () -> (int) parametarSpinner.getValue());
        op[9] = new MonadicOperation("Log", "");
        op[10] = new MonadicOperation("Abs", "");
        op[11] = new MonadicOperation("Invert", "");
        op[12] = new MonadicOperation("Gray", "");
        op[13] = new MonadicOperation("Black and white", "");
        op[14] = new MonadicOperation("Median", "");
        return op;
    }

    private void addProjectOperationToList() {
        java.util.List<Operation> list = project.getAll_operations();
        DefaultListModel listModel = (DefaultListModel) all_operations.getModel();
        list.forEach(listModel::addElement);
        all_operations.setModel(listModel);
    }

    public Operation getOperation(String name) throws ProjectNotLoaded {
        if(default_operations == null)
            throw new ProjectNotLoaded();
        return Stream.of(default_operations).filter(operation -> operation.getName().equals(name)).findFirst().get();

    }

    private class UseOperationHandler extends Thread{
        Operation operation;
        public UseOperationHandler(Operation operation) {
            this.operation = operation;
        }

        @Override
        public void run() {
            try {
                if(operation == null)
                    return;
                PhotoshopExec ph = new PhotoshopExec();
                ph.setFilterActive(true);
                ph.addLayers(project.getAll_layers());
                ph.addOperation(operation);
                ph.start();
                ph.join();
                project.reloadLayers();
                drawingPanel.repaint();
            } catch (InterruptedException ignore) {}
        }
    }
}

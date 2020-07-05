package photoshop.widgets;

import photoshop.PhotoshopExec;
import photoshop.exceptions.NameAlreadyExists;
import photoshop.exceptions.ProjectNotLoaded;
import photoshop.operations.ComplexOperation;
import photoshop.operations.DiadicOperation;
import photoshop.operations.MonadicOperation;
import photoshop.operations.Operation;
import photoshop.project.Project;

import javax.swing.*;
import javax.swing.border.EmptyBorder;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import java.awt.*;
import java.io.File;
import java.util.LinkedList;
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

        remove.addActionListener(e -> emptyCreateList());
        create.addActionListener(e -> addNewOperation());
        right.add(new Label("Name: "));
        right.add(operationName);
        right.add(create);
        right.add(remove);
        creationPanel.add(right);
    }

    private void addNewOperation() {
        try {
            Operation op = createOperation();
            addToListsOperation(op);
            emptyCreateList();
        } catch(NameAlreadyExists e) {
            JOptionPane.showMessageDialog(null, e.getMessage());
        }
    }

    private void addToListsOperation(Operation op) {
        project.addOperation(op);
        DefaultListModel model = (DefaultListModel) all_operations.getModel();
        model.addElement(op);
    }

    private Operation createOperation() throws NameAlreadyExists {
        int n = createList.getModel().getSize();
        java.util.List<Operation> list = new LinkedList<>();
        for(int i=0; i<n; i++) {
            Operation oper = createList.getModel().getElementAt(i);
            oper.getList().forEach(operation -> list.add(operation));
        }
        String name = getOperationName();
        Operation cOp = new ComplexOperation(name, "resource" + File.separator + name + ".fun", list);
        return cOp;
    }

    private String getOperationName() throws NameAlreadyExists {
        String text = operationName.getText();
        if(nameExistsCheck(text) || text == "")
            throw new NameAlreadyExists(text);
        return text;
    }

    private boolean nameExistsCheck(String text) {
        if(project.getAll_operations().stream().filter(operation -> operation.getName().equals(text)).count() > 0)
            return true;
        return false;
    }

    private void emptyCreateList() {
        createList.setModel(new DefaultListModel<>());
    }

    private void addOperationCreaterPanelLeft(JPanel creationPanel) {
        JPanel listPanel = new JPanel();
        listPanel.setLayout(new GridLayout(1, 1));
        createList = new JList<>();
        createList.setModel(new DefaultListModel<>());
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
        all_operations.addListSelectionListener(e -> updateList());
        all_operations.setBorder(BorderFactory.createLineBorder(Color.BLACK));
        JScrollPane scrollPane = new JScrollPane();
        scrollPane.setViewportView(all_operations);
        right.add(scrollPane);
        operations.add(right);
    }

    private void addOperationPickerPanelRight(JPanel operations) {
        JPanel center = new JPanel();
        center.setLayout(new BorderLayout());
        JPanel rightPart = new JPanel();
        rightPart.setLayout(new FlowLayout());
        Label label = new Label("Arg:");
        parametarSpinner = new JSpinner();
        parametarSpinner.setPreferredSize(new Dimension(60, 20));
        parametarSpinner.addChangeListener(e -> {
            updateList();
        });
        Button use = new Button("Use");
        Button add = new Button("Add");
        Button delete = new Button("Delete");

        add.addActionListener(e -> addPickToCreate());
        use.addActionListener(e -> {
            if(all_operations.getSelectedValue() == null)
                return;
            if(all_operations.getSelectedIndex() < default_operations.length)
                all_operations.getSelectedValue().setParam();

            new UseOperationHandler(all_operations.getSelectedValue()).start();
        });
        delete.addActionListener(e -> removeSelectedNonDefaultOperation());
        rightPart.add(label);
        rightPart.add(parametarSpinner);
        rightPart.add(use);
        rightPart.add(add);
        rightPart.add(delete);
        center.add(BorderLayout.CENTER, rightPart);
        operations.add(center);
    }

    private void updateList() {
        if(all_operations.getSelectedValue() == null)
            return;
        all_operations.getSelectedValue().setParam();
        all_operations.repaint();
    }

    private void removeSelectedNonDefaultOperation() {
        if(all_operations.getSelectedValue() == null)
            return;
        if(all_operations.getSelectedIndex() < default_operations.length)
            return;
        Operation operation = all_operations.getSelectedValue();
        project.removeOperation(operation);
        loadOperations();
    }

    private void addPickToCreate() {
        if(all_operations.getSelectedValue() == null)
            return;
        DefaultListModel<Operation> model = (DefaultListModel) createList.getModel();
        try {
            Operation newOp = (Operation) all_operations.getSelectedValue().clone();
            newOp.setParam();
            model.addElement(newOp);
        } catch (CloneNotSupportedException e) {
            e.printStackTrace();
        }
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
                ph.addSelections(project.getAll_Selections());
                ph.start();
                ph.join();
                project.reloadLayers();
                drawingPanel.repaint();
            } catch (InterruptedException ignore) {}
        }
    }
}

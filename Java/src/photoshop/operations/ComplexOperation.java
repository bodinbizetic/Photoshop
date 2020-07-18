package photoshop.operations;

import photoshop.project.Project;

import java.util.LinkedList;
import java.util.List;

public class ComplexOperation extends Operation{

    private List<Operation> all_operations = new LinkedList<>();

    public ComplexOperation(String name, String path, List<Operation> operations) {
        super(name, path);
        this.all_operations = operations;
    }

    @Override
    public List<Operation> getList() {
        return all_operations;
    }

    @Override
    public Object clone() throws CloneNotSupportedException {
        ComplexOperation newOp = (ComplexOperation) super.clone();
        newOp.all_operations = new LinkedList<>();
        all_operations.forEach(op -> {
            try {
                newOp.all_operations.add((Operation) op.clone());
            } catch (CloneNotSupportedException e) {
                e.printStackTrace();
            }
        });
        return newOp;
    }
}

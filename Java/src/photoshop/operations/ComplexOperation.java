package photoshop.operations;

import photoshop.project.Project;

import java.util.LinkedList;
import java.util.List;

public class ComplexOperation extends Operation{

    private List<Operation> all_operations = new LinkedList<>();

    public ComplexOperation(String name, String path, int cppID, List<Operation> operations) {
        super(name, path, cppID);
        this.all_operations = operations;
    }

    @Override
    List<Operation> getList() {
        return all_operations;
    }
}

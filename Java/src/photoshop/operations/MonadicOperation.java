package photoshop.operations;

import photoshop.project.Project;

import java.util.LinkedList;
import java.util.List;

public class MonadicOperation extends Operation {

    public MonadicOperation(String name, String path, int cppID) {
        super(name, path, cppID);
    }

    @Override
    List<Operation> getList() {
        List<Operation> tempList = new LinkedList<>();
        tempList.add(this);
        return tempList;
    }
}

package photoshop.operations;

import photoshop.project.Project;

import java.util.LinkedList;
import java.util.List;

public class DiadicOperation extends Operation {

    private int parametar;

    public DiadicOperation(String name, String path, int cppID, ParametarGetter parametarGetter) {
        super(name, path, cppID);
        this.parametar = parametarGetter.getParametar();
    }

    @Override
    boolean hasParam() {
        return true;
    }

    @Override
    public int getParametar() {
        return parametar;
    }

    @Override
    List<Operation> getList() {
        List<Operation> tempList = new LinkedList<>();
        tempList.add(this);
        return tempList;
    }
}

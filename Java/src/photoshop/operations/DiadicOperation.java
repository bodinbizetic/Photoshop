package photoshop.operations;

import photoshop.project.Project;

import java.util.LinkedList;
import java.util.List;

public class DiadicOperation extends Operation {

    private int parametar;

    public DiadicOperation(String name, String path, ParametarGetter parametarGetter) {
        super(name, path);
        this.parametar = parametarGetter.getParametar();
    }

    @Override
    public boolean hasParam() {
        return true;
    }

    @Override
    public int getParametar() {
        return parametar;
    }

    @Override
    public List<Operation> getList() {
        List<Operation> tempList = new LinkedList<>();
        tempList.add(this);
        return tempList;
    }
}

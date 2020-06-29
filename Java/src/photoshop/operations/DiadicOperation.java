package photoshop.operations;

import photoshop.project.Project;

import java.util.LinkedList;
import java.util.List;

public class DiadicOperation extends Operation {

    private int parametar;
    private ParametarGetter parametarGetter;
    public DiadicOperation(String name, String path, ParametarGetter parametarGetter) {
        super(name, path);
        this.parametarGetter = parametarGetter;
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
    public void setParam() {this.parametar = parametarGetter.getParametar();}

    @Override
    public List<Operation> getList() {
        List<Operation> tempList = new LinkedList<>();
        tempList.add(this);
        return tempList;
    }
}

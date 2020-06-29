package photoshop.operations;

import photoshop.project.Project;

import java.io.File;
import java.util.List;

abstract public class Operation {

    protected File saveFile;
    protected String name;

    public Operation(String name, String path) {
        this.name = name;
        this.saveFile = new File(System.getProperty("user.dir"), path);
    }

    public boolean hasParam() {
        return false;
    }

    public int getParametar() {
        return 0;
    }
    public abstract List<Operation> getList();

    public void setParam() {}

    @Override
    public String toString() {
        return getName();
    }

    public String getName() {
        return name;
    }
}

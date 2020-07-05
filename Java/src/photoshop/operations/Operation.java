package photoshop.operations;

import photoshop.project.Project;

import java.io.File;
import java.util.List;

abstract public class Operation implements Cloneable{

    private final String path;
    protected File saveFile;
    protected String name;

    public Operation(String name, String path) {
        this.name = name;
        this.path = path;
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
        return getName() + (hasParam() ? " " + getParametar() : "");
    }

    public String getName() {
        return name;
    }

    public String getPath() {
        return path;
    }

    @Override
    public Object clone() throws CloneNotSupportedException {
        return super.clone();
    }
}

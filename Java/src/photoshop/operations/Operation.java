package photoshop.operations;

import photoshop.project.Project;

import java.io.File;
import java.util.List;

abstract public class Operation {

    protected File saveFile;
    protected String name;
    protected int cppID;

    public Operation(String name, String path, int cppID) {
        this.name = name;
        this.saveFile = new File(path);
        this.cppID = cppID;
    }

    boolean hasParam() {
        return false;
    }

    int getParametar() {
        return 0;
    }
    abstract List<Operation> getList();

    public String getName() {
        return name;
    }

    public int getcppID() {
        return cppID;
    }
}

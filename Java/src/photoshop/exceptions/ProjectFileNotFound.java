package photoshop.exceptions;

public class ProjectFileNotFound extends Throwable {
    public ProjectFileNotFound(String s) {
        super("Project file " + s + " is damaged or missing");
    }
}

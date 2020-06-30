package photoshop.exceptions;

public class NameAlreadyExists extends Throwable {
    public NameAlreadyExists(String text) {
        super("Name " + text + " already exists");
    }
}

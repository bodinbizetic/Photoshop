package photoshop.exceptions;

public class FileNameException extends Throwable {
    public FileNameException(String path) {
        super("File name error");
    }
}

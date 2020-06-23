package photoshop.exceptions;

public class FileCorruptedException extends Exception {

    public FileCorruptedException(String path) {
        super("File " + path + " is corrupted");
    }
}

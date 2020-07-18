package photoshop.exceptions;

public class FileExtensionMissmatch extends Throwable {
    public FileExtensionMissmatch(String path) {
        super("File " + path + " is not supported. Please choose 24bit .bmp or .pam file format");
    }
}

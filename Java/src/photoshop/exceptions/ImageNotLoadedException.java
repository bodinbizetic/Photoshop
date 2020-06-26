package photoshop.exceptions;

public class ImageNotLoadedException extends Exception {
    public ImageNotLoadedException(String msg) {
        super("Image " + msg + " could not be loaded");
    }
}

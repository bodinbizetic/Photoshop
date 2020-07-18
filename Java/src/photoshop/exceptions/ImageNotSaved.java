package photoshop.exceptions;

public class ImageNotSaved extends Exception {
    public ImageNotSaved(String path) {
        super("Image could not be saved " + path);
    }
}

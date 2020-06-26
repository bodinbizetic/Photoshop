package photoshop.layer;

import photoshop.exceptions.ImageNotLoadedException;

import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

public class Layer {
    private String name;
    private String path;
    private int opacity;
    private boolean active;


    private File imageFile;
    private BufferedImage image;

    public Layer(String name, String path, int opacity, boolean active) throws ImageNotLoadedException {
        this.name = name;
        this.path = path;
        this.opacity = opacity;
        this.active = active;

        imageFile = new File(System.getProperty("user.dir"), path);
        loadImage();
    }

    public synchronized void loadImage() throws ImageNotLoadedException {
        try {
            image = ImageIO.read(imageFile);
        } catch (IOException e) {
            throw new ImageNotLoadedException(path);
        }
    }

    @Override
    public String toString() {
        return name;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getPath() {
        return path;
    }

    public void setPath(String path) {
        this.path = path;
    }

    public int getOpacity() {
        return opacity;
    }

    public void setOpacity(int opacity) {
        this.opacity = opacity;
    }

    public boolean isActive() {
        return active;
    }

    public void setActive(boolean active) {
        this.active = active;
    }

    public void delete() {
        File file = new File(System.getProperty("user.dir"), path);
        file.delete();
    }

    public synchronized BufferedImage getImage() {
        return image;
    }
}

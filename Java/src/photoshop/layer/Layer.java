package photoshop.layer;

import photoshop.exceptions.ImageNotLoadedException;
import photoshop.exceptions.ImageNotSaved;

import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.nio.file.CopyOption;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardCopyOption;

import static java.nio.file.StandardCopyOption.REPLACE_EXISTING;

public class Layer {
    protected String name;
    protected String path;
    protected int opacity;
    protected boolean active;

    protected File originalImage;
    protected BufferedImage image;

    protected Layer() {

    }

    public Layer(String name, String path) throws ImageNotLoadedException {
        this.opacity = 100;
        this.active = true;
        this.name = name;
        this.path = path;

        originalImage = new File(path);
        if(originalImage.exists() == false)
            throw new ImageNotLoadedException(path);
    }

    @Override
    public String toString() {
        return name;
    }

    public String getName() {
        return name;
    }

    public String getPath() {
        return originalImage.getPath();
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
        originalImage.delete();
    }

    public synchronized BufferedImage getImage() {
        return image;
    }

    public synchronized void loadImage() throws ImageNotLoadedException {
        try {
            image = ImageIO.read(originalImage);
        } catch (IOException e) {
            throw new ImageNotLoadedException(path);
        }
    }
}

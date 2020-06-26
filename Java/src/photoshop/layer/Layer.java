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
    private String name;
    private String path;
    private int opacity;
    private boolean active;

    private File originalImage;
    private File tempImageFile;
    private BufferedImage image;

    public Layer(String name, String path, int opacity, boolean active) throws ImageNotLoadedException {
        this.name = name;
        this.path = path;
        this.opacity = opacity;
        this.active = active;

        originalImage = new File(System.getProperty("user.dir"), path);
        copyToTemp();
        loadImage();
    }

    private void copyToTemp() throws ImageNotLoadedException {
        String temp_name = ".temp";
        File tempFolder = new File(System.getProperty("user.dir"), temp_name);
        if(!tempFolder.exists())
            tempFolder.mkdir();
        String dst_path = temp_name + File.separator + originalImage.getName().substring(0, originalImage.getName().indexOf('.')) + ".bmp";
        tempImageFile = new File(System.getProperty("user.dir"), dst_path);
        try {
            Files.copy(Paths.get(originalImage.getPath()), Paths.get(tempImageFile.getPath()), REPLACE_EXISTING);
        } catch (IOException e) {
            e.printStackTrace();
            System.out.println("Terminal error: file cannot be copied to temp " + tempImageFile.getPath());
            throw new ImageNotLoadedException(originalImage.getPath());
        }
    }

    public void saveLayer() throws ImageNotSaved {
        try {
            Files.copy(Paths.get(tempImageFile.getPath()), Paths.get(originalImage.getPath()), REPLACE_EXISTING);
        } catch (IOException e) {
            e.printStackTrace();
            throw new ImageNotSaved(originalImage.getPath());
        }
    }

    public synchronized void loadImage() throws ImageNotLoadedException {
        try {
            image = ImageIO.read(tempImageFile);
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

    public String getTempPath() {
        return tempImageFile.getPath();
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

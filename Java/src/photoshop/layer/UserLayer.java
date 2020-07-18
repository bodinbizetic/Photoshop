package photoshop.layer;

import photoshop.PhotoshopExec;
import photoshop.exceptions.ImageNotLoadedException;
import photoshop.exceptions.ImageNotSaved;

import javax.imageio.ImageIO;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.LinkedList;
import java.util.List;

import static java.nio.file.StandardCopyOption.REPLACE_EXISTING;

public class UserLayer extends Layer {
    private File tempImageFile;

    public UserLayer(String name, String path, int opacity, boolean active) throws ImageNotLoadedException {
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
            Thread t = new LayerConverter(originalImage, tempImageFile);
            t.start();
            t.join();
        } catch (IOException | InterruptedException e) {
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

    @Override
    public synchronized void loadImage() throws ImageNotLoadedException {
        try {
            image = ImageIO.read(tempImageFile);
        } catch (IOException e) {
            throw new ImageNotLoadedException(path);
        }
    }

    @Override
    public String getPath() {
        return tempImageFile.getPath();
    }

    private static class LayerConverter extends Thread {

        private File src;
        private File dst;

        public LayerConverter(File src, File dst) throws FileNotFoundException {
            this.src = src;
            this.dst = dst;
            if(!src.exists())
                throw new FileNotFoundException();
        }

        @Override
        public void run() {
            PhotoshopExec ps = new PhotoshopExec();
            try {
                Layer layer = new Layer("LogicalLayer", src.getPath());
                List<Layer> temp = new LinkedList<>();
                temp.add(layer);
                ps.addLayers(temp);
                ps.addDestination(dst.getPath());
                ps.start();
                ps.join();
            } catch (ImageNotLoadedException | InterruptedException ignore) {}

        }
    }
}

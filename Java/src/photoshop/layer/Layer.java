package photoshop.layer;

import java.io.File;

public class Layer {
    private String name;
    private String path;
    private int opacity;
    private boolean active;

    public Layer(String name, String path, int opacity, boolean active) {
        this.name = name;
        this.path = path;
        this.opacity = opacity;
        this.active = active;
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
}

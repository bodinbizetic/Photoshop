package photoshop.selection;

import java.util.List;

public class Selection {

    private final String name;
    private final String path;
    private final List<Rectangle> all_rectangles;
    private final boolean active;

    public Selection(String name, String path, List<Rectangle> all_rectangles, boolean active) {
        this.name = name;
        this.path = path;
        this.all_rectangles = all_rectangles;
        this.active = active;
    }

    @Override
    public String toString() {
        return name;
    }

    public String getName() {
        return name;
    }

    public String getPath() {
        return path;
    }

    public List<Rectangle> getAll_rectangles() {
        return all_rectangles;
    }

    public boolean isActive() {
        return active;
    }
}

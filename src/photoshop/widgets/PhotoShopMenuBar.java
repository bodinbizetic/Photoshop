package photoshop.widgets;

import java.awt.*;

public class PhotoShopMenuBar extends MenuBar {

    public PhotoShopMenuBar() {
        super();
        addMenuFile();
    }

    private void addMenuFile() {
        Menu file = new Menu("File");
        MenuItem open = new MenuItem("Open");
        MenuItem save = new MenuItem("Save");
        file.add(open);
        file.add(save);
        add(file);
    }
}

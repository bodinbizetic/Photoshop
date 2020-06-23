package photoshop.widgets;

import java.awt.*;

public class PhotoShopMenuBar extends MenuBar {

    public PhotoShopMenuBar() {
        super();
        addMenuFile();
        addMenuExport();
    }

    private void addMenuExport() {
        Menu export = new Menu("Export");
        MenuItem bmp = new MenuItem("as BMP");
        MenuItem pam = new MenuItem("as PAM");
        export.add(bmp);
        export.add(pam);
        add(export);
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

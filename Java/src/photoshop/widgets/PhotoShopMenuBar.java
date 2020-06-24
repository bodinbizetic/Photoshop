package photoshop.widgets;

import photoshop.MainWindow;
import photoshop.exceptions.ChooseFolderDialogCanceled;
import photoshop.exceptions.FileCorruptedException;
import photoshop.exceptions.ProjectFileNotFound;
import photoshop.project.ProjectLoader;

import javax.swing.*;
import java.awt.*;
import java.io.File;

public class PhotoShopMenuBar extends MenuBar {

    private MainWindow parent;

    public PhotoShopMenuBar(MainWindow parent) {
        super();
        this.parent = parent;
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
        open.addActionListener((e -> openProject()));
        file.add(save);
        add(file);
    }

    private String folderDialog() throws ChooseFolderDialogCanceled {
        JFileChooser folderChooser = new JFileChooser();
        folderChooser.setCurrentDirectory(new File(System.getProperty("user.home")));
        folderChooser.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
        int result = folderChooser.showOpenDialog(parent);
        File selectedFolder = folderChooser.getSelectedFile();
        if(selectedFolder == null)
            throw new ChooseFolderDialogCanceled();
        return selectedFolder.getAbsolutePath();
    }

    private void openProject() {
        try {
            String path = folderDialog();
            checkIfFileExists(path + File.separator + "Project.xml");
            System.out.println(System.getProperty("user.dir"));
            System.setProperty("user.dir", path);
            System.out.println(System.getProperty("user.dir"));
            ProjectLoader projectLoader = new ProjectLoader(path + File.separator + "Project.xml");
            parent.loadProject(projectLoader.loadProject());
        } catch (ProjectFileNotFound | FileCorruptedException e) {
            JOptionPane.showMessageDialog(parent, e.getMessage());
        } catch (ChooseFolderDialogCanceled e) {
        }
    }

    private void checkIfFileExists(String s) throws ProjectFileNotFound {
        File f = new File(s);
        if(!f.exists() || f.isDirectory())
            throw new ProjectFileNotFound(s);
    }
}

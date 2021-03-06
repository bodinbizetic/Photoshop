package photoshop.widgets;

import photoshop.MainWindow;
import photoshop.PhotoshopExec;
import photoshop.exceptions.*;
import photoshop.project.Project;
import photoshop.project.ProjectLoader;
import photoshop.project.ProjectSaver;

import javax.swing.*;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.TransformerException;
import java.awt.*;
import java.io.File;
import java.nio.file.FileAlreadyExistsException;
import java.nio.file.Files;

public class PhotoShopMenuBar extends MenuBar {

    private MainWindow parent;

    public PhotoShopMenuBar(MainWindow parent) {
        super();
        this.parent = parent;
        addMenuFile();
    }

    private void addMenuFile() {
        Menu file = new Menu("File");
        MenuItem createNew      = new MenuItem("New");
        MenuItem open           = new MenuItem("Open");
        MenuItem save           = new MenuItem("Save");
        MenuItem export         = new MenuItem("Export");
        MenuItem loadCppPath    = new MenuItem("Path to engine");
        createNew.addActionListener(e -> createNewProject());
        save.addActionListener(e -> saveProject());
        export.addActionListener(e -> {
            try {
                exportProject();
            } catch (FileAlreadyExistsException | FileExtensionMissmatch | ProjectNotLoaded ex) {
                JOptionPane.showMessageDialog(parent, ex.getMessage());
            }
        });
        open.addActionListener((e -> openProject()));
        loadCppPath.addActionListener(e -> setPathToEngine());
        file.add(createNew);
        file.add(open);
        file.add(save);
        file.addSeparator();
        file.add(export);
        file.add(loadCppPath);
        add(file);
    }

    private void createNewProject() {
        try {
            String path = folderDialog();
            String name = JOptionPane.showInputDialog("Name of the project: ");
            System.setProperty("user.dir", path);
            parent.loadProject(new Project(name, path));
            saveProject();
        } catch (ChooseFolderDialogCanceled chooseFolderDialogCanceled) {

        }
    }

    private void setPathToEngine() {
        String path = JOptionPane.showInputDialog("Input engine .exe path: ");
        if( new File(path).exists() == false) {
            JOptionPane.showMessageDialog(null, "File not found!");
            return;
        }
        PhotoshopExec.setPath(path);
    }

    private void exportProject() throws FileAlreadyExistsException, FileExtensionMissmatch, ProjectNotLoaded {
        JFileChooser fileChooser = new JFileChooser();
        fileChooser.setDialogTitle("Specify a file to save");

        int userSelection = fileChooser.showSaveDialog(parent);

        if (userSelection == JFileChooser.APPROVE_OPTION) {
            File fileToSave = fileChooser.getSelectedFile();
            if(fileToSave.exists())
                throw new FileAlreadyExistsException(fileToSave.getPath());
            if(!fileToSave.getName().contains(".bmp") && !fileToSave.getName().contains(".pam"))
                throw new FileExtensionMissmatch(fileToSave.getPath());

            exportToPath(fileToSave);
        }
    }
    private void exportToPath(File fileToSave) throws ProjectNotLoaded {
        new FileExporter(fileToSave.getPath(), parent.getProject()).start();
    }

    private String folderDialog() throws ChooseFolderDialogCanceled {
        JFileChooser folderChooser = new JFileChooser();
        folderChooser.setCurrentDirectory(new File(System.getProperty("user.home")));
        folderChooser.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
        folderChooser.showOpenDialog(parent);
        File selectedFolder = folderChooser.getSelectedFile();
        if(selectedFolder == null)
            throw new ChooseFolderDialogCanceled();
        return selectedFolder.getAbsolutePath();
    }

    public void saveProject() {
        try {
            ProjectSaver projectSaver = new ProjectSaver(parent.getProject());
            projectSaver.saveProject();
        } catch (ProjectNotLoaded | ParserConfigurationException | TransformerException e) {
            JOptionPane.showMessageDialog(parent, e.getMessage());
        }
    }

    private void openProject() {
        try {
            String path;// = folderDialog();
            path = "C:\\Users\\Dinbo-PC\\Desktop\\Paint\\Projekat"; // TODO: Revert
            checkIfFileExists(path + File.separator + "Project.xml");
            System.setProperty("user.dir", path);
            ProjectLoader projectLoader = new ProjectLoader(path + File.separator + "Project.xml");
            parent.loadProject(projectLoader.loadProject());
        } catch (ProjectFileNotFound | FileCorruptedException e) {
            JOptionPane.showMessageDialog(parent, e.getMessage());
        } /*catch (ChooseFolderDialogCanceled ignored) {
        }*/
    }

    private void checkIfFileExists(String s) throws ProjectFileNotFound {
        File f = new File(s);
        if(!f.exists() || f.isDirectory())
            throw new ProjectFileNotFound(s);
    }

    private static class FileExporter extends Thread {
        private String path;
        private Project project;
        public FileExporter(String path, Project project) {
            this.path = path;
            this.project = project;
        }

        @Override
        public void run() {
            try {
                PhotoshopExec exec = new PhotoshopExec();
                exec.addDestination(path);
                exec.addLayers(project.getAll_layers());
                exec.start();
                exec.join();
            } catch (InterruptedException e) {}
        }
    }
}

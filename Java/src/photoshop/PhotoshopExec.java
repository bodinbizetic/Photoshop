package photoshop;

import photoshop.exceptions.EngineNotLoaded;
import photoshop.layer.Layer;
import photoshop.operations.Operation;
import photoshop.project.Project;
import photoshop.project.ProjectSaver;
import photoshop.selection.Selection;

import javax.swing.*;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.TransformerException;
import java.io.File;
import java.io.IOException;
import java.util.LinkedList;
import java.util.List;

public class PhotoshopExec extends Thread{
    private static String cppFilePath = "";

    private String path;
    private List<Layer>     layers      = new LinkedList<>();
    private List<Operation> operations  = new LinkedList<>();
    private List<Selection> selections  = new LinkedList<>();
    private List<String>    args        = new LinkedList<>();
    private static int ID_Temp = 0;


    private boolean filterActive = false;
    public static void setPath(String path) {
        cppFilePath = "\"" + path + "\"";
    }

    public void setFilterActive(boolean filterActive) {
        this.filterActive = filterActive;
    }

    public void addLayers(List<Layer> l) {
        l.forEach(layer -> layers.add(layer));
//        layers.add(l);
    }

    public void addOperation(Operation op) {
        operations.add(op);
    }

    public void addSelections(List<Selection> s) {
        s.stream().filter(selection -> selection.isActive()).forEach(selection -> selections.add(selection));
    }
//
//    public void addSelection(Selection sel) {
//        selections.add(sel);
//    }

    private String getArgumentsList() {
        StringBuilder sb = new StringBuilder();
        sb.append(" ");
        sb.append(getCppArgList());
        sb.append(getFileList());
        sb.append(getOperationList());
        sb.append(getSelectionList());
        return sb.toString();
    }

    private String getSelectionList() {
        StringBuilder sb = new StringBuilder();
        selections.forEach(selection -> {
            try {
                String path = tempCopySelection(selection);
                sb.append(path);
                sb.append(" ");
            } catch (TransformerException e) {
                e.printStackTrace();
            } catch (ParserConfigurationException e) {
                e.printStackTrace();
            }
        });
        return sb.toString();
    }

    private String tempCopySelection(Selection selection) throws TransformerException, ParserConfigurationException {
        String path = ".temp" + File.separator + ID_Temp++ + ".sel";
        ProjectSaver.saveSelectionFile(path, selection);
        return path;
    }

    private String getOperationList() {
        StringBuilder bs = new StringBuilder();
        operations.forEach(operation -> {
            try {
                String path = tempCopyOperation(operation);
                bs.append(path);
                bs.append(" ");
            } catch (TransformerException e) {
                e.printStackTrace();
            } catch (ParserConfigurationException e) {
                e.printStackTrace();
            }
        });
        return bs.toString();
    }

    private String tempCopyOperation(Operation operation) throws TransformerException, ParserConfigurationException {
        String path = ".temp" + File.separator + ID_Temp++ + ".fun";
        ProjectSaver.saveOperationFile(path, operation);
        return path;
    }

    private String getFileList() {
        StringBuilder sb = new StringBuilder();
        layers.stream().filter(layer -> layer.isActive() || !filterActive).forEach(layer -> {
            sb.append(layer.getPath()).append(" ");
            if(layer.getOpacity() != 100)
                sb.append("--opacity " + layer.getOpacity() + " ");
        });
        return sb.toString();
    }

    private String getCppArgList() {
        StringBuilder sb = new StringBuilder();
        args.stream().forEach(arg -> sb.append(arg).append(" "));
        return sb.toString();
    }

    public void addDestination(String path) {
        args.add("-e");
        args.add(path);
    }
    @Override
    public void run() {
        try {
            if(cppFilePath == "" || new File(cppFilePath.substring(1, cppFilePath.length()-1)).exists() == false)
                throw new EngineNotLoaded();
            synchronized (this.getClass()) {
                //System.out.println("Starting " + System.getProperty("user.dir"));
                String command = cppFilePath + getArgumentsList();
                System.out.println(command);
                Process process = Runtime.getRuntime().exec(command + "", null, new File(System.getProperty("user.dir")));
                //System.out.println("Ending " + ;
                process.waitFor();
            }
        } catch (IOException | InterruptedException e) {
            System.out.println("Failed");
            e.printStackTrace();
        } catch (EngineNotLoaded engineNotLoaded) {
            JOptionPane.showMessageDialog(null, "Engine not loaded!");
        } finally {
            synchronized (this) {
                notifyAll();
            }
        }
    }

    public static void main(String[] args) throws InterruptedException {
        PhotoshopExec.setPath("\"C:\\Users\\Dinbo\\Desktop\\Photoshop\\C++\\x64\\Release\\Poop C++ Projekat.exe\"");
        PhotoshopExec exec = new PhotoshopExec();
        exec.start();
        for(int i=0; i<5; i++) {
            System.out.println("Step " + i);
            Thread.sleep(1000);
        }
    }
}

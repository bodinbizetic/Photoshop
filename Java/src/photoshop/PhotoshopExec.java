package photoshop;

import photoshop.layer.Layer;
import photoshop.operations.Operation;
import photoshop.selection.Selection;

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

//    public void addOperation(Operation op) {
//        operations.add(op);
//    }
//
//    public void addSelection(Selection sel) {
//        selections.add(sel);
//    }

    private String getArgumentsList() {
        StringBuilder sb = new StringBuilder();
        sb.append(" ");
        sb.append(getCppArgList());
        sb.append(getFileList());
        return sb.toString();
    }

    private String getFileList() {
        StringBuilder sb = new StringBuilder();
        layers.stream().filter(layer -> layer.isActive() || !filterActive).forEach(layer -> sb.append(layer.getPath()).append(" "));
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
            synchronized (this.getClass()) {
                System.out.println("Starting " + System.getProperty("user.dir"));
                String command = cppFilePath + getArgumentsList();
                System.out.println(command);
                Process process = Runtime.getRuntime().exec(command + "", null, new File(System.getProperty("user.dir")));
                System.out.println("Ending " + process.waitFor()); // TODO: remove System.out.println
            }
        } catch (IOException | InterruptedException e) {
            System.out.println("Failed"); //TODO: better fail if cpp program not found
            e.printStackTrace();
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

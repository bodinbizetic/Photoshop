package photoshop.project;

import photoshop.exceptions.FileCorruptedException;
import photoshop.exceptions.ImageNotLoadedException;
import photoshop.layer.Layer;
import photoshop.operations.Operation;
import photoshop.selection.Selection;

import java.util.ArrayList;
import java.util.List;

public class Project {

    private String path;
    private String name;
    private List<Selection> all_selections = new ArrayList<>();
    private List<Operation> all_operations = new ArrayList<>();
    private List<Layer> all_layers = new ArrayList<>();

    public Project(String name, String path) {
        this.path = path;
        this.name = name;
    }

    Project(List<Selection> all_selections, List<Operation> all_operations, List<Layer> all_layers, String name, String path) {
        this.all_selections = all_selections;
        this.all_operations = all_operations;
        this.all_layers = all_layers;
    }

//    public List<Selection> getAll_selections() {
//        return all_selections;
//    }
//
//    public List<Operation> getAll_operations() {
//        return all_operations;
//    }
//
    public List<Layer> getAll_layers() {
        return all_layers;
    }

    public void addLayer(Layer l) {
        synchronized (all_layers) {
            all_layers.add(l);
        }
    }

    public void removeLayer(Layer l) {
        synchronized (all_layers) {
            all_layers.remove(l);
        }
    }

    public static void main(String[] args) throws FileCorruptedException {
        String path = "C:\\Users\\Dinbo\\Desktop\\POOP C++\\Photoshop\\myProj\\Project.xml";
        ProjectLoader projectLoader = new ProjectLoader(path);
        Project p = projectLoader.loadProject();

        for(Layer l : p.all_layers)
            System.out.println(l.getName() + " " + l.getTempPath());
    }

    public void reloadLayers() {
        synchronized (all_layers) {
            all_layers.forEach(layer -> {
                try {
                    layer.loadImage();
                } catch (ImageNotLoadedException e) {

                }
            });
        }
    }
}

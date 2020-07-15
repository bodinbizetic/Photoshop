package photoshop.widgets;

import photoshop.PhotoshopExec;
import photoshop.exceptions.FileExtensionMissmatch;
import photoshop.exceptions.FileNameException;
import photoshop.exceptions.ImageNotLoadedException;
import photoshop.layer.Layer;
import photoshop.layer.UserLayer;
import photoshop.project.Project;

import javax.swing.*;
import javax.swing.filechooser.FileNameExtensionFilter;
import java.awt.*;
import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class LayerTab extends JPanel {
    private static int LAYER_INDEX=0;
    private Project project;

    private JList<Layer> layerJList;
    private DrawingPanel drawingPanel;
    private Checkbox activeCB;
    private JSlider slider;

    private TextField newLayerName = new TextField();

    private Label valueLabel = new Label("Value: 100");
    private Layer combinedLayers;

    public LayerTab(DrawingPanel drawingPanel) {
        this.drawingPanel = drawingPanel;
        setLayout(new GridLayout(4, 1));
        populateLayer();
    }

    private void populateLayer() {
        layerJList = new JList<>();
        layerJList.addListSelectionListener(e -> {
            Layer activeLayer = layerJList.getSelectedValue();
            if(activeLayer == null)
                return;
            activeCB.setState(activeLayer.isActive());
            setSlider(activeLayer.getOpacity());
        });
        add(layerJList);

        addControls();

    }

    private void addControls() {
        JPanel allControls = new JPanel();
        allControls.setLayout(new FlowLayout());
        addButtonsPanel(allControls);
        addSliderPanel(allControls);
        addCreateLayerPanel(allControls);

        add(allControls);
    }

    private void addCreateLayerPanel(JPanel allControls) {
        JPanel controls = new JPanel();
        JPanel buttons = new JPanel();
        controls.add(new Label("Name: "));
        newLayerName.setPreferredSize(new Dimension(130, 20));
        controls.add(newLayerName);
        Button addLayer         = new Button("Add layer");
        Button deleteSelected   = new Button("Delete selected");
        addLayer.addActionListener(ev->new LayerTabCreater().start());
        deleteSelected.addActionListener(ev-> deleteSelectedLayer());

        buttons.add(addLayer);
        buttons.add(deleteSelected);

        allControls.add(controls);
        allControls.add(buttons);
    }

    private void addLayer() {
        if(project == null)
            return;

        try {
            String name = (newLayerName.getText().isEmpty() ? "Layer" + ++LAYER_INDEX : newLayerName.getText());
            String path = getLayerPath(name);
            Layer newLayer = new UserLayer(name, path, 100, true);
            project.addLayer(newLayer);
            PhotoshopExec ph = new PhotoshopExec();
            ph.addLayers(project.getAll_layers());
            ph.start();
            ph.join();
        } catch(FileExtensionMissmatch | FileNameException | ImageNotLoadedException e) {
            JOptionPane.showMessageDialog(this, e.getMessage());
        }catch (IOException e) {
            JOptionPane.showMessageDialog(this, "File with that name already exists");
        } catch(InterruptedException ignore) {}
    }

    private String getLayerPath(String newName) throws FileExtensionMissmatch, FileNameException, IOException {
        String src_path = getLayerPathDialog();
        String dst_path = "resource" + File.separator + newName + getExtension(src_path);
        Files.copy(Paths.get(src_path), Paths.get(System.getProperty("user.dir") + File.separator + dst_path));
        return dst_path;
    }

    private String getExtension(String path) throws FileNameException {
        Pattern pattern = Pattern.compile(".*\\.(.*)");
        Matcher matcher = pattern.matcher(path);
        if(matcher.find())
            return "." + matcher.group(1);
        throw new FileNameException(path);
    }

    private String getLayerPathDialog() throws FileExtensionMissmatch {
        JFileChooser jf = new JFileChooser();
        jf.addChoosableFileFilter(new FileNameExtensionFilter("*.bmp", "bmp"));
        jf.addChoosableFileFilter(new FileNameExtensionFilter("*.pam", "pam"));
        jf.setCurrentDirectory(new File("C:\\Users\\Dinbo\\Desktop\\Paint")); // TODO: Change to be System.getProperty("user.dir");
        jf.showOpenDialog(this);
        File file = jf.getSelectedFile();
        if(!file.getPath().contains(".bmp") && !file.getPath().contains(".pam"))
            throw new FileExtensionMissmatch(file.getPath());
        return jf.getSelectedFile().getPath();
    }

    private void deleteSelectedLayer() {
        try {
            Layer toDelete = layerJList.getSelectedValue();
            project.removeLayer(toDelete);
            toDelete.delete();
            loadLayers();
        }catch(NullPointerException ignored) {}
    }

    private void setSlider(int value) {
        slider.setValue(value);
        valueLabel.setText("Value: " + value);
    }

    private void addSliderPanel(JPanel allControls) {
        JPanel sliderPanel = new JPanel();
        slider = new JSlider(JSlider.HORIZONTAL, 0, 100, 100);
        slider.addChangeListener(e -> {

            int value = 0;
            try {
                value = slider.getValue();
                Layer activeLayer = layerJList.getSelectedValue();
                activeLayer.setOpacity(value);

            } catch (NullPointerException ignored) {
            } finally {
                valueLabel.setText("Value: " + value);
            }
        });
        sliderPanel.add(slider);
        sliderPanel.add(valueLabel);

        allControls.add(sliderPanel);
    }

    private void addActiveControl(JPanel controls) {
        activeCB = new Checkbox("Active");
        activeCB.addItemListener(e -> {
            try {
                Layer activeLayer = layerJList.getSelectedValue();
                activeLayer.setActive(activeCB.getState());
            }catch (NullPointerException ignored) {}
        });
        controls.add(activeCB);
    }

    private void addButtonsPanel(JPanel allControls) {
        JPanel controls = new JPanel();
        controls.setLayout(new FlowLayout());
        Button showOne = new Button("Show selected");
        Button showAll = new Button("Show combined");
        controls.add(showOne);
        controls.add(showAll);

        showOne.addActionListener(e->{
            drawingPanel.clearLayers();
            drawingPanel.addLayer(layerJList.getSelectedValue());
            drawingPanel.repaint();
        });

        showAll.addActionListener(e-> new LayerTabCombiner().start());

        addActiveControl(controls);
        allControls.add(controls);
    }

    public void loadProject(Project project) {
        closeProject();
        this.project = project;
        loadLayers();
    }

    public void closeProject() {
        this.project = null;
        layerJList.setModel(new DefaultListModel<>());
        drawingPanel.clearRectangles();
        drawingPanel.clearSelection();
        drawingPanel.clearLayers();
    }

    private synchronized void loadLayers() {
        List<Layer> all_layers = project.getAll_layers();
        DefaultListModel layerList = new DefaultListModel<>();
        all_layers.forEach(layerList::addElement);
        layerJList.setModel(layerList);
    }

    public static final String LAYER_COMBINE_PATH = ".temp" + File.separator + "combined.bmp";

    private void combineLayers() {
        File combinedLayersFile = new File(System.getProperty("user.dir"), LAYER_COMBINE_PATH); //TODO: if .temp does not exist
        PhotoshopExec ps = new PhotoshopExec();
        ps.setFilterActive(true);
        ps.addLayers(project.getAll_layers());
        ps.addDestination(combinedLayersFile.getPath());
        ps.start();

        try {
            ps.join();
            combinedLayers = new Layer("CombineLayer", combinedLayersFile.getPath());
        } catch (InterruptedException ignore) {} catch (ImageNotLoadedException e) {
            JOptionPane.showMessageDialog(this, "Critical error: " + e.getMessage());
        }
    }

    private void showCombinedLayer() {
        if(combinedLayers == null)
            return;
        drawingPanel.clearLayers();
        drawingPanel.addLayer(combinedLayers);
        drawingPanel.repaint();
    }

    private class LayerTabCreater extends Thread {

        @Override
        public void run() {
            if(project == null)
                return;
            addLayer();
            loadLayers();
            project.reloadLayers();
        }
    }

    private class LayerTabCombiner extends Thread {
        @Override
        public void run() {
            if(project == null)
                return;
            combineLayers();
            showCombinedLayer();
        }
    }
}

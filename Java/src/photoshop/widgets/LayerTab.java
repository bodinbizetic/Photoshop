package photoshop.widgets;

import photoshop.layer.Layer;
import photoshop.project.Project;

import javax.swing.*;
import java.awt.*;
import java.util.List;

public class LayerTab extends JPanel {

    private Project project;

    private JList<Layer> layerJList;
    private DrawingPanel drawingPanel;
    private Checkbox activeCB;
    private JSlider slider;

    private TextField newLayerName = new TextField();

    private Label valueLabel = new Label("Value: 100");

    public LayerTab(DrawingPanel drawingPanel) {
        this.drawingPanel = drawingPanel;
        setLayout(new GridLayout(4, 1));
        populateLayer();
    }

    private void populateLayer() {
        layerJList = new JList<>();
        layerJList.addListSelectionListener(e -> {
            Layer activeLayer = layerJList.getSelectedValue();
            activeCB.setState(activeLayer.isActive());
            setSlider(activeLayer.getOpacity());
        });
        add(layerJList);

        addButtonsPanel();
        addSliderPanel();
        addCreateLayerPanel();
    }

    private void addCreateLayerPanel() {
        JPanel controls = new JPanel();

        controls.add(new Label("Name: "));
        controls.add(newLayerName);
        Button deleteSelected = new Button("Delete selected");
        deleteSelected.addActionListener(ev-> {
            deleteSelectedLayer();
        });

        controls.add(deleteSelected);

        add(controls);
    }

    private void deleteSelectedLayer() {
        try {
            Layer toDelete = layerJList.getSelectedValue();
            List<Layer> all_layers = project.getAll_layers();
            all_layers.remove(toDelete);
            toDelete.delete();
            loadLayers();
        }catch(NullPointerException exception) {}
    }

    private void setSlider(int value) {
        slider.setValue(value);
        valueLabel.setText("Value: " + value);
    }

    private void addSliderPanel() {
        JPanel sliderPanel = new JPanel();
        slider = new JSlider(JSlider.HORIZONTAL, 0, 100, 100);
        slider.addChangeListener(e -> {
            try {
                int value = slider.getValue();
                Layer activeLayer = layerJList.getSelectedValue();
                activeLayer.setOpacity(value);
                valueLabel.setText("Value: " + value);
            }catch (NullPointerException ex) {}
        });
        sliderPanel.add(slider);
        sliderPanel.add(valueLabel);

        add(sliderPanel);
    }

    private void addActiveControl(JPanel controls) {
        activeCB = new Checkbox("Active");
        activeCB.addItemListener(e -> {
            try {
                Layer activeLayer = layerJList.getSelectedValue();
                activeLayer.setActive(activeCB.getState());
            }catch (NullPointerException ex) {}
        });
        controls.add(activeCB);
    }

    private void addButtonsPanel() {
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

        addActiveControl(controls);
        add(controls);
    }

    public void loadProject(Project project) {
        this.project = project;
        loadLayers();
    }

    private void loadLayers() {
        List<Layer> all_layers = project.getAll_layers();
        DefaultListModel layerList = new DefaultListModel<>();
        all_layers.forEach(layerList::addElement);
        layerJList.setModel(layerList);
    }

    public void closeLayers() {
        ((DefaultListModel)layerJList.getModel()).clear();
        project = null;
    }
}

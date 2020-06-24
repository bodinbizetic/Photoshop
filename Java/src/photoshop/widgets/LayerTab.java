package photoshop.widgets;

import photoshop.layer.Layer;
import photoshop.project.Project;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ItemEvent;
import java.util.List;

public class LayerTab extends JPanel {

    private JList<Layer> layerJList;
    private DrawingPanel drawingPanel;
    private Checkbox activeCB;
    private JSlider slider;
    private Label valueLabel = new Label("Value: 100");
    public LayerTab(DrawingPanel drawingPanel) {
        this.drawingPanel = drawingPanel;
        setLayout(new GridLayout(3, 1));
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

        addButtons();
        addSlider();
    }

    private void setSlider(int value) {
        slider.setValue(value);
        valueLabel.setText("Value: " + value);
    }

    private void addSlider() {
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

    private void addButtons() {
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

    public void loadLayers(List<Layer> all_layers) {
        DefaultListModel layerList = new DefaultListModel<>();
        all_layers.forEach(layerList::addElement);
        layerJList.setModel(layerList);
    }

    public void closeLayers() {
        ((DefaultListModel)layerJList.getModel()).clear();
    }
}

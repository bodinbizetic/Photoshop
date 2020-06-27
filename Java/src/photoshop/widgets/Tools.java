package photoshop.widgets;

import photoshop.layer.Layer;
import photoshop.project.Project;

import javax.swing.*;
import java.awt.*;

public class Tools extends JTabbedPane {

    private static final Color bgColor = new Color(0xFFFFFF);

    private LayerTab layerPanel;
    private OperationTab operationPanel;
    private JPanel selectionPanel;

    private JList layer_list = new JList();
    private DrawingPanel drawingPanel;
    public Tools(DrawingPanel drawingPanel) {
        super();
        this.drawingPanel = drawingPanel;
        addOperationPanel();
        addLayerPanel();
        addSelectionPanel();
        setBackground(Color.LIGHT_GRAY);
    }

    private void addSelectionPanel() {
        selectionPanel = new JPanel();
//        selectionPanel.setBackground(bgColor);
        addTab("Selections", selectionPanel);
    }

    private void addLayerPanel() {
        layerPanel = new LayerTab(drawingPanel);

        addTab("Layers", layerPanel);
    }

    private void addOperationPanel() {
        operationPanel = new OperationTab();
//        selectionPanel.setBackground(Color.WHITE);
        addTab("Operations", operationPanel);
    }

    public void loadProject(Project project) {
        layerPanel.loadProject(project);
    }
}

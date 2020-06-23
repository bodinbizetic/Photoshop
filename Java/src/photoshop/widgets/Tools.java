package photoshop.widgets;

import javax.swing.*;
import java.awt.*;

public class Tools extends JTabbedPane {

    private static final Color bgColor = new Color(0xFFFFFF);

    private JPanel layerPanel;
    private JPanel operationPanel;
    private JPanel selectionPanel;

    public Tools() {
        super();

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
        layerPanel = new JPanel();
//        selectionPanel.setBackground(bgColor);
        addTab("Layers", layerPanel);
    }

    private void addOperationPanel() {
        operationPanel = new JPanel();
//        selectionPanel.setBackground(Color.WHITE);
        addTab("Operations", operationPanel);
    }
}

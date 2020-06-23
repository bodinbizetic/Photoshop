package photoshop;

import photoshop.widgets.PhotoShopMenuBar;
import photoshop.widgets.Tools;

import javax.swing.*;
import java.awt.*;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

public class MainWindow  extends Frame {
    private static final int DEFAULT_WINDOW_WIDTH = 1000;
    private static final int DEFAULT_WINDOW_HEIGHT = 700;

    private JPanel drawingPanel;
    private JTabbedPane toolPanel;

    public MainWindow() {
        super("Photoshop");
        setBounds(0, 0, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
        setLayout(new BorderLayout());

        addClosingOption();
        addMenuBarOptions();
        addDrawPanel();
        addToolPanel();
        setBackground(Color.WHITE);
        setVisible(true);
    }

    private void addToolPanel() {
        toolPanel = new Tools();
        toolPanel.setPreferredSize(new Dimension(300, getHeight()));
        add(toolPanel, BorderLayout.EAST);
    }

    private void addDrawPanel() {
        drawingPanel = new JPanel();
        add(drawingPanel, BorderLayout.CENTER);
    }

    private void addMenuBarOptions() {
        PhotoShopMenuBar menuBar = new PhotoShopMenuBar();

        setMenuBar(menuBar);
    }

    private void addClosingOption() {
        addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                dispose();
            }
        });
    }

    public static void main(String[] args) {
        new MainWindow();
    }
}

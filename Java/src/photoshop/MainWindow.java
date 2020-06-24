package photoshop;

import photoshop.project.Project;
import photoshop.widgets.DrawingPanel;
import photoshop.widgets.PhotoShopMenuBar;
import photoshop.widgets.Tools;

import javax.swing.*;
import java.awt.*;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

public class MainWindow  extends Frame {
    private static final int DEFAULT_WINDOW_WIDTH = 1000;
    private static final int DEFAULT_WINDOW_HEIGHT = 700;

    private DrawingPanel drawingPanel;
    private Tools toolPanel;

    private Project project;

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
        toolPanel = new Tools(drawingPanel);
        toolPanel.setPreferredSize(new Dimension(300, getHeight()));
        add(toolPanel, BorderLayout.EAST);
    }

    private void addDrawPanel() {

        drawingPanel = new DrawingPanel();

        JScrollPane scrollPane = new JScrollPane(drawingPanel);
        scrollPane.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
        scrollPane.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED);
        scrollPane.setBounds(50, 30, 300, 50);
        JPanel contentPane = new JPanel();
        contentPane.add(scrollPane);
        add(scrollPane, BorderLayout.CENTER);
    }

    private void addMenuBarOptions() {
        PhotoShopMenuBar menuBar = new PhotoShopMenuBar(this);

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

    public void loadProject(Project project) {
        this.project = project;
        toolPanel.loadProject(project);
    }

    public static void main(String[] args) {
        new MainWindow();
    }
}

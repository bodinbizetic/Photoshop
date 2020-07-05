package photoshop.widgets;

import photoshop.layer.Layer;
import photoshop.selection.Rectangle;
import photoshop.selection.Selection;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

public class DrawingPanel extends JPanel{
    private List<Layer> to_Draw = new LinkedList<>();
    private List<Selection> selected = new LinkedList<>();
    private List<Rectangle> selected_rectangles = new LinkedList<>();
    private BufferedImage prevImage;
    public synchronized void addLayer(Layer l) {
        to_Draw.add(l);
    }

    public synchronized void clearLayers() {
        to_Draw.clear();
    }

    public synchronized void addSelection(Selection s) {
        selected.add(s);
    }

    public synchronized void clearSelection() {
        selected.clear();
    }

    public synchronized void addRectangle(Rectangle r) {
        selected_rectangles.add(r);
    }

    public synchronized void clearRectangles() {
        selected_rectangles.clear();
    }

        @Override
    public void paint(Graphics g) {
        super.paint(g);
        paintImage(g);
        paintSelections(g);
        paintRectnagles(g);
    }

    private void paintSelections(Graphics g) {
        if(to_Draw.isEmpty())
            return;
        selected.forEach(selection -> {
            List<Rectangle> rectangles = selection.getAll_rectangles();
            rectangles.forEach(rectangle -> paintRectangle(g, rectangle, false));
        });
    }

    private void paintRectnagles(Graphics g) {
        if(to_Draw.isEmpty())
            return;
        selected_rectangles.forEach(rectangle -> {
            paintRectangle(g, rectangle, true);
        });
    }

    private void paintRectangle(Graphics g, Rectangle rectangle, boolean hasBorder) {
        Color old = g.getColor();
        Color newColor = new Color(240, 240, 240, 127);
        g.setColor(newColor);
        g.fillRect(rectangle.getX(), rectangle.getY(), rectangle.getWidth(), rectangle.getHeight());
        g.setColor(old);

        if(hasBorder) {
            Graphics2D g2 = (Graphics2D) g;
            g2.setStroke(new BasicStroke(3));
            g2.drawRect(rectangle.getX(), rectangle.getY(), rectangle.getWidth(), rectangle.getHeight());
        }
    }

    private void paintImage(Graphics g) {
        if(to_Draw.isEmpty() == false) {
            Layer first = to_Draw.get(0);
            if(first == null)
                return;
            BufferedImage image = first.getImage();
            setPreferredSize(new Dimension(image.getWidth(), image.getHeight()));
            revalidate();
            g.drawImage(image, 0, 0, null);
        }
    }
}

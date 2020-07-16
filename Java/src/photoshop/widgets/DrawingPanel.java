package photoshop.widgets;

import photoshop.layer.Layer;
import photoshop.selection.MouseRectangleSelection;
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
    public enum MouseAction {
        SELECTING
    }


    private MouseAction currentAction = MouseAction.SELECTING;

    private List<Layer> to_Draw = new LinkedList<>();
    private List<Selection> selected = new LinkedList<>();
    private List<Rectangle> selected_rectangles = new LinkedList<>();
    private MouseRectangleSelection mouseSelection;
    private BufferedImage prevImage;

    public void setCurrentAction(MouseAction currentAction) {
        this.currentAction = currentAction;
    }

    public MouseAction getCurrentAction() {
        return currentAction;
    }

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

    public void setMouseSelection(MouseRectangleSelection mouseSelection) {
        this.mouseSelection = mouseSelection;
    }

    @Override
    public void paint(Graphics g) {
        super.paint(g);
        paintImage(g);
        paintSelections(g);
        paintRectnagles(g);
        paintMouseSelection(g);
    }

    private void paintMouseSelection(Graphics g) {
        if(currentAction != MouseAction.SELECTING)
            return;
        if(to_Draw.isEmpty())
            return;
        if(mouseSelection == null)
            return;
        Rectangle rectangle = mouseSelection.getRectangle();
        if(rectangle.getHeight() == 0 || rectangle.getHeight() == 0)
            return;
        paintRectangle(g, rectangle, false, false);
        paintBorder(g, rectangle, new Color(Color.RED.getRGB()), true);
    }

    private void paintSelections(Graphics g) {
        if(to_Draw.isEmpty())
            return;
        selected.forEach(selection -> {
            List<Rectangle> rectangles = selection.getAll_rectangles();
            rectangles.forEach(rectangle -> paintRectangle(g, rectangle, true, true));
        });

    }

    private void paintRectnagles(Graphics g) {
        if(to_Draw.isEmpty())
            return;
        selected_rectangles.forEach(rectangle -> {
            paintRectangle(g, rectangle, true, false);
        });
    }

    private void paintRectangle(Graphics g, Rectangle rectangle, boolean hasBorder, boolean isDashed) {
        Color old = g.getColor();
        Color newColor = new Color(240, 240, 240, 127);
        g.setColor(newColor);
        g.fillRect(rectangle.getX(), rectangle.getY(), rectangle.getWidth(), rectangle.getHeight());
        g.setColor(old);

        if(hasBorder) {
                Graphics2D g2 = (Graphics2D) g;
                float[] dash1 = { 2f, 0f, 2f };
                Stroke dashed = new BasicStroke(1, BasicStroke.CAP_BUTT, BasicStroke.JOIN_ROUND,1.0f, dash1,2f);
                Stroke old1 = g2.getStroke();
                g2.setStroke(dashed);
                paintBorder(g2, rectangle, new Color(Color.BLACK.getRGB()), isDashed);
                g2.setStroke(old1);
               // paintBorder(g, rectangle, new Color(Color.BLACK.getRGB()));
        }
    }

    private void paintBorder(Graphics g, Rectangle rectangle, Color borderColor, boolean isDahsed) {
        Graphics2D g2 = (Graphics2D) g;
        g.setColor(borderColor);
        float[] dash1 = { 2f, 0f, 2f };
        Stroke dashed = (isDahsed ? new BasicStroke(1, BasicStroke.CAP_BUTT, BasicStroke.JOIN_ROUND,1.0f, dash1,2f) : new BasicStroke(3));
        Stroke old1 = g2.getStroke();
        g2.setStroke(dashed);
        g2.drawRect(rectangle.getX(), rectangle.getY(), rectangle.getWidth(), rectangle.getHeight());
        g2.setStroke(old1);
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

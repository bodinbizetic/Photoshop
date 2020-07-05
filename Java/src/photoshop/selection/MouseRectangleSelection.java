package photoshop.selection;

import photoshop.widgets.DrawingPanel;
import photoshop.widgets.SelectionTab;

import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;

public class MouseRectangleSelection implements MouseListener, MouseMotionListener {
    private final DrawingPanel drawingPanel;
    private final SelectionTab selectionTab;
    private int startX;
    private int startY;

    private int endX;
    private int endY;

    public MouseRectangleSelection(DrawingPanel drawingPanel, SelectionTab selectionTab) {
        this.drawingPanel = drawingPanel;
        this.selectionTab = selectionTab;
        drawingPanel.setMouseSelection(this);
    }

    @Override
    public void mouseClicked(MouseEvent e) {

    }

    @Override
    public void mousePressed(MouseEvent e) {
        startX = e.getX();
        startY = e.getY();
    }

    @Override
    public void mouseReleased(MouseEvent e) {

    }

    @Override
    public void mouseEntered(MouseEvent e) {

    }

    @Override
    public void mouseExited(MouseEvent e) {

    }

    @Override
    public void mouseDragged(MouseEvent e) {
        endX = e.getX();
        endY = e.getY();
        drawingPanel.repaint();
    }

    @Override
    public void mouseMoved(MouseEvent e) {

    }

    public Rectangle getRectangle() {
        return new Rectangle(startX, startY, endX-startX, endY-startY);
    }
}

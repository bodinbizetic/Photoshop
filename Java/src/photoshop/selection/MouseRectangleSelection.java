package photoshop.selection;

import photoshop.widgets.DrawingPanel;
import photoshop.widgets.SelectionTab;

public class MouseRectangleSelection {
    private final DrawingPanel drawingPanel;
    private final SelectionTab selectionTab;
    private int startX;
    private int startY;

    public MouseRectangleSelection(DrawingPanel drawingPanel, SelectionTab selectionTab) {
        this.drawingPanel = drawingPanel;
        this.selectionTab = selectionTab;
    }

}

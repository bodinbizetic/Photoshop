package photoshop.widgets;

import photoshop.layer.Layer;
import photoshop.selection.Selection;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class DrawingPanel extends JPanel{
    private List<Layer> to_Draw = new ArrayList<>();
    private List<Selection> selected = new ArrayList<>();
    private BufferedImage prevImage;
    public synchronized void addLayer(Layer l) {
        to_Draw.add(l);
    }

    public synchronized void clearLayers() {
        to_Draw.clear();
    }

    @Override
    public void paint(Graphics g) {
        super.paint(g);
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

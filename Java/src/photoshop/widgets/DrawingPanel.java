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

public class DrawingPanel extends JPanel implements Runnable{
    private List<Layer> to_Draw = new ArrayList<>();
    private List<Selection> selected = new ArrayList<>();

    public synchronized void addLayer(Layer l) {
        to_Draw.add(l);
    }

    public synchronized void clearLayers() {
        to_Draw.clear();
    }

    @Override
    public void run() {

    }

    @Override
    public void paint(Graphics g) {
        super.paint(g);
        if(to_Draw.isEmpty() == false) {
            Layer first = to_Draw.get(0);
            if(first == null)
                return;
            try {
                File file = new File(System.getProperty("user.dir"), first.getPath());
                BufferedImage image = ImageIO.read(file);
                setPreferredSize(new Dimension(image.getWidth(), image.getHeight()));
                g.drawImage(image, 0, 0, null);
            } catch (IOException e) {
                System.out.println("Image " + first.getPath() + " not found");
                e.printStackTrace();
            }
        }
    }
}

package photoshop.project;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;
import photoshop.exceptions.FileCorruptedException;
import photoshop.layer.Layer;
import photoshop.operations.Operation;
import photoshop.selection.Selection;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class ProjectLoader {

    private String path;
    private List<Layer> all_layers = new ArrayList<>();
    private List<Selection> all_selections = new ArrayList<>();
    private List<Operation> all_operations = new ArrayList<>();

    public ProjectLoader(String path) {
        this.path = path;
    }

    public Project loadProject() throws FileCorruptedException {
        Document document = openXMLDocument();
        Element root = document.getDocumentElement();

        loadLayers(root);
        return new Project(all_selections, all_operations, all_layers, root.getAttribute("name"), path);
    }

    private void loadLayers(Element root) {
        Element layers = (Element) root.getElementsByTagName("Layers").item(0);
        if(layers == null)
            return;

        extractAllLayers(layers);
    }

    private void extractAllLayers(Element layers) {
        NodeList nodeList = layers.getElementsByTagName("Layer");
        for(int i=0; i < nodeList.getLength(); i++){
            extractLayer((Element) nodeList.item(i));
        }
    }

    private void extractLayer(Element element) {
        String name = element.getAttribute("name");
        String path = element.getAttribute("path");
        int opacity = Integer.parseInt(element.getAttribute("opacity"));
        boolean active = (element.getAttribute("active").equals("true"));
        all_layers.add(new Layer(name, path, opacity, active));
    }

    private Document openXMLDocument() throws FileCorruptedException {
        try {
            DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
            DocumentBuilder builder = factory.newDocumentBuilder();
            return builder.parse(new File( path ));
        } catch (ParserConfigurationException | IOException | SAXException e) {
            e.printStackTrace();
            throw new FileCorruptedException(path);
        }
    }

}

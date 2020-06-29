package photoshop.project;

import org.w3c.dom.*;
import org.xml.sax.SAXException;
import photoshop.exceptions.FileCorruptedException;
import photoshop.exceptions.ImageNotLoadedException;
import photoshop.layer.Layer;
import photoshop.layer.UserLayer;
import photoshop.operations.ComplexOperation;
import photoshop.operations.DiadicOperation;
import photoshop.operations.Operation;
import photoshop.selection.Selection;

import javax.swing.*;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;
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
        loadOperations(root);
        return new Project(all_selections, all_operations, all_layers, root.getAttribute("name"), path);
    }

    private void loadOperations(Element root) {
        NodeList operations = root.getElementsByTagName("Operations");
        Node op = operations.item(0);
        if(op == null)
            return;

        NodeList list = op.getChildNodes();
        for(int i=0; i<list.getLength(); i++) {
            try {
                if(list.item(i).getNodeType() == Node.ELEMENT_NODE) {
                    Operation oper = loadSingleOperation(list.item(i));
                    all_operations.add(oper);
                    System.out.println(list.item(i).getNodeName());
                }
            } catch (FileCorruptedException e) {
                JOptionPane.showMessageDialog(null, e.getMessage());
            }
        }
    }

    private Operation loadSingleOperation(Node item) throws FileCorruptedException {
        String path = getSingleOperationPath(item);
        XMLFormater xml = new XMLFormater(path, "Operation");
        HashMap<String, String> header = xml.getHeaderValues();
        final List<Operation> operation_list = new LinkedList<>();
        xml.getBodyValuesList().forEach(val -> {
            operation_list.add(new DiadicOperation(val.get("name"), "", ()-> Integer.parseInt(val.get("arg")))); // TODO: Use already made operations
        });
        return new ComplexOperation(header.get("name"), path, operation_list);
    }

    private String getSingleOperationPath(Node item) {
        NamedNodeMap map = item.getAttributes();
        Node node = map.item(0);
        String path = node.getNodeValue();
        return path;
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
        try {
            all_layers.add(new UserLayer(name, path, opacity, active));
        } catch (ImageNotLoadedException e) {
            System.out.println("Image not loaded");
        }
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

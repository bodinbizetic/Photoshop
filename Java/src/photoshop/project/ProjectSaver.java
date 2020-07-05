package photoshop.project;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import photoshop.exceptions.FileCorruptedException;
import photoshop.exceptions.ImageNotSaved;
import photoshop.layer.UserLayer;
import photoshop.operations.DiadicOperation;
import photoshop.operations.MonadicOperation;
import photoshop.operations.Operation;
import photoshop.selection.Selection;

import javax.swing.*;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.*;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import java.io.File;
import java.util.LinkedList;

public class ProjectSaver {

    private Project project;

    public ProjectSaver(Project project) {
        this.project = project;
    }

    private static Document createDocument() throws ParserConfigurationException {
        DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
        DocumentBuilder builder = factory.newDocumentBuilder();
        Document doc = builder.newDocument();
        return doc;
    }

    public static void saveSelectionFile(String path, Selection selection) throws ParserConfigurationException, TransformerException {
        File output = new File(System.getProperty("user.dir"), path);
        Document doc = createDocument();

        createSelectionXml(doc, selection);

        saveXmlFile(doc, output);
    }

    private static void createSelectionXml(Document doc, Selection selection) {
        Element root = doc.createElement("Selection");
        root.setAttribute("name", selection.getName());
        root.setAttribute("active", String.valueOf(selection.isActive()));
        doc.appendChild(root);
        addSelectionChildren(doc, root, selection);
    }

    private static void addSelectionChildren(Document doc, Element root, Selection selection) {
        selection.getAll_rectangles().forEach(rec -> {
            Element node = doc.createElement("Rectangle");
            node.setAttribute("height", String.valueOf(rec.getHeight()));
            node.setAttribute("width", String.valueOf(rec.getWidth()));
            node.setAttribute("x", String.valueOf(rec.getX()));
            node.setAttribute("y", String.valueOf(rec.getY()));
            root.appendChild(node);
        });
    }

    public static void saveOperationFile(String path, Operation operation) throws ParserConfigurationException, TransformerException {
        File output = new File(System.getProperty("user.dir"), path);
        Document doc = createDocument();

        createOperationXml(doc, operation);
        
        saveXmlFile(doc, output);
    }

    private static void saveXmlFile(Document doc, File myFile) throws TransformerException {
        TransformerFactory transformerFactory = TransformerFactory.newInstance();
        Transformer transf = transformerFactory.newTransformer();

        transf.setOutputProperty(OutputKeys.ENCODING, "UTF-8");
        transf.setOutputProperty(OutputKeys.INDENT, "yes");
        transf.setOutputProperty("{http://xml.apache.org/xslt}indent-amount", "2");
        transf.setOutputProperty("omit-xml-declaration", "yes");

        DOMSource source = new DOMSource(doc);


        StreamResult file = new StreamResult(myFile);
        transf.transform(source, file);
    }

    private static void createOperationXml(Document doc, Operation operation) {
        Element root = doc.createElement("CustomOperation");
        root.setAttribute("name", operation.getName());
        doc.appendChild(root);
        addOperationsChildren(doc, root, operation);
    }

    private static void addOperationsChildren(Document doc, Element root, Operation operation) {
        operation.getList().forEach(op -> {
            Element node = doc.createElement("Operation");
            node.setAttribute("arg", Integer.toString(op.getParametar()));
            node.setAttribute("name", op.getName());
            root.appendChild(node);
        });
    }

    public void saveProject() throws ParserConfigurationException, TransformerException {
//        File projectFile = new File(System.getProperty("user.dir"), project.getPath());
        Document doc = createDocument();

        Element root = doc.createElement("Project");
        root.setAttribute("name", project.getName());

        renewFolders();
        saveLayers(doc, root);
        saveOperations(doc, root);
        saveSelections(doc, root);

        doc.appendChild(root);
        saveXmlFile(doc, new File(System.getProperty("user.dir"), "Project.xml"));
    }

    private void saveOperations(Document doc, Element root) {
        Element all_operations_node = doc.createElement("Operations");
        project.getAll_operations().forEach(operation -> {
            try {
                saveOperationFile(operation.getPath(), operation);
                Element operation_node = doc.createElement("Operation");
                operation_node.setAttribute("path", operation.getPath());
                all_operations_node.appendChild(operation_node);
            } catch (TransformerException | ParserConfigurationException e) {
                JOptionPane.showMessageDialog(null, e.getMessage());
            }
        });
        root.appendChild(all_operations_node);
    }

    private void saveSelections(Document doc, Element root) {
        Element all_selections_node = doc.createElement("Selections");
        project.getAll_Selections().forEach(selection -> {
            try {
                saveSelectionFile(selection.getPath(), selection);
                Element operation_node = doc.createElement("Selection");
                operation_node.setAttribute("path", selection.getPath());
                all_selections_node.appendChild(operation_node);
            } catch (TransformerException | ParserConfigurationException e) {
                JOptionPane.showMessageDialog(null, e.getMessage());
            }
        });
        root.appendChild(all_selections_node);
    }

    private void renewFolders() {
        String[] paths = {"resource", "operations", "selections"};
        for(String path : paths) {
            renewFolder(path);
        }
    }

    private void renewFolder(String path) {
        File tempFolder = new File(System.getProperty("user.dir"), path);
        if(!tempFolder.exists()) {
            tempFolder.mkdir();
            return;
        }
        File[] allContents = tempFolder.listFiles();
        if (allContents != null) {
            for (File file : allContents) {
                file.delete();
            }
        }
        tempFolder.delete();
        tempFolder.mkdir();
    }

    private void saveLayers(Document doc, Element root) {
        Element all_layers_node = doc.createElement("Layers");
        project.getAll_layers().forEach(layer -> {
            try {
                if (layer instanceof UserLayer) {
                    UserLayer uLayer = (UserLayer) layer;
                    uLayer.saveLayer();
                    Element layer_node = doc.createElement("Layer");
                    layer_node.setAttribute("name", layer.getName());
                    layer_node.setAttribute("path", layer.getRelativePath());
                    layer_node.setAttribute("opacity", String.valueOf(layer.getOpacity()));
                    layer_node.setAttribute("active", String.valueOf(layer.isActive()));
                    all_layers_node.appendChild(layer_node);
                }
            } catch (ImageNotSaved imageNotSaved) {
                JOptionPane.showMessageDialog(null, imageNotSaved.getMessage());
            }
        });
        root.appendChild(all_layers_node);
    }

    public static void main(String[] args) throws TransformerException, ParserConfigurationException, FileCorruptedException {

        saveSelectionFile("C:\\Users\\Dinbo-PC\\Desktop\\Paint\\Projekat\\operations\\oper.sel", new Selection("ime", "", new LinkedList<>(), true));
    }
}

package photoshop.project;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import photoshop.exceptions.FileCorruptedException;
import photoshop.operations.DiadicOperation;
import photoshop.operations.MonadicOperation;
import photoshop.operations.Operation;
import photoshop.selection.Selection;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.*;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import java.io.File;
import java.util.LinkedList;

public class ProjectSaver {

    public ProjectSaver() {

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

    public static void main(String[] args) throws TransformerException, ParserConfigurationException, FileCorruptedException {

        saveSelectionFile("C:\\Users\\Dinbo-PC\\Desktop\\Paint\\Projekat\\operations\\oper.sel", new Selection("ime", "", new LinkedList<>(), true));
    }
}

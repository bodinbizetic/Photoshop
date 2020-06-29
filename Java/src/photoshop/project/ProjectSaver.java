package photoshop.project;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import photoshop.exceptions.FileCorruptedException;
import photoshop.operations.DiadicOperation;
import photoshop.operations.MonadicOperation;
import photoshop.operations.Operation;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.*;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import java.io.File;

public class ProjectSaver {

    public ProjectSaver() {

    }

    private static Document createDocument() throws ParserConfigurationException {
        DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
        DocumentBuilder builder = factory.newDocumentBuilder();
        Document doc = builder.newDocument();
        return doc;
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

        saveOperationFile("C:\\Users\\Dinbo\\Desktop\\Paint\\Projekat\\operations\\oper.fun", new DiadicOperation("ime", "", () -> 5));
    }
}

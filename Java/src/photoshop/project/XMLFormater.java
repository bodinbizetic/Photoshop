package photoshop.project;

import org.w3c.dom.*;
import org.xml.sax.SAXException;
import photoshop.exceptions.FileCorruptedException;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import java.io.File;
import java.io.IOException;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;

public class XMLFormater {
    private String path;
    private String header;
    private String body;

    private HashMap<String, String> headerValues;
    private List<HashMap<String, String> > bodyValuesList;

    public XMLFormater(String path, String body) {
        this.path = path;
        this.header = header;
        this.body = body;
    }

    public void loadDocument() throws FileCorruptedException {
        Document document = openXMLDocument();
        Element root = document.getDocumentElement();

        loadHeader(root);
        loadBody(root);
    }

    private void loadBody(Element root) {
        NodeList list = root.getElementsByTagName(body);
        bodyValuesList = new LinkedList<>();
        for(int i=0; i<list.getLength(); i++) {
            HashMap<String, String> attr = loadBodyAttributes(list.item(i));
            bodyValuesList.add(attr);
        }
    }

    private HashMap<String, String> loadBodyAttributes(Node item) {
        HashMap<String, String> attr = new HashMap<>();
        NamedNodeMap map = item.getAttributes();
        for(int i=0; i<map.getLength(); i++) {
            Node element = map.item(i);
            attr.put(element.getNodeName(), element.getNodeValue());
        }
        return attr;
    }

    private void loadHeader(Element root) {
        headerValues = loadBodyAttributes(root);
    }



    private Document openXMLDocument() throws FileCorruptedException {
        try {
            DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
            DocumentBuilder builder = factory.newDocumentBuilder();
            return builder.parse(new File(System.getProperty("user.dir"), path));
        } catch (ParserConfigurationException | IOException | SAXException e) {
            e.printStackTrace();
            throw new FileCorruptedException(path);
        }
    }

    public HashMap<String, String> getHeaderValues() throws FileCorruptedException {
        if(headerValues == null)
            loadDocument();
        return headerValues;
    }

    public List<HashMap<String, String>> getBodyValuesList() throws FileCorruptedException {
        if(bodyValuesList == null)
            loadDocument();
        return bodyValuesList;
    }

    public static void main(String[] args) throws FileCorruptedException {
        String path = "C:\\Users\\Dinbo\\Desktop\\Paint\\Projekat\\operations\\Op1.fun";
        XMLFormater formater = new XMLFormater(path, "Operation");
        formater.loadDocument();
        formater.getBodyValuesList().forEach(l -> l.forEach((a, b) -> System.out.println(a + " -> " + b)));
    }
}

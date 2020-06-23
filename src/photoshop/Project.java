package photoshop;

import org.w3c.dom.Document;
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

public class Project {

    private final String path;
    private String name;
    private List<Selection> all_selections = new ArrayList<>();
    private List<Operation> all_operations = new ArrayList<>();
    private List<Layer> all_layers = new ArrayList<>();

    public Project(String path) {
        this.path = path;
    }

    public void loadProject() throws FileCorruptedException {
        try {
            DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
            DocumentBuilder builder = factory.newDocumentBuilder();
            Document document = builder.parse(new File( path ));

        } catch (ParserConfigurationException e) {
            e.printStackTrace();
        } catch (IOException | SAXException e) {
            throw new FileCorruptedException(path);
        }
    }
}

#include <algorithm>
#include <fstream>
#include "menu_layer.h"
#include "menu_main.h"
#include "utilities.h"

void Menu_Layer::functionCall(std::string x) {
    if(x == "0")
        running = false;
    else if(x == "1"){
        addLayer();
    } else if(x == "2") {
        deleteLayer();
    } else if(x == "3") {
        printLayers();
    } else if(x == "4"){
        toggleLayer();
    } else if(x == "5") {
        setOpacity();
    } else if(x == "6") {
        draw();
    } else if(x == "7") {
        swapLayers();
    } else if(x == "8") {
        showCombined();
    } else {
        throw WrongCommand();
    }
}

void Menu_Layer::addLayer() {
    LayerCollection &layers = project.getLayerCollection();
    std::string name;
    std::cout << "Layer name:\n>>> ";
    std::cin >> name; // TODO: Check if layer exists
    
    auto names = layers.getLayerNames();
    if(std::find_if(names.begin(), names.end(), [&name](std::pair<std::string, std::string> s)->bool {
        return s.first == name;
        
    }) != names.end()){
        addHeader("Name Already exists");
        return;
    }

    std::string path;
    std::cout << "Path of BMP/PAM file to be loaded:\n>>> ";
    std::cin >> path;
    std::ifstream file(path);
    if(!file){
        file.close();
        addHeader("Not valid path: created empty layer");
        path="";
    }
    
    if(layers.getLayerNames().size() == 0 && path == "") {
        int w = inputIntMsg("Width:\n>>> ");
        if(w < 1) addHeader("Not valid number");
        int h = inputIntMsg("Height:\n>>> ");
        if(h < 1) addHeader("Not valid number");
        
        layers.addLayer({w, h}, name); 
    } else
        layers.addLayer(-1, name, path);
}

void Menu_Layer::deleteLayer() {
    printLayers();
    clClean();
    LayerCollection &layers = project.getLayerCollection();
    layers.removeLayer(inputIntMsg("Insert position of layer to be removed:\n>>> "));
}

void Menu_Layer::printLayers() {
    LayerCollection &layers = project.getLayerCollection();
    std::vector< std::pair<std::string, std::string> > names = layers.getLayerNames();
    int x=0;
    for(const std::pair<std::string, std::string>& n : names)
        std::cout << x++ << ". " << n.first << "\t" << n.second << std::endl;
    setClean();
}

void Menu_Layer::toggleLayer() {
    printLayers();
    clClean();
    LayerCollection &layers = project.getLayerCollection();
    layers.toggleLayer(inputIntMsg("Insert position of layer to be toggled:\n>>> "));
    
}

void Menu_Layer::setOpacity() {
    printLayers();
    clClean();
    int pos = inputIntMsg("Insert position of layer:\n>>> ");
    int val = inputIntMsg("Insert value of opacity [0-100]:\n>>> ");
    if(val > Layer::MAX_OPACITY){
        val = Layer::MAX_OPACITY;
    }
    if(val < Layer::MIN_OPACITY)
        val = Layer::MIN_OPACITY;
        LayerCollection &layers = project.getLayerCollection();
    layers.setOpacity(pos, val);
    std::cout << "Opacity set to " << val << std::endl;
    
}

void Menu_Layer::draw() {
    int pos = inputIntMsg("Insert position of layer to be drawn:\n>>> ");
    LayerCollection &layers = project.getLayerCollection();
    std::vector<int> matrix = layers.getLayerMatrix(pos);
    std::pair<int, int> dim = layers.Dimensions();
    system("cls");
    consoleDraw(matrix, dim);
    std::string unused;
    std::cin >> unused;
}

void Menu_Layer::swapLayers() {
    int l1 = inputIntMsg("Input first layer id:\n>>> ");
    int l2 = inputIntMsg("Input second layer id:\n>>> ");
    LayerCollection &layers = project.getLayerCollection();
    layers.swapLayers(l1, l2);
}

void Menu_Layer::showCombined() {
    consoleDraw(project.getFinalResult(), project.Dimensions());
    std::string x;
    std::cin >> x;
}

/* Create empty layer and show
1
1
1
Name2
C:\Users\Dinbo\Desktop\PROJEKAT1\bmp_24.bmp
1
Name3
C:\Users\Dinbo\Desktop\PROJEKAT1\bmp_24_2.bmp
8


*/
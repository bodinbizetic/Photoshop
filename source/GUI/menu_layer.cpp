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
    else {
        throw WrongCommand();
    }
}

void Menu_Layer::addLayer() {
    std::string name;
    std::cout << "Layer name:\n>>> ";
    std::cin >> name; // TODO: Check if layer exists
    
    std::string path;
    std::cout << "Path of BMP/PAM file to be loaded:\n>>> ";
    std::cin >> path;
    std::ifstream file(path);
    if(!file){
        file.close();
        std::cout << "Not valid path: creating empty layer" << std::endl;
        path="";
    }

    project.addLayer(-1, name, path);
}

void Menu_Layer::deleteLayer() {
    printLayers();
    project.removeLayer(inputIntMsg("Insert position of layer to be removed:\n>>> "));
}

void Menu_Layer::printLayers() {
    std::vector< std::pair<std::string, std::string> > names = project.getLayerNames();
    int x=0;
    for(const std::pair<std::string, std::string>& n : names)
        std::cout << x++ << ". " << n.first << "\t" << n.second << std::endl;
    setClean();
}

void Menu_Layer::toggleLayer() {
    printLayers();
    project.toggleLayer(inputIntMsg("Insert position of layer to be toggled:\n>>> "));
    
}

void Menu_Layer::setOpacity() {
    int pos = inputIntMsg("Insert position of layer:\n>>> ");
    int val = inputIntMsg("Insert value of opacity [0-100]:\n>>> ");
    if(val > Layer::MAX_OPACITY){
        val = Layer::MAX_OPACITY;
    }
    if(val < Layer::MIN_OPACITY)
        val = Layer::MIN_OPACITY;
    project.setOpacity(pos, val);
    std::cout << "Opacity set to " << val << std::endl;
    
}

void Menu_Layer::draw() {
    int pos = inputIntMsg("Insert position of layer to be drawn:\n>>> ");
    std::vector<int> matrix = project.getLayerMatrix(pos);
    std::pair<int, int> dim = project.Dimensions();
    system("cls");
    consoleDraw(matrix, dim);
    std::string unused;
    std::cin >> unused;
}

void Menu_Layer::swapLayers() {
    int l1 = inputIntMsg("Input first layer id:\n>>> ");
    int l2 = inputIntMsg("Input second layer id:\n>>> ");
    project.swapLayers(l1, l2);
}

/* Create empty layer and show
1
1
1
Name
Location
1
Name2
Location2
1
Name3
Location3
3


1
1
1
Name
C:\Users\Dinbo\Desktop\PROJEKAT1\bmp_24.bmp
6
0
*/
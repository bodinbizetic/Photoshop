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
        // TODO: Selection menu
    } else if(x == "5") {
        // TODO: operation menu
    } else if(x == "6") {
        // TODO: Selection menu
    }else {
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
    }

    project.addLayer(-1, name, path);
}

void Menu_Layer::deleteLayer() {
    printLayers();

    std::string command;
    std::cout << "Insert position of layer to be removed:\n>>> ";
    std::cin >> command;
    if(!isInteger(command))
        throw WrongCommand();
    project.removeLayer(atoi(command.c_str()));
}

void Menu_Layer::printLayers() {
    std::vector<std::string> names = project.getLayerNames();
    int x=0;
    for(const std::string& n : names)
        std::cout << x++ << ". " << n << std::endl;
    setClean();
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
3

*/
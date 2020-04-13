#include "menu_layer.h"

void Menu_Layer::functionCall(std::string x) {
    if(x == "0")
        running = false;
    else if(x == "1"){
        // TODO: Show layers
    } else if(x == "2") {
        // TODO: operation menu
    } else if(x == "3") {
        // TODO: Selection menu
    } else if(x == "4"){
        printLayers();
    } else if(x == "5") {
        // TODO: operation menu
    } else if(x == "6") {
        // TODO: Selection menu
    }else {
        throw WrongCommand();
    }
}

void Menu_Layer::printLayers() const{
    std::vector<std::string> names = project.getLayerNames();
    int x=0;
    for(const std::string& n : names)
        std::cout << x << ". " << n << std::endl;
}
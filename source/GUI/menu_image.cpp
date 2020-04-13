#include <vector>

#include "menu_image.h"

void Menu_Image::functionCall(std::string x) {
    if(x == "0")
        running = false;
    else if(x == "1"){
        // TODO: layer menu
    } else if(x == "2") {
        // TODO: operation menu
    } else if(x == "3") {
        // TODO: Selection menu
    } else {
        throw WrongCommand();
    }
}
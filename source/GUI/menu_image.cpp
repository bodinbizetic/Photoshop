#include <vector>

#include "menu_selection.h"
#include "menu_image.h"
#include "menu_layer.h"

void Menu_Image::functionCall(std::string x) {
    if(x == "0")
        running = false;
    else if(x == "1"){
        Menu_Layer m(project);
        m.start();
    } else if(x == "2") {
        // TODO: operation menu
    } else if(x == "3") {
        Menu_Selection m(project);
        m.start();
    } else {
        throw WrongCommand();
    }
}
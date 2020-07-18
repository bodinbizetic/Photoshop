#include <vector>

#include "menu_selection.h"
#include "menu_image.h"
#include "menu_layer.h"
#include "menu_operations.h"
#include "menu_file.h"

void Menu_Image::functionCall(std::string x) {
    if (x == "0") {
        promptSave();
        running = false;
    }
    else if(x == "1"){
        Menu_Layer m(project);
        m.start();
    } else if(x == "2") {
        Menu_Operation m(project);
        m.start();
    } else if(x == "3") {
        Menu_Selection m(project);
        m.start();
    } else if (x == "4") {
        Menu_File m(project);
        m.start();
    }
    else {
        throw WrongCommand();
    }
}

void Menu_Image::promptSave() {
    std::cout << "Do you wish to save?\n0. Yes\n1. No\n>>> ";
    std::string line;
    std::getline(std::cin, line);
    if (line == "0") {
        project.saveAll();
    }
    else if (line == "1")
        return;
    else throw WrongCommand();
}

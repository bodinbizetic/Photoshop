#include "menu_operations.h"

void Menu_Operation::functionCall(std::string x) {
    if(x == "0")
        running = false;
    else if(x == "1"){
        showAllOperations();
    } else if(x == "2") {
        // Use
    } else if(x == "3") {
        // Create
    } else if(x == "4"){
        // Gray
    } else if(x == "5") {
        // BlackW
    } else if(x == "6") {
        // Invert
    } else {
        throw WrongCommand();
    }
}

void Menu_Operation::showAllOperations() {
    int x = 0;
    showDiadic(x);
    showMonadic(x);
    setClean();
}

void Menu_Operation::showDiadic(int& x) const {
    std::vector<std::string> names = project.getDiadicNames();
    for(std::string name : names) {
        std::cout << x++ << " " << name << std::endl;
    }
}

void Menu_Operation::showMonadic(int& x) const {
    std::vector<std::string> names = project.getOperationNames();
    for(std::string name : names) {
        std::cout << x++ << " " << name << std::endl;
    }
}
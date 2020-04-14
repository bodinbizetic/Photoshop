#include "menu_selection.h"

void Menu_Selection::functionCall(std::string x ){
    if(x == "0")
        running = false;
    else if(x == "1"){
        // Add
    } else if(x == "2") {
        // Remove
    } else if(x == "3") {
        showAllSelections();
    } else if(x == "4"){
        // Toggle
    } else if(x == "5") {
        // Add to select
    } else {
        throw WrongCommand();
    }
}

void Menu_Selection::showAllSelections() {
    
}
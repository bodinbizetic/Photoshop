#include <algorithm>

#include "menu_selection.h"
#include "utilities.h"
#include "rectangle.h"

void Menu_Selection::functionCall(std::string x ){
    if(x == "0")
        running = false;
    else if(x == "1"){
        addSelection();
    } else if(x == "2") {
        removeSelection();
    } else if(x == "3") {
        showAllSelections();
    } else if(x == "4"){
        toggleSelection();
    } else if(x == "5") {
        addRectangle();
    } else {
        throw WrongCommand();
    }
}

void Menu_Selection::addSelection() {
    std::string name;
    std::cout << "Insert a name for new selection:\n>>> ";
    std::cin >> name;
    std::vector<std::pair<std::string, std::string>> all_names = project.getSelectionNames();
    
    if(std::find_if(all_names.begin(), all_names.end(), [name](std::pair<std::string, std::string> s) -> bool {
        return name == s.first;
    }) != all_names.end()) {
        std::cout << "Name already exists, Creation failed" << std::endl;
        setClean();
        return;
    }
    project.addSelection(name);
}

void Menu_Selection::removeSelection() {
    int position = inputIntMsg("Insert position of seleciton to be deleted:\n>>> ");
    project.removeSelection(position);
}

void Menu_Selection::showAllSelections() {
    auto all = project.getSelectionNames();
    for(std::pair<std::string, std::string> n : all)
        std::cout << n.first << "\t" << n.second << std::endl;
    setClean();
}

void Menu_Selection::toggleSelection() {
    int position = inputIntMsg("Insert position of seleciton to be toggled:\n>>> ");
    project.toggleSelection(position);
}

void Menu_Selection::addRectangle() {
    int position =  inputIntMsg("Insert position of selection to selecti rectangle:\n>>> ");
    int x =         inputIntMsg("Insert X coordinate:\n>>> ");
    int y =         inputIntMsg("Insert Y coordinate:\n>>> ");
    int w =         inputIntMsg("Insert width:\n>>> ");
    int h =         inputIntMsg("Insert height:\n>>> ");
    RectangleShape reck(x, y, w, h);
    project.select(reck, position);
}
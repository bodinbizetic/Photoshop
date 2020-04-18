#include <iostream>

#include "menu.h"

#define MENU_DIVIDER "+---------------------------------+"

void Menu::start() {
    loopMenu();
}

void Menu::loopMenu() {
    while(running) {
        showMenu();
        std::string command;
        std::cout << ">>> ";
        std::cin >> command;
        try{
            functionCall(command);
        } catch(std::exception& e) {
            addHeader(e.what());
            clean = true;
        }
    }
}

void Menu::showMenu() {
    if(clean) {
        system("cls");
        printHeader();
        int id=0; 
        for(std::string c : commands)
            std::cout << id++ << ". " << c << std::endl;
    } else
       clean = true;
    
}

void Menu::printHeader() {
    for(std::string s : header)
        std::cout << s << std::endl;
    
    std::cout << MENU_DIVIDER << std::endl;
    header.clear();
}
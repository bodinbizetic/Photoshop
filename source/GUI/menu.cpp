#include <iostream>

#include "menu.h"

void Menu::start() {
    loopMenu();
}

void Menu::loopMenu() {
    while(running) {
        showMenu();
        std::string command;
        std::cout << ">>> ";
        std::cin >> command;
        functionCall(command);
    }
}

void Menu::showMenu() {
    if(clean) {
        system("cls");
        int id=0; 
        for(std::string c : commands)
            std::cout << id++ << ". " << c << std::endl;
    } else
       clean = true;
    
}
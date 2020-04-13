#include <iostream>

#include "menu.h"

void Menu::start() {
    loopMenu();
}

void Menu::loopMenu() {
    while(running) {
        showMenu();
        std::string command;
        
        std::cin >> command;
        functionCall(command);
    }
}

void Menu::showMenu() {
    system("cls");
    int id=0; 
    for(std::string c : commands)
        std::cout << id++ << ". " << c << std::endl;
}
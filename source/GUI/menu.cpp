#include <iostream>

#include "menu.h"

void Menu::start() {
    loopMenu();
}

void Menu::loopMenu() {
    while(1) {
        std::string command;
        std::cin >> command;
        functionCall(command.c_str());
    }
}
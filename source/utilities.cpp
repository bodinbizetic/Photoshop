#include <string>
#include <stdlib.h>
#include <iostream>

#include "menu.h"

bool isInteger(std::string s) {
    for(auto c : s)
        if(!isdigit(c))
            return false;
    return true;
}

int inputIntMsg(std::string x) {
    std::string command;
    std::cout << "Insert position of layer to be toggled:\n>>> ";
    std::cin >> command;
    if(!isInteger(command))
        throw WrongCommand();
    
    return atoi(command.c_str());
}

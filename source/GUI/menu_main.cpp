#include <vector>
#include <iostream>
#include <stdlib.h>
#include "menu_main.h"

void Menu_Main::functionCall(std::string x) {
    if(x == "0")
        running = false;
    else if(x == "1"){
        // TODO: image creation menu
    } else if(x == "2") {
        // TODO: image open
    } else {
        throw WrongCommand();
    }
}


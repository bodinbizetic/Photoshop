#include "menu_operations_mode.h"
#include "utilities.h"

void Menu_Operation_Mode::functionCall(std::string x) {
    if(x == "0")
        running = false;
    else if(x == "1"){
        showCurrentOperationMode();
    } else if(x == "2") {
        toggleOperationMode();
    } else {
        throw WrongCommand();
    }
}

void Menu_Operation_Mode::showCurrentOperationMode() {
    auto modes = project.getOperationMode();
    int x = 0;
    for(auto m : modes)
        std::cout << x++ << ". " << m.first << "\t" << m.second << std::endl;
    setClean();
}

void Menu_Operation_Mode::toggleOperationMode() {
    int op = inputIntMsg("Input id of atribute to be changed:\n>>> ");
    if(op < 0 || op >= project.getOperationMode().size()) {
        addHeader("Index out of bounds");
        return;
    }
    project.toggleModeColor(project.getOperationMode()[op].first);
}

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
    OperationCollection &operations = project.getOperationCollection();
    auto modes = operations.getOperationMode();
    int x = 0;
    for(auto m : modes)
        std::cout << x++ << ". " << m.first << "\t" << m.second << std::endl;
    setClean();
}

void Menu_Operation_Mode::toggleOperationMode() {
    OperationCollection &operations = project.getOperationCollection();
    int op = inputIntMsg("Input id of atribute to be changed:\n>>> ");
    if(op < 0 || op >= operations.getOperationMode().size()) {
        addHeader("Index out of bounds");
        return;
    }
    operations.toggleModeColor(operations.getOperationMode()[op].first);
}

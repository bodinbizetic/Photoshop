#include "menu_operations_mode.h"
#include "menu_operations.h"
#include "utilities.h"

void Menu_Operation::functionCall(std::string x) {
    if(x == "0")
        running = false;
    else if(x == "1"){
        showAllOperations();
    } else if(x == "2") {
        useOperation();
    } else if(x == "3") {
        createOperation();
    } else if(x == "4"){
        // project.toGray();
    } else if(x == "5") {
        // project.toBlackWhite();
    } else if(x == "6") {
        // project.invert();
    } else if(x == "7") {
        // project.blur();
    } else if(x == "8") {
        Menu_Operation_Mode m(project);
        m.start();
    } else {
        throw WrongCommand();
    }
}

void Menu_Operation::showAllOperations() {
    int x = 0;
    OperationCollection& operations = project.getOperationCollection();
    std::vector<std::string> names = operations.getOperationNames();
    for (std::string name : names) {
        std::cout << x++ << " " << name << std::endl;
    }
    setClean();
}

void Menu_Operation::useOperation() {
    OperationCollection &operations = project.getOperationCollection();
    showAllOperations();
    setClean();
    
    int oper_num = operations.getOperationNames().size();
    std::pair<int, int> operation_id_arg = insertOperation();
    if(operation_id_arg.first < 0 || operation_id_arg.first >= oper_num) {
        addHeader("Wrong ID");
        return;
    }

    applyOperation(operation_id_arg);
}

void Menu_Operation::applyOperation(std::pair<int, int> op_id_arg) {
    project.useOperation(op_id_arg);
}

void Menu_Operation::createOperation() {
    std::vector<std::pair<int,int>> op_scheme;
    showAllOperations();
    setClean();
    std::string name;
    std::cout << "Insert name:\n>>> ";
    std::getline(std::cin, name);
    std::cout << "End with -1" << std::endl;
    while(1) {
        std::pair<int, int> op = insertOperation();
        if(op.first == -1)
            break;
        op_scheme.push_back(op);
    }

    OperationCollection &operations = project.getOperationCollection();
    operations.createOperation(op_scheme, name);
}

std::pair<int, int> Menu_Operation::insertOperation() {
    std::cout << "Insert operation name and argument:\n>>> ";
    std::string line;
    std::getline(std::cin, line);
    std::pair<int, int> op_id_arg{ 0,0 };
    if(sscanf_s(line.c_str(), "%d %d", &op_id_arg.first, &op_id_arg.second) == 0)
        throw WrongCommand();
    return op_id_arg;
}
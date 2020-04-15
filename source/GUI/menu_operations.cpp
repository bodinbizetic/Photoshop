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
        project.toGray();
    } else if(x == "5") {
        project.toBlackWhite();
    } else if(x == "6") {
        project.invert();
    } else if(x == "7") {
        project.blur();
    } else if(x == "8") {
        Menu_Operation_Mode m(project);
        m.start();
    } else {
        throw WrongCommand();
    }
}

void Menu_Operation::showAllOperations() {
    int x = 0;
    showDiadic(x);
    showMonadic(x);
    setClean();
}

void Menu_Operation::showDiadic(int& x) const {
    std::vector<std::string> names = project.getDiadicNames();
    for(std::string name : names) {
        std::cout << x++ << " " << name << std::endl;
    }
}

void Menu_Operation::showMonadic(int& x) const {
    std::vector<std::string> names = project.getOperationNames();
    for(std::string name : names) {
        std::cout << x++ << " " << name << std::endl;
    }
}

void Menu_Operation::useOperation() {
    int diadic_num = project.getDiadicNames().size();
    int oper_num   = project.getOperationNames().size();
    int operation_id = inputIntMsg("Insert id of operation you want to use\n>>> ");
    if(operation_id < 0 || operation_id >= diadic_num + oper_num) {
        addHeader("Wrong ID");
        return;
    }

    if(operation_id < diadic_num)
        useDiadic(project.getDiadicNames()[operation_id]);
    else
        useMonadicOperation(operation_id - diadic_num);
}

void Menu_Operation::useDiadic(std::string op_id) {
    int arg = inputIntMsg("Insert constant for other operand:\n>>> ");
    project.useDiadic(op_id, arg);
}

void Menu_Operation::useMonadicOperation(int op_id) {
    project.useOperation(op_id);
}

void Menu_Operation::createOperation() {
    std::vector<std::pair<int,int>> op_scheme;
    showAllOperations();
    std::string name;
    std::cout << "Insert name:\n>>> ";
    std::cin >> name;
    std::cout << "End with -1" << std::endl;
    while(1) {
        std::pair<int, int> op = insertOperation();
        if(op.first == -1)
            break;
        op_scheme.push_back(op);
    }

    project.createOperation(op_scheme, name);
}

std::pair<int, int> Menu_Operation::insertOperation() {
    int diadic_num = project.getDiadicNames().size();
    int oper_num   = project.getOperationNames().size();
    int operation_id = inputIntMsg("OPERATION:\n>>> ");
    if(operation_id < 0 || operation_id >= diadic_num + oper_num) {
        return {-1, -1};
    }

    if(operation_id < diadic_num) {
        int arg = inputIntMsg("ARGUMENT:\n>>> ");
        return {operation_id, arg};
    }
    else
        return {operation_id, -1};
        
}
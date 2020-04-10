#include "operation.h"

std::map<std::string, Operation*> Operation::all_operations;

Operation::Operation(std::string name_) {
    setName(name_);
}

Operation::~Operation() {
    remove(name);
}

void Operation::setName(std::string name_) {
    if(name_ == "")
        return;

    if(all_operations.find(name_) != all_operations.end())
        throw OperationNameAlreadyExists();
    
    remove(name);
    name = name_;

    all_operations[name] = this;
}

void Operation::remove(std::string name_) {
    if(all_operations.find(name_) != all_operations.end())
        all_operations.erase(all_operations.find(name_));
}
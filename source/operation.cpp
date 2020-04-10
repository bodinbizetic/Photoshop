#include "operation.h"

Operation::Operation(std::string name_) {
    setName(name_);
}

Operation::~Operation() {
}

void Operation::setName(std::string name_) {
    if(name_ == "")
        return;
    name = name_;
}
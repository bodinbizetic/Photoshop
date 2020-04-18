#include "operation.h"

const std::string Operation::DEFAULT_OP_NAME = "";

Operation::Operation(std::string name_, int RGBA_mask_) : RGBA_mask(RGBA_mask_) {
    setName(name_);
}

Operation::~Operation() {
}

void Operation::setName(std::string name_) {
    if(name_ == DEFAULT_OP_NAME)
        return;
    name = name_;
}
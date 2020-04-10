#include "simple_operation.h"

SimpleOperation::SimpleOperation(std::function<int(int)> operation_function_, std::string name_ )
:   operation_function(operation_function_),
    Operation(name_) {

}

int SimpleOperation::operator() (int x) {
    return operation_function(x);
}

Operation* SimpleOperation::copy() {
    return new SimpleOperation(*this);
}
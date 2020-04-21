
#include <algorithm>

#include "complex_operation.h"

ComplexOperation::ComplexOperation(std::vector<Operation*> operations, std::string name_) : Operation(name_) {
    for (Operation* op : operations)
        add(*op);
}


void ComplexOperation::add(const Operation& operation) {
    std::vector<Operation*> temp = operation.copyVector();
    operation_functions.insert(operation_functions.end(), temp.begin(), temp.end());
}

ComplexOperation::ComplexOperation(const ComplexOperation& cop2) {
    copy(cop2);
}

ComplexOperation ComplexOperation::operator= (const ComplexOperation& cop2) {
    if(&cop2 == this)
        return *this;
    copy(cop2);
    return *this;
}

OperationalLayer& ComplexOperation::operator() (OperationalLayer& op, const std::vector<std::pair<int, int>>& toChange) const {
    std::for_each(operation_functions.begin(), operation_functions.end(), [&] (Operation* oper) {
        (*oper)(op, toChange);
    });
    return op;
}

std::vector<Operation*> ComplexOperation::copyVector() const {
    std::vector<Operation*> deep_copy;
    for (Operation* op : operation_functions) {
        std::vector<Operation*> temp = op->copyVector();
        deep_copy.insert(deep_copy.end(), temp.begin(), temp.end());
    }
        
    return deep_copy;    
}

void ComplexOperation::copy(const ComplexOperation& cop) {
    setName(cop.Name());
    operation_functions = cop.copyVector();
}


void ComplexOperation::clear() {
    for(Operation*& o : operation_functions) {
        delete o;
        o = nullptr;
    }
}
#include <algorithm>

#include "complex_operation.h"

ComplexOperation::ComplexOperation(std::vector<Operation*> operations, std::string name_) : Operation(name_) {
    operation_functions = copy(operations);
}


void ComplexOperation::add(const Operation& op) {
    operation_functions.push_back(op.copy());
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

Operation* ComplexOperation::copy() const {
    return new ComplexOperation(*this);
}

std::vector<Operation*> ComplexOperation::copy(std::vector<Operation*> op) const {
    std::vector<Operation*> new_vector(op);
    for(Operation*&o : new_vector) {
        o = o->copy();
    }
    return new_vector;
}

void ComplexOperation::copy(const ComplexOperation& cop) {
    setName(cop.Name());
    operation_functions = cop.copy(cop.operation_functions);
}


void ComplexOperation::clear() {
    for(Operation*& o : operation_functions) {
        delete o;
        o = nullptr;
    }
}
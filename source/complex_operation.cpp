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

int ComplexOperation::operator() (int x) {
    int result = x;
    std::for_each(operation_functions.begin(), operation_functions.end(), [&result] (Operation* op) {
        result = (*op)(result);
    });
    return result;
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
    operation_functions = cop.copy(cop.operation_functions);
}


void ComplexOperation::clear() {
    for(Operation*& o : operation_functions) {
        delete o;
        o = nullptr;
    }
}
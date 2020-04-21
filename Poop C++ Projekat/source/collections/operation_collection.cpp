#include <math.h>
#include <algorithm>
#include "operation_collection.h"
#include "complex_operation.h"
#include "simple_operation.h"
#include "diadic_operation.h"
#include "gray_operation.h"

OperationCollection::~OperationCollection() {
    for(Operation*& o : all_operations) {
        delete o;
        o = nullptr;
    }
    all_operations.clear();
}

std::vector<std::string> OperationCollection::getOperationNames() const {
    std::vector<std::string> names;
    for(auto p : all_operations)
        names.push_back(p->Name());
    
    return names;
}

std::vector<std::pair<std::string, std::string>> OperationCollection::getOperationMode() const {
    std::vector<std::pair<std::string, std::string>> ret;
    for(auto i : operation_mode)
        ret.push_back({i.first, (i.second ? "True" : "False")});
    return ret;
}

void OperationCollection::addOperation(const Operation& op) {
    all_operations.push_back(op.copy());
}

void OperationCollection::removeOperation(int position) {
    delete all_operations[position];
    all_operations.erase(all_operations.begin() + position);
}

Operation* OperationCollection::getOperation(int pos) {
    if(pos < 0 || pos >= all_operations.size())
        throw CollectionIndexOutOfBounds();
    
    return all_operations[pos];
}

void OperationCollection::createOperation(std::vector<std::pair<int, int>> op_arg, std::string name_) {
    ComplexOperation cop(name_);
    for(std::pair<int, int> op : op_arg) {
        Operation* stored_operation = all_operations[op.first];
        stored_operation->setParam(op.second);
        cop.add(*stored_operation);
    }
    addOperation(cop);
}

void OperationCollection::initOperations() {
    DiadicOperation op1(std::plus<int>(), 0, "add");
    DiadicOperation op2(std::minus<int>(), 0, "sub");
    DiadicOperation op3([](int y, int x) -> int { if(x ==0) return 255; return y/x; }, 1, "div");
    DiadicOperation op4(std::multiplies<int>(), 1, "mul");
    DiadicOperation op5([](int x, int y) -> int { if(x ==0) return 255; return y/x; }, 1, "rdiv");
    DiadicOperation op6([](int x, int y) -> int { return y-x; }, 0, "rsub");
    DiadicOperation op7([](int x, int y) -> int  { return pow(x, y); }, 0, "pow");
    DiadicOperation op8([](int x, int y) -> int  { return std::max(x, y); }, 0, "max");
    DiadicOperation op9([](int x, int y) -> int  { return std::min(x, y); }, 255, "min");
    SimpleOperation sop1([](int x) -> int { return log(x); }, "Log");
    SimpleOperation sop2([](int x) -> int { return abs(x); }, "Abs");
    GrayTransformation gop1("Gray");
    all_operations.push_back(sop1.copy());
    all_operations.push_back(sop2.copy());
    all_operations.push_back(gop1.copy());
    all_operations.push_back(op1.copy());
    all_operations.push_back(op2.copy());
    all_operations.push_back(op3.copy());
    all_operations.push_back(op4.copy());
    all_operations.push_back(op5.copy());
    all_operations.push_back(op6.copy());
    all_operations.push_back(op7.copy());
    all_operations.push_back(op8.copy());
    all_operations.push_back(op9.copy());
    
}

void OperationCollection::toggleModeColor(std::string name) {
    if(operation_mode.find(name) != operation_mode.end())
        operation_mode[name] = !operation_mode[name];
}

int OperationCollection::getModeBinary() {
    int ret=0;
    if(operation_mode["Red"])
        ret += 0b1000;
    if(operation_mode["Blue"])
        ret += 0b0100;
    if(operation_mode["Green"])
        ret += 0b0010;
    if(operation_mode["Alfa"])
        ret += 0b0001;
    return ret;
}
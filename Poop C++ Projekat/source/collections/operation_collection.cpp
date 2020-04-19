#include <math.h>
#include <algorithm>
#include "operation_collection.h"
#include "complex_operation.h"
#include "simple_operation.h"
#include "gray_operation.h"

OperationCollection::~OperationCollection() {
    for(Operation*& o : all_operations) {
        delete o;
        o = nullptr;
    }
    all_operations.clear();
}

std::vector<std::string> OperationCollection::getDiadicNames() const {
    std::vector<std::string> names;
    for(auto p : diadic_functions)
        names.push_back(p.first);
    
    return names;
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

std::function<int(int,int)> OperationCollection::getDiadic(int pos) {
    if(pos < 0 || pos >= diadic_functions.size())
        throw CollectionIndexOutOfBounds();
    
    return diadic_functions[getDiadicNames()[pos]];
}

Operation* OperationCollection::getOperation(int pos) {
    if(pos < 0 || pos >= all_operations.size())
        throw CollectionIndexOutOfBounds();
    
    return all_operations[pos];
}

void OperationCollection::createOperation(std::vector<std::pair<int, int>> op_arg, std::string name_) {
    std::vector<std::string> diadic = getDiadicNames();
    ComplexOperation cop(name_);
    for(std::pair<int, int> op : op_arg) {
        if(op.first < diadic.size()){
            auto fun = std::bind(diadic_functions[diadic[op.first]], std::placeholders::_1, op.second);
            cop.add(SimpleOperation(fun, diadic[op.first]));
        } else {
            cop.add(*all_operations[op.first - diadic.size()]);
        }
    }
    addOperation(cop);
}

void OperationCollection::initOperations() {
    diadic_functions["add"] = std::plus<int>();
    diadic_functions["sub"] = std::minus<int>();
    diadic_functions["div"] = [](int y, int x) -> int { if(x ==0) return 255; return y/x; };
    diadic_functions["mul"] = std::multiplies<int>();
    diadic_functions["rdiv"] = [](int x, int y) -> int { if(x ==0) return 255; return y/x; };
    diadic_functions["rsub"] = [](int x, int y) -> int { return y-x; };
    diadic_functions["pow"] = [](int x, int y) -> int  { return pow(x, y); };
    diadic_functions["max"] = [](int x, int y) -> int  { return std::max(x, y); };
    diadic_functions["min"] = [](int x, int y) -> int  { return std::min(x, y); };
    SimpleOperation sop1([](int x) -> int { return log(x); }, "Log");
    SimpleOperation sop2([](int x) -> int { return abs(x); }, "Abs");
    GrayTransformation gop1("Gray");
    all_operations.push_back(sop1.copy());
    all_operations.push_back(sop2.copy());
    all_operations.push_back(gop1.copy());
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
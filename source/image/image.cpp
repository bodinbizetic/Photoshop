#include <set>
#include <math.h>
#include <algorithm>

#include "formater_bmp.h"
#include "image.h"
#include "simple_operation.h"

Image::Image() {
    initOperations();
}

Image::~Image() {
    for(Operation*& o : all_operations) {
        delete o;
        o = nullptr;
    }
    all_operations.clear();
}

std::vector<std::string> Image::getDiadicNames() const {
    std::vector<std::string> names;
    for(auto p : diadic_functions)
        names.push_back(p.first);
    
    return names;
}

std::vector<std::string> Image::getOperationNames() const {
    std::vector<std::string> names;
    for(auto p : all_operations)
        names.push_back(p->Name());
    
    return names;
}

std::vector<std::pair<std::string, std::string>> Image::getOperationMode() const {
    std::vector<std::pair<std::string, std::string>> ret;
    for(auto i : operation_mode)
        ret.push_back({i.first, (i.second ? "True" : "False")});
    return ret;
}

Image& Image::addOperation(const Operation& op) {
    all_operations.push_back(op.copy());
    return *this;
}

Image& Image::removeOperation(int position) {
    delete all_operations[position];
    all_operations.erase(all_operations.begin() + position);
    return *this;
}

std::vector<int> Image::getFinalResult() {
    auto vp = all_layers.combineLayers().Matrix();
    std::vector<int> vi;
    for(Pixel& p : vp)
        vi.push_back((int)p);
    return vi;
}

void Image::initOperations() {
    diadic_functions["add"] = std::plus<int>();
    diadic_functions["sub"] = std::minus<int>();
    diadic_functions["div"] = [](int y, int x) -> int { if(x ==0) throw DivisionByZero(); return y/x; };
    diadic_functions["mul"] = std::multiplies<int>();
    diadic_functions["rdiv"] = [](int x, int y) -> int { if(x ==0) throw DivisionByZero(); return y/x; };
    diadic_functions["rsub"] = [](int x, int y) -> int { return y-x; };
    diadic_functions["pow"] = [](int x, int y) -> int  { return pow(x, y); };
    diadic_functions["max"] = [](int x, int y) -> int  { return std::max(x, y); };
    diadic_functions["min"] = [](int x, int y) -> int  { return std::min(x, y); };
    SimpleOperation sop1([](int x) -> int { return log(x); }, "Log");
    SimpleOperation sop2([](int x) -> int { return abs(x); }, "Abs");
    all_operations.push_back(sop1.copy());
    all_operations.push_back(sop2.copy());

}

void Image::toggleModeColor(std::string name) {
    if(operation_mode.find(name) != operation_mode.end())
        operation_mode[name] = !operation_mode[name];
}


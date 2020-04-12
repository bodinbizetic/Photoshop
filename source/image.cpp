#include "image.h"
#include <math.h>
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

Image& Image::addLayer(int position, std::string name_) {
    Layer newLayer = Layer(dimensions, name_);
    
    if(position >= all_layers.size() || position < 0)
        all_layers.push_back(newLayer);
    all_layers.insert(all_layers.begin() + position, newLayer);

    return *this;
}

Image& Image::removeLayer(int position) {
    if(position >= all_layers.size() || position < 0)
       throw ImageIndexOutOfBounds();
    all_layers.erase(all_layers.begin() + position);

    return *this;
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

void Image::initOperations() {
    diadic_functions["add"] = std::plus<int>();
    diadic_functions["sub"] = std::minus<int>();
    diadic_functions["div"] = std::divides<int>();
    diadic_functions["mul"] = std::multiplies<int>();
    diadic_functions["rdiv"] = [](int x, int y) -> int { return y/x; };
    diadic_functions["rsub"] = [](int x, int y) -> int { return y-x; };
    diadic_functions["pow"] = [](int x, int y) -> int  { return pow(x, y); };
    diadic_functions["max"] = [](int x, int y) -> int  { return std::max(x, y); };
    diadic_functions["min"] = [](int x, int y) -> int  { return std::min(x, y); };
    SimpleOperation sop1([](int x) -> int { return log(x); }, "Log");
    SimpleOperation sop2([](int x) -> int { return abs(x); }, "Abs");
    all_operations.push_back(sop1.copy());
    all_operations.push_back(sop2.copy());

}
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

Image& Image::addLayer(int position, std::string name_, std::string path_) {
    Layer newLayer = createLayer(name_, path_);

    
    if(position >= all_layers.size() || position < 0)
        all_layers.push_back(newLayer);
    else 
        all_layers.insert(all_layers.begin() + position, newLayer);

    fitAll();
    return *this;
}

Image& Image::addLayer(std::pair<int, int> dimensions_, std::string name_) {
    Layer newLayer(dimensions_, name_);
    all_layers.push_back(newLayer);
    updateDim(dimensions_);
    fitAll();

    return *this;
}

Image& Image::removeLayer(int position) {
    if(position >= all_layers.size() || position < 0)
       throw ImageIndexOutOfBounds();
    all_layers.erase(all_layers.begin() + position);
    if(all_layers.size() == 0)
        dimensions = {0,0};
    return *this;
}

std::vector<std::pair<std::string, std::string>> Image::getLayerNames() const {
    std::vector<std::pair<std::string, std::string>> names;
    for(const Layer& l: all_layers) {
        names.push_back({l.getName(), (l.Active() ? "True" : "False")});
    }
    return names;
}

Image& Image::toggleLayer(int position) {
    if(position >= all_layers.size() || position < 0)
       throw ImageIndexOutOfBounds();
    
    all_layers[position].setActive(!all_layers[position].Active());

    return *this;
}

Image& Image::setOpacity(int position, int val) {
    if(position >= all_layers.size() || position < 0)
       throw ImageIndexOutOfBounds();
    
    all_layers[position].setOpacity(val);
    
    return *this;
}

std::vector<int> Image::getLayerMatrix(int position) const {
    if(position >= all_layers.size() || position < 0)
       throw ImageIndexOutOfBounds();
    
    auto matrix = all_layers[position].Matrix();
    std::vector<int> ret;
    for(auto m : matrix)
        ret.push_back((int)m);
    
    return ret;
}

void Image::swapLayers(int position1, int position2) {
    if(position1 >= all_layers.size() || position1 < 0)
       throw ImageIndexOutOfBounds();
    if(position2 >= all_layers.size() || position2 < 0)
       throw ImageIndexOutOfBounds();
    
    std::swap(all_layers[position1], all_layers[position2]);
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
    auto vp = combineLayers().Matrix();
    std::vector<int> vi;
    for(Pixel& p : vp)
        vi.push_back((int)p);
    return vi;
}

Layer Image::combineLayers() const {
    Layer l1(dimensions);
    for(const Layer& l : all_layers)
        if(l.Active())
            l1 = l1 + l;

    return l1;
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

Layer Image::createLayer(std::string name_, std::string path_) {
    if(path_ == "")
        return Layer(dimensions, name_);
    else {
        Formater &f = * new Formater_BMP(path_);
        std::vector<int> vi = f.load();
        std::vector<Pixel> vp;
        for(int i : vi) { // TODO: Add constructor from vi to vp
            vp.push_back((Pixel) i);
        }
        std::pair<int, int> dim = f.Dimensions();
        Layer newLayer(dim, vp, name_);
        // TODO: call fit layers
        updateDim(dim);
        delete &f;
        return newLayer;
    }
}

void Image::fitAll() {
    for(Layer& l : all_layers)
        l.fitLayer(dimensions);
}

void Image::updateDim(std::pair<int, int> newDim) {
    dimensions.first = std::max(dimensions.first, newDim.first);
    dimensions.second = std::max(dimensions.second, newDim.second);
}

void Image::toggleModeColor(std::string name) {
    if(operation_mode.find(name) != operation_mode.end())
        operation_mode[name] = !operation_mode[name];
}


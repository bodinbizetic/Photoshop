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

    return *this;
}

Image& Image::removeLayer(int position) {
    if(position >= all_layers.size() || position < 0)
       throw ImageIndexOutOfBounds();
    all_layers.erase(all_layers.begin() + position);

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

Image& Image::useDiadic(std::string name, int arg) {
    std::function<int(int, int)> fun = diadic_functions[name];
    std::function<int(int)> fun_operation = std::bind(fun, std::placeholders::_1, arg);
    SimpleOperation op(fun_operation);
    applyOperation(op);
    return *this;
}

Image& Image::applyOperation(const Operation& op) {
    int count = std::count_if(all_selections.begin(), all_selections.end(), [](const Selection& l){
        return l.isActive();
    });
    if(count)
        applyOperationSelection(op);
    else
        applyOperationImage(op);
    
    return *this;
}

Image& Image::applyOperationSelection(const Operation& op) {
    std::set<std::pair<int, int>> all_coordinates;
    for(const Selection& s : all_selections)
        if(s.isActive()){
            auto vii = s.getSelectedCoordinates(dimensions);
            all_coordinates.insert(vii.begin(), vii.end());
        }
    applyOperationCoordinates(op, {all_coordinates.begin(), all_coordinates.end()});
    return *this;
}

Image& Image::applyOperationImage(const Operation& op) {

}

Image& Image::applyOperationCoordinates(const Operation& op, std::vector<std::pair<int, int>> coordinates) {
    for(Layer& l : all_layers)
        if(l.Active())
            for(std::pair<int, int> c : coordinates) {
                if(operation_mode["Red"])
                    l[c].setRed(op);
                if(operation_mode["Green"])
                    l[c].setGreen(op);
                if(operation_mode["Blue"])
                    l[c].setBlue(op);
                if(operation_mode["Alfa"])
                    l[c].setAlfa(op);
            }
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

Image& Image::select(RectangleShape r, int position) {
    if(position >= all_selections.size() || position < 0)
       throw ImageIndexOutOfBounds();

    all_selections[position].add(r);
    return *this;
}


Image& Image::addSelection(std::string name) {
    Selection newSelection;
    newSelection.setName(name);
    all_selections.push_back(newSelection);
    return *this;
}

std::vector<std::pair<std::string, std::string>> Image::getSelectionNames() const {
    std::vector<std::pair<std::string, std::string>> sol;
    for(const Selection& s : all_selections)
        sol.push_back({s.Name(), (s.isActive() ? "Active" : "Not Active")});
    
    return sol;
}

Image& Image::removeSelection(int position) {
    if(position >= all_selections.size() || position < 0)
       throw ImageIndexOutOfBounds();
    
    all_selections.erase(all_selections.begin() + position);
    
    return *this;
}

Image& Image::toggleSelection(int position) {
    if(position >= all_selections.size() || position < 0)
       throw ImageIndexOutOfBounds();
    
    all_selections[position].setActive(!all_selections[position].isActive());

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
        fitAll();
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
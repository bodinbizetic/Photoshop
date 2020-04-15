#include <algorithm>
#include <set>

#include "pixel.h"
#include "layer.h"
#include "image.h"
#include "selection.h"
#include "simple_operation.h"

Image& Image::useDiadic(std::string name, int arg) {
    std::function<int(int, int)> fun = diadic_functions[name];
    std::function<int(int)> fun_operation = std::bind(fun, std::placeholders::_1, arg);
    SimpleOperation op(fun_operation);
    applyOperation(op);
    return *this;
}

Image& Image::useOperation(int pos) {
    applyOperation(*all_operations[pos]);
    return *this;
}

Image& Image::applyOperationSelection(const Operation& op) {
    applyOperationCoordinates(op, getActiveCoordinates());
    return *this;
}

void Image::toGray() {
    auto coordinates = getActiveCoordinates();
    for(Layer& l : all_layers)
        if(l.Active())
            for(std::pair<int, int> c : coordinates) {
                l[c] = l[c].getGray();
            }
}

void Image::toBlackWhite() {
    auto coordinates = getActiveCoordinates();
     for(Layer& l : all_layers)
        if(l.Active())
            for(std::pair<int, int> c : coordinates) {
                l[c] = l[c].getBlackWhite();
            }
}

Image& Image::applyOperation(const Operation& op) {
    applyOperationSelection(op);
    
    return *this;
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

std::vector<std::pair<int, int>> Image::getActiveCoordinates() {
    std::set<std::pair<int, int>> all_coordinates;
    for(const Selection& s : all_selections)
        if(s.isActive()){
            auto vii = s.getSelectedCoordinates(dimensions);
            all_coordinates.insert(vii.begin(), vii.end());
        }
    
    if(all_coordinates.empty()){
        std::vector<std::pair<int,int>> coords;
        for(int i=0; i<dimensions.second; i++)
            for(int j=0; j<dimensions.first; j++)
                coords.push_back({j, i});
        return coords;
    }
        
    return {all_coordinates.begin(), all_coordinates.end()};
}

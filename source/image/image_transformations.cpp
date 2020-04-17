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
    applyOperationCoordinates(op, all_selections.getActiveCoordinates(dimensions));
    return *this;
}

void Image::toGray() {
    auto coordinates = all_selections.getActiveCoordinates(dimensions);
    for(Layer& l : all_layers)
        if(l.Active())
            for(std::pair<int, int> c : coordinates) {
                l[c] = l[c].getGray();
            }
}

void Image::toBlackWhite() {
    auto coordinates = all_selections.getActiveCoordinates(dimensions);
     for(Layer& l : all_layers)
        if(l.Active())
            for(std::pair<int, int> c : coordinates) {
                l[c] = l[c].getBlackWhite();
            }
}

void Image::invert() {
    std::vector<std::pair<int, int>> coordinates = all_selections.getActiveCoordinates(dimensions);
    SimpleOperation op([](int i) -> int{
        return Pixel::MAX_VALUE - i;
    });
    applyOperation(op);
}

void Image::blur() {
    std::vector<std::pair<int, int>> coordinates = all_selections.getActiveCoordinates(dimensions);
    for(Layer& l : all_layers)
        if(l.Active()) {
            Layer old(l);
            for(std::pair<int, int> c : coordinates)
                l[c] = old.getMedian(c);
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

#include <set>
#include <math.h>
#include <algorithm>

#include "formater_bmp.h"
#include "image.h"
#include "simple_operation.h"

Image::Image() {

}

Image::~Image() {
    
}

void Image::useDiadic(int pos, int arg) {
    std::function<int(int, int)> fun = all_operations.getDiadic(pos);
    SimpleOperation op(fun, arg, "", all_operations.getModeBinary());
    applyOperation(op);
}

void Image::useOperation(int pos) {
    applyOperation(*all_operations.getOperation(pos));
}

void Image::applyOperation(const Operation& op) {
    std::vector<std::pair<int, int>> selected = all_selections.getActiveCoordinates(Dimensions());
    applyOperationCoordinates(op, selected);
}

void Image::applyOperationCoordinates(const Operation& op, const std::vector<std::pair<int, int>>& selected) {
    for(Layer& l : all_layers) {
        OperationalLayer operational = makeOperationalLayer(l);
        op(operational, selected);
        for(std::pair<int, int> s : selected) {
            l[s].setAlfa(operational.matrix[operational.dimensions.first * s.second + s.first].alfa);
            l[s].setRed(operational.matrix[operational.dimensions.first * s.second + s.first].red);
            l[s].setBlue(operational.matrix[operational.dimensions.first * s.second + s.first].blue);
            l[s].setGreen(operational.matrix[operational.dimensions.first * s.second + s.first].green);
        }
    }
}

OperationalLayer Image::makeOperationalLayer(Layer& l) {
    std::vector<OperationalPixel> operational;
    for(Pixel p : l)
        operational.push_back({p.Red(), p.Green(), p.Blue(), p.Alfa()});
    return {operational, l.Dimension()};
}

std::vector<int> Image::getFinalResult() {
    auto vp = all_layers.combineLayers().Matrix();
    std::vector<int> vi;
    for(Pixel& p : vp)
        vi.push_back((int)p);
    return vi;
}
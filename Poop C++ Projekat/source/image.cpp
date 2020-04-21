#include <set>
#include <math.h>
#include <algorithm>

#include "formater_bmp.h"
#include "image.h"
#include "simple_operation.h"

Image::Image(std::string path) : project_manager(path) {

}

Image::~Image() {
    
}

void Image::useOperation(std::pair<int, int> op_id_arg) {
    Operation* operation_to_use = all_operations.getOperation(op_id_arg.first)->copy();
    operation_to_use->setParam(op_id_arg.second);
    applyOperation(*operation_to_use);
    delete operation_to_use;
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

/*
C:\Users\Dinbo\Desktop
*/
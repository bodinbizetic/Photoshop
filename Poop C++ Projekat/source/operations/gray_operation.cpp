#include "gray_operation.h"

OperationalLayer& GrayTransformation::operator()  (OperationalLayer& op, const std::vector<std::pair<int, int>>& toChange) const {
    for(auto coordinate : toChange){
        OperationalPixel& p = op.matrix[op.dimensions.first * coordinate.second + coordinate.first];
        int average = (p.red + p.green + p.blue) / 3;
        p.red = average;
        p.green = average;
        p.blue = average;
    }
    return op;
}
#include "gray_operation.h"

OperationalLayer& PixelTransformation::operator()  (OperationalLayer& op, const std::vector<std::pair<int, int>>& toChange) const {
    for(auto coordinate : toChange){
        OperationalPixel& p = op.matrix[op.dimensions.first * coordinate.second + coordinate.first];
        p = (*this)(p);
    }
    return op;
}

OperationalPixel& PixelTransformation::operator()(OperationalPixel& p) const {
    p = operation_function(p);
    return p;
}

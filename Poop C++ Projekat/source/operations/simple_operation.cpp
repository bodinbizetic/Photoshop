#include "simple_operation.h"

SimpleOperation::SimpleOperation(std::function<int(int)> operation_function_, std::string name_, int RGBA_mask )
:   operation_function(operation_function_),
    Operation(name_) {

}

SimpleOperation::SimpleOperation(std::function<int(int, int)> operation_function_, int arg, std::string name_, int RGBA_mask) 
: Operation(name_, RGBA_mask){

    operation_function = std::bind(operation_function_, std::placeholders::_1, arg);
}


OperationalLayer& SimpleOperation::operator() (OperationalLayer& op, const std::vector<std::pair<int, int>>& toChange) const {
    for(auto coordinate : toChange){
        OperationalPixel& p = op.matrix[op.dimensions.first * coordinate.second + coordinate.first];
        if(RGBA_mask & 0b1000)
            p.red = operation_function(p.red);
        if(RGBA_mask & 0b0100)
            p.blue = operation_function(p.blue);
        if(RGBA_mask & 0b0010)
            p.green = operation_function(p.green);
        if(RGBA_mask & 0b0001)
            p.alfa = operation_function(p.alfa);
    }
    return op; 
}

std::vector<Operation*> SimpleOperation::copyVector() const {
    return { new SimpleOperation(*this) };
}
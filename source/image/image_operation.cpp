#include "image.h"
#include "simple_operation.h"
#include "complex_operation.h"

void Image::createOperation(std::vector<std::pair<int, int>> op_arg, std::string name_) {
    std::vector<std::string> diadic = getDiadicNames();
    ComplexOperation cop(name_);
    for(std::pair<int, int> op : op_arg) {
        if(op.first < diadic.size()){
            auto fun = std::bind(diadic_functions[diadic[op.first]], std::placeholders::_1, op.second);
            cop.add(SimpleOperation(fun, diadic[op.first]));
        } else {
            cop.add(*all_operations[op.first - diadic.size()]);
        }
    }
    addOperation(cop);
}
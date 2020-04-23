#include "diadic_operation.h"
#include "simple_operation.h"

DiadicOperation::DiadicOperation(std::function<int(int, int)> function, int arg, std::string name_, int RGBA_mask)
: operation_function(function), argument(arg), Operation(name_, RGBA_mask){

}

OperationalLayer& DiadicOperation::operator()(OperationalLayer& op, const std::vector<std::pair<int, int>>& toChange) const {
	SimpleOperation sop(operation_function, argument, "", RGBA_mask);
	op = sop(op, toChange);
	return op;
}

OperationalPixel& DiadicOperation::operator()(OperationalPixel& op) const {
	SimpleOperation sop(operation_function, argument, "", RGBA_mask);
	op = sop(op);
	return op;
}

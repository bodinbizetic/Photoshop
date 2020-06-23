#ifndef __GRAY_OPERATION_H__
#define __GRAY_OPERATION_H__

#include <functional>
#include "operation.h"

class PixelTransformation : public Operation {
public:
    PixelTransformation(std::function<OperationalPixel&(OperationalPixel&)> function, std::string name_ = Operation::DEFAULT_OP_NAME)
        : Operation(name_), operation_function(function) {
    }
    ~PixelTransformation() {}

    virtual OperationalLayer& operator()  (OperationalLayer& op, const std::vector<std::pair<int, int>>& toChange) const override;
    virtual std::vector<Operation*> copyVector() const override { return { new PixelTransformation(*this) }; }
    virtual Operation* copy() const override { return new PixelTransformation(*this); }
    virtual OperationalPixel& operator() (OperationalPixel& op) const override;

private:    
    std::function<OperationalPixel&(OperationalPixel&)> operation_function;

};

#endif // __GRAY_OPERATION_H__

#ifndef __SIMPLE_OPERATION_H__
#define __SIMPLE_OPERATION_H__

#include <functional>

#include "operation.h"

class SimpleOperation : public Operation {
public:
    SimpleOperation(std::function<int(int)> operation_function_, std::string name_ = DEFAULT_OP_NAME, int RGBA_mask = 0b1110);
    SimpleOperation(std::function<int(int, int)> operation_function_, int arg, std::string name_ = DEFAULT_OP_NAME, int RGBA_mask = 0b1110);

    virtual OperationalLayer& operator() (OperationalLayer& op, const std::vector<std::pair<int, int>>& toChange) const override;
    virtual std::vector<Operation*> copyVector() const override;
    virtual Operation* copy() const override { return new SimpleOperation(*this); }
private:
    std::function<int(int)> operation_function;
};

#endif // __SIMPLE_OPERATION_H__

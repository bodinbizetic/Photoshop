#ifndef __SIMPLE_OPERATION_H__
#define __SIMPLE_OPERATION_H__

#include <functional>

#include "operation.h"

class SimpleOperation : public Operation {
public:
    SimpleOperation(std::function<int(int)> operation_function_, std::string name_ = DEFAULT_OP_NAME);

    virtual int operator() (int x) const override;
    virtual Operation* copy() const override;
private:
    std::function<int(int)> operation_function;
};

#endif // __SIMPLE_OPERATION_H__

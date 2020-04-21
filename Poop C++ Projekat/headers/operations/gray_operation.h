#ifndef __GRAY_OPERATION_H__
#define __GRAY_OPERATION_H__

#include "operation.h"

class GrayTransformation : public Operation {
public:
    GrayTransformation(std::string name_ = Operation::DEFAULT_OP_NAME)
        : Operation(name_) {
    }
    ~GrayTransformation() {}

    virtual OperationalLayer& operator()  (OperationalLayer& op, const std::vector<std::pair<int, int>>& toChange) const override;
    virtual std::vector<Operation*> copyVector() const override { return { new GrayTransformation(*this) }; }
    
    virtual Operation* copy() const override { return new GrayTransformation(*this); }

};

#endif // __GRAY_OPERATION_H__

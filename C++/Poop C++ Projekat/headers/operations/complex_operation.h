#ifndef __COMPLEX_OPERATION_H__
#define __COMPLEX_OPERATION_H__

#include <string>
#include <vector>
#include "operation.h"

class ComplexOperation : public Operation {
public:
    explicit ComplexOperation(std::vector<Operation*> operations = std::vector<Operation*>(), std::string name_ = DEFAULT_OP_NAME);
    ComplexOperation(std::string name_) : Operation(name_) {}
    virtual ~ComplexOperation() { clear(); }

    void add(const Operation& op);
    std::vector<Operation*>::iterator begin() { return operation_functions.begin(); }
    std::vector<Operation*>::iterator end()  {return operation_functions.end(); }

    ComplexOperation(const ComplexOperation& cop2);
    ComplexOperation operator=(const ComplexOperation& cop2);

    virtual OperationalLayer& operator() (OperationalLayer& op, const std::vector<std::pair<int, int>>& toChange) const override;
    virtual OperationalPixel& operator() (OperationalPixel& p) const override;
    virtual std::vector<Operation*> copyVector() const override;
    virtual Operation* copy() const override { return new ComplexOperation(*this); }

private:
    std::vector<Operation*> operation_functions;

    void copy(const ComplexOperation& cop);
    void clear();
};

#endif // __COMPLEX_OPERATION_H__

#ifndef __COMPLEX_OPERATION_H__
#define __COMPLEX_OPERATION_H__

#include <string>
#include <vector>
#include "operation.h"

class ComplexOperation : public Operation {
public:
    ComplexOperation(std::vector<Operation*> operations = std::vector<Operation*>(), std::string name_ = "");
    ~ComplexOperation();

    void add(const Operation& op);
    std::vector<Operation*>::iterator begin();
    std::vector<Operation*>::iterator end();

    ComplexOperation(const ComplexOperation& cop2);
    ComplexOperation operator=(const ComplexOperation& cop2);

    virtual int operator() (int x) override;
    virtual Operation* copy() override;
};

#endif // __COMPLEX_OPERATION_H__

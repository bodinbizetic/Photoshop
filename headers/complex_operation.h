#ifndef __COMPLEX_OPERATION_H__
#define __COMPLEX_OPERATION_H__

#include <string>
#include <vector>
#include "operation.h"

class ComplexOperation : public Operation {
public:
    ComplexOperation(std::vector<Operation*> operations = std::vector<Operation*>(), std::string name_ = "");
    virtual ~ComplexOperation() { clear(); }

    void add(const Operation& op);
    std::vector<Operation*>::iterator begin() { return operation_functions.begin(); }
    std::vector<Operation*>::iterator end()  {return operation_functions.end(); }

    ComplexOperation(const ComplexOperation& cop2);
    ComplexOperation operator=(const ComplexOperation& cop2);

    virtual int operator() (int x) override;
    virtual Operation* copy() const override;

private:
    std::vector<Operation*> operation_functions;

    std::vector<Operation*> copy(std::vector<Operation*> op) const;
    void copy(const ComplexOperation& cop);
    void clear();
};

#endif // __COMPLEX_OPERATION_H__

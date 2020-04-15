#ifndef __OPERATION_H__
#define __OPERATION_H__

#include <map>
#include <string>
#include <exception>

class OperationNameAlreadyExists : public std::exception {

};

class DivisionByZero : public std::exception {
    const char * what() const noexcept override {
        return "Division by zero";
    }
};

class Operation {
public:
    static const std::string DEFAULT_OP_NAME;
    
    Operation(std::string name_ = DEFAULT_OP_NAME);
    virtual ~Operation();
    std::string Name() const { return name; }
    void setName(std::string name_);

    virtual int operator() (int val) const = 0;
    virtual Operation* copy() const = 0;
private:
    std::string name;

};

#endif // __OPERATION_H__

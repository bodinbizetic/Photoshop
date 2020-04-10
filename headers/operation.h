#ifndef __OPERATION_H__
#define __OPERATION_H__

#include <map>
#include <string>
#include <exception>

class OperationNameAlreadyExists : public std::exception {

};

class Operation {
public:
    Operation(std::string name_ = "");
    virtual ~Operation();
    std::string Name() const { return name; }
    void setName(std::string name_);

    virtual int operator() (int val) = 0;
    virtual Operation* copy() = 0;
private:
    std::string name;

};

#endif // __OPERATION_H__

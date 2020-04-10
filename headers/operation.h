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
    ~Operation();
    std::string Name() const { return name; }
    void setName(std::string name_);

    virtual int operator() (int val) = 0;
private:
    static std::map<std::string, Operation*> all_operations;
    std::string name;

    static void remove(std::string name_);
};

#endif // __OPERATION_H__

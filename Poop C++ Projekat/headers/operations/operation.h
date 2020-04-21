#ifndef __OPERATION_H__
#define __OPERATION_H__

#include <map>
#include <string>
#include <exception>
#include <vector>

class Layer;

class OperationNameAlreadyExists : public std::exception {

};

class DivisionByZero : public std::exception {
    const char * what() const noexcept override {
        return "Division by zero";
    }
};

struct OperationalPixel {
    int red;
    int green;
    int blue;
    int alfa;
};

struct OperationalLayer {
    std::vector<OperationalPixel> matrix;
    std::pair<int, int> dimensions;
};

class Operation {
public:
    static const std::string DEFAULT_OP_NAME;
    
    Operation(std::string name_ = DEFAULT_OP_NAME, int RGBA_mask_ = 0b1110);
    virtual ~Operation();
    std::string Name() const { return name; }
    void setName(std::string name_);
    void setMask(int RGBA_mask_) { RGBA_mask = RGBA_mask_; }
    virtual OperationalLayer& operator() (OperationalLayer& op, const std::vector<std::pair<int, int>>& toChange) const = 0;
    virtual Operation* copy() const = 0;
    virtual std::vector<Operation*> copyVector() const = 0;
    virtual void setParam(int arg) {}

protected:
    int RGBA_mask;
private:
    std::string name;

};

#endif // __OPERATION_H__

#ifndef __TRANSFORMATION_H__
#define __TRANSFORMATION_H__

#include <functional>
#include "operation.h"
#include "layer.h"

class Transformation : public Operation {
public:
    Transformation(std::function<void(Layer&, std::pair<int, int>)> fun_, std::string name)
    : fun(fun_), Operation(name) {}
    ~Transformation() {}
    virtual int operator() (Layer&, std::vector<std::pair<int, int>>) const;
    virtual Operation* copy() const override { return new Transformation(*this); }
private:
    std::function<void(Layer&, std::pair<int, int>)> fun;
};

#endif // __TRANSFORMATION_H__

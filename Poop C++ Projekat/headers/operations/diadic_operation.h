#ifndef _DIADIC_OPERATION_H_
#define _DIADIC_OPERATION_H_

#include <functional>

#include "operation.h"

class DiadicOperation : public Operation {
public:
	DiadicOperation(std::function<int(int, int)> function, int arg = 0, std::string name_ = DEFAULT_OP_NAME, int RGBA_mask = 0b1110);

	virtual OperationalLayer& operator() (OperationalLayer& op, const std::vector<std::pair<int, int>>& toChange) const;
	virtual OperationalPixel& operator() (OperationalPixel& op) const;
	virtual Operation* copy() const { return new DiadicOperation(*this); }
	virtual std::vector<Operation*> copyVector() const { return { new DiadicOperation(*this) }; }
	virtual void setParam(int arg) { argument = arg; }
	virtual int getParam() const override { return argument;  }
private:
	int argument;
	std::function<int(int, int)> operation_function;
};

#endif // !_DIADIC_OPERATION_H_

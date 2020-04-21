#ifndef _MEDIAN_OPERATION_H_
#define _MEDIAN_OPERATION_H_

#include "operation.h"

class MedianOperation : public Operation {
public:
	MedianOperation(std::string name_ = DEFAULT_OP_NAME) : Operation(name_) {}
	virtual OperationalLayer& operator() (OperationalLayer& op, const std::vector<std::pair<int, int>>& toChange) const;
	virtual Operation* copy() const { return new MedianOperation(*this); }
	virtual std::vector<Operation*> copyVector() const { return { new MedianOperation(*this) }; };
private:
	bool checkCoordinate(const std::pair<int, int>& dimension, const std::pair<int, int>& coord) const;
	void getMedianPixel(const OperationalLayer& op_p, OperationalLayer& op_change, const std::pair<int, int>& c) const;
	int getMedianValueSort(std::vector<int>& median_vector, const int& size) const;

};

#endif // !_MEDIAN_OPERATION_H_

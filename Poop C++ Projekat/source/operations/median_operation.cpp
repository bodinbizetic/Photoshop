#include <algorithm>
#include <functional>
#include "median_operation.h"

// TODO: clear screen on consoleDraw

OperationalLayer& MedianOperation::operator() (OperationalLayer& op, const std::vector<std::pair<int, int>>& toChange) const {
	OperationalLayer copy_op = op;
	for (const std::pair<int, int>& c : toChange) {
		getMedianPixel(copy_op, op, c);
	}
	return op;
}

bool MedianOperation::checkCoordinate(const std::pair<int, int>& dimension, const std::pair<int, int>& coord) const {
	if(coord.first < 0 || coord.first >= dimension.first)
		return false;
	if (coord.second < 0 || coord.second >= dimension.second)
		return false;
	return true;
}

void MedianOperation::getMedianPixel(const OperationalLayer& op_p, OperationalLayer& op_change, const std::pair<int, int>& c) const {
	std::vector<int> red(8, INT_MAX), green(8, INT_MAX), blue(8, INT_MAX);
	int size=0;
	std::function<void(const OperationalPixel&)> add = [&](const OperationalPixel& p) {
		red[size] = p.red;
		green[size] = p.green;
		blue[size] = p.blue;
		size++;
	};
	if (checkCoordinate(op_p.dimensions, c))
		add(op_p[c]);
	if (checkCoordinate(op_p.dimensions, { c.first + 1, c.second }))
		add(op_p[{c.first + 1, c.second}]);
	if (checkCoordinate(op_p.dimensions, {c.first - 1, c.second}))
		add(op_p[{c.first - 1, c.second}]);
	if (checkCoordinate(op_p.dimensions, { c.first, c.second + 1 }))
		add(op_p[{c.first, c.second + 1}]);
	if (checkCoordinate(op_p.dimensions, { c.first, c.second - 1 }))
		add(op_p[{c.first, c.second - 1}]);
	op_change[c].red = getMedianValueSort(red, size);
	op_change[c].green = getMedianValueSort(green, size);
	op_change[c].blue = getMedianValueSort(blue, size);

}

int MedianOperation::getMedianValueSort(std::vector<int>& median_vector, const int& size) const {
	std::sort(median_vector.begin(), median_vector.end());
	int mid = size / 2;
	if (size % 2)
		return (median_vector[mid] + median_vector[mid + 1]) / 2;
	return median_vector[mid];
}


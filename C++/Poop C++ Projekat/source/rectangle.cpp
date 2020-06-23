#include "rectangle.h"
#include <algorithm>

bool RectangleShape::inRectangle(std::pair<int, int> dot) {
    if(between(coordinates.first, dimensions.first, dot.first) && 
        between(coordinates.second, dimensions.second, dot.second))
        return true;
    return false;
}

bool RectangleShape::between(int coord, int dim, int dot) {
    int first  =    std::min(coord, coord + dim);
    int second =    std::max(coord, coord + dim);
    if(first <= dot && dot <= second) return true;
    return false;
}
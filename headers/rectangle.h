#ifndef __RECTANGLE_H__
#define __RECTANGLE_H__

#include <utility>

class Rectangle {
public:
    Rectangle(int x, int y, int w, int h) : coordinates{x, y}, dimensions{w, h} {}
    Rectangle(std::pair<int, int> coord, std::pair<int, int> dim) : coordinates(coord), dimensions(dim) {}

    bool inRectangle(std::pair<int, int>);
private:
    std::pair<int, int> coordinates;
    std::pair<int, int> dimensions;

    bool between(int coord, int dim, int dot);
};

#endif // __RECTANGLE_H__

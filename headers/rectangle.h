#ifndef __RECTANGLE_H__
#define __RECTANGLE_H__

#include <utility>

class Rectangle {
public:
    Rectangle(int x, int y, int w, int h);
    Rectangle(std::pair<int, int>, std::pair<int, int>);

    bool inRectangle(std::pair<int, int>);
private:
    std::pair<int, int> coordinates;
    std::pair<int, int> dimensions;
};

#endif // __RECTANGLE_H__

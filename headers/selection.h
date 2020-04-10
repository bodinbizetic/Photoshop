#ifndef __SELECTION_H__
#define __SELECTION_H__

#include <vector>

#include "rectangle.h"

class Selection {
public:
    Selection();
    Selection(std::vector<Rectangle> selected_rectangles_) : selected_rectangles(selected_rectangles_) {}
    Selection(Rectangle r) { add(r); };

    bool isActive() const { return active; }
    void setActive(bool active_) { active = active_; }

    void add(Rectangle r);
    std::vector< std::pair<int, int> > getSelectedCoordinates(std::pair<int, int> dimension);
private:
    std::vector<Rectangle> selected_rectangles;
    bool active = true;
};

#endif // __SELECTION_H__

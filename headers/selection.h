#ifndef __SELECTION_H__
#define __SELECTION_H__

#include <vector>
#include <string>
#include "rectangle.h"

class Selection {
public:
    static const std::string DEFAULT_SELECT_NAME;

    Selection();
    Selection(std::vector<Rectangle> selected_rectangles_) : selected_rectangles(selected_rectangles_) {}
    Selection(Rectangle r) { add(r); };

    bool isActive() const { return active; }
    void setActive(bool active_) { active = active_; }
    void deselectAll() { selected_rectangles.clear(); }
    
    std::string Name() const { return name; }
    void setName(std::string s) { name = s; }


    void add(Rectangle r);
    std::vector< std::pair<int, int> > getSelectedCoordinates(std::pair<int, int> dimension);
private:
    std::string name = "";
    std::vector<Rectangle> selected_rectangles;
    bool active = true;
};

#endif // __SELECTION_H__

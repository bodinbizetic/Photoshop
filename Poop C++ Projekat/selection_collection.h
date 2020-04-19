#ifndef __SELECTION_COLECTION_H__
#define __SELECTION_COLECTION_H__

#include "selection.h"

class SelectionIndexOutOfBounds : public std::exception{
    const char* what() const noexcept override {
        return "Selection index out of bounds";
    }
};

class SelectionCollection {
public:
    void select(RectangleShape r, int position);
    void addSelection(std::string name_);
    std::vector<std::pair<std::string, std::string>> getSelectionNames() const;
    void removeSelection(int pos);
    void clearSelection(int pos);
    void toggleSelection(int position);
    std::vector<std::pair<int, int>> getActiveCoordinates(std::pair<int, int> dimensions) const;
private:
    std::vector<Selection> all_selections;
};

#endif // __SELECTION_COLECTION_H__

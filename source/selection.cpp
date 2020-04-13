#include <algorithm>

#include "selection.h"

const std::string Selection::DEFAULT_SELECT_NAME = "";


void Selection::add(RectangleShape r) {
    selected_rectangles.push_back(r);
}

std::vector< std::pair<int, int> > Selection::getSelectedCoordinates(std::pair<int, int> dimension) {
    std::vector< std::pair<int, int> > allCoordinates;
    for(int i=0; i<dimension.second; i++)
        for(int j=0; j<dimension.first; j++)
            if(std::count_if(selected_rectangles.begin(), selected_rectangles.end(), [i, j](RectangleShape r)->bool {
                return r.inRectangle({j, i});
            }))
                allCoordinates.push_back({j, i});

    return allCoordinates;
}

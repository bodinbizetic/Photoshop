#include <set>

#include "selection_collection.h"

void SelectionCollection::select(RectangleShape r, int position) {
    if(position >= all_selections.size() || position < 0)
       throw SelectionIndexOutOfBounds();

    all_selections[position].add(r);
}


void SelectionCollection::addSelection(std::string name) {
    Selection newSelection;
    newSelection.setName(name);
    all_selections.push_back(newSelection);
}

std::vector<std::pair<std::string, std::string>> SelectionCollection::getSelectionNames() const {
    std::vector<std::pair<std::string, std::string>> sol;
    for(const Selection& s : all_selections)
        sol.push_back({s.Name(), (s.isActive() ? "Active" : "Not Active")});
    
    return sol;
}

void SelectionCollection::removeSelection(int position) {
    if(position >= all_selections.size() || position < 0)
       throw SelectionIndexOutOfBounds();
    
    all_selections.erase(all_selections.begin() + position);
}

void SelectionCollection::toggleSelection(int position) {
    if(position >= all_selections.size() || position < 0)
       throw SelectionIndexOutOfBounds();
    
    all_selections[position].setActive(!all_selections[position].isActive());
}

std::vector<std::pair<int, int>> SelectionCollection::getActiveCoordinates(std::pair<int, int> dimensions) const {
    std::set<std::pair<int, int>> all_coordinates;
    for(const Selection& s : all_selections)
        if(s.isActive()){
            auto vii = s.getSelectedCoordinates(dimensions);
            all_coordinates.insert(vii.begin(), vii.end());
        }
    
    if(all_coordinates.empty()){
        std::vector<std::pair<int,int>> coords;
        for(int i=0; i<dimensions.second; i++)
            for(int j=0; j<dimensions.first; j++)
                coords.push_back({j, i});
        return coords;
    }
        
    return {all_coordinates.begin(), all_coordinates.end()};
}
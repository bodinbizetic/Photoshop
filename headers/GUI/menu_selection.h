#ifndef __MENU_SELECTION_H__
#define __MENU_SELECTION_H__

#include "image.h"
#include "menu.h"

class Menu_Selection : public Menu {
public:
    Menu_Selection(Image& project_) : project(project_), Menu({
        "Return",
        "Add selection",
        "Remove selection",
        "Show all selections",
        "Toggle selection",
        "Add to selection"
    }) {}
public:
    virtual void functionCall(std::string x);
    Image& project;

    void addSelection();
    void removeSelection();
    void showAllSelections();
    void toggleSelection();
    void addRectangle();

    
};

#endif // __MENU_SELECTION_H__

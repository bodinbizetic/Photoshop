#ifndef __MENU_LAYER_H__
#define __MENU_LAYER_H__

#include "menu.h"
#include "image.h"

class Menu_Layer : public Menu {
public:
    Menu_Layer(Image& project_) : project(project_), Menu({
        "Return",
        "Add layer",
        "Delete layer",
        "Show all layers",
        "Toggle layer",
        "Set Opacity",
        "Draw layer",
    }) {}
private:
    Image& project;
    void functionCall(std::string x) override;

    void addLayer();
    void deleteLayer();
    void printLayers();
};

#endif // __MENU_LAYER_H__

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
        "Swap layer",
        "Show combined"
    }) {}
private:
    Image& project;
    void functionCall(std::string x) override;

    void addLayer();
    void deleteLayer();
    void printLayers();
    void toggleLayer();
    void setOpacity();
    void draw();
    void swapLayers();
    void showCombined();

};

#endif // __MENU_LAYER_H__

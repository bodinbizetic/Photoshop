#ifndef __MENU_LAYER_H__
#define __MENU_LAYER_H__

#include "menu.h"
#include "image.h"

class LayerNameAlreadyExists : public std::exception {
    const char* what() const noexcept override {
        return "Layer name already exists";
    }
};

class ExtensionError : public std::exception {
    const char* what() const noexcept override {
        return "File type not supported";
    }
};

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
        "Show combined",
        "Save all"
    }) {}
private:
    Image& project;
    void functionCall(std::string x) override;

    void addLayer();
    void checkIfLayerExists(const LayerCollection& layers, std::string name);
    void deleteLayer();
    void printLayers();
    void toggleLayer();
    void setOpacity();
    void draw();
    void swapLayers();
    void showCombined();
    void saveAll(std::string ext);

    std::string getRelativePath(std::string path);

};

#endif // __MENU_LAYER_H__

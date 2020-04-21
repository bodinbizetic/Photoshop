#ifndef __MENU_IMAGE_H__
#define __MENU_IMAGE_H__

#include "menu.h"
#include "image.h"

class Menu_Image : public Menu {
public:
    Menu_Image(Image& project_) : project(project_), Menu({
        "Return",
        "Layer", 
        "Operation",
        "Selection",
        "File"
        }) {}
private:
    Image& project;
    void functionCall(std::string cmd) override;
};

#endif // __MENU_IMAGE_H__

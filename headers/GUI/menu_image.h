#ifndef __MENU_IMAGE_H__
#define __MENU_IMAGE_H__

#include "menu.h"
#include "image.h"

class Menu_Image : public Menu {
public:
    Menu_Image() : Menu({
        "Return",
        "Layer", 
        "Operation",
        "Selection"
        }) {}
private:
    Image project;
    void functionCall(std::string cmd) override;
};

#endif // __MENU_IMAGE_H__

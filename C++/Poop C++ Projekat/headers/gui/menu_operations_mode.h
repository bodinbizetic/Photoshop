#ifndef __MENU_OPERATIONS_MODE_H__
#define __MENU_OPERATIONS_MODE_H__

#include "menu.h"
#include "image.h"

class Menu_Operation_Mode : public Menu {
public:
    Menu_Operation_Mode(Image& project_) : project(project_), Menu({
        "Return",
        "Show modes",
        "Toggle mode"
    }) {}
private:
    Image& project;
    void functionCall(std::string x) override;

    void showCurrentOperationMode();
    void toggleOperationMode();
};

#endif // __MENU_OPERATIONS_MODE_H__

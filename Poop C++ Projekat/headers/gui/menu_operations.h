#ifndef __MENU_OPERATIONS_H__
#define __MENU_OPERATIONS_H__

#include "image.h"
#include "menu.h"

class Menu_Operation : public Menu {
public:
    Menu_Operation(Image& project_) : project(project_), Menu({
        "Return",
        "Show all operations",
        "Use operation",
        "Create operation",
        "Turn picture to gray",
        "Turn picture to Black and White",
        "Invert",
        "Blur",
        "Choose operation mode"
    }) {}
private:
    Image& project;
    void functionCall(std::string x) override;

    void showAllOperations();

    void useOperation();
    void applyOperation(std::pair<int, int> op_id_arg);

    void createOperation();
    std::pair<int, int> insertOperation();

    
};

#endif // __MENU_OPERATIONS_H__

#include "menu.h"

class Menu_Main : public Menu{
public:
    Menu_Main() : Menu({
        "Exit",
        "Create new Project", 
        "Open existing project",
    }) {}
private:
    void functionCall(std::string x) override;
};
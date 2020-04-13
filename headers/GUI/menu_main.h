#include "menu.h"

class PathNotExists {

};

class Menu_Main : public Menu{
public:
    Menu_Main() : Menu({
        "Exit",
        "Create new Project", 
        "Open existing project",
    }) {}
private:
    std::string path_="";
    void functionCall(std::string x) override;

    void initProject();
    void createProjectFolder();
    void createProjectResource();
};
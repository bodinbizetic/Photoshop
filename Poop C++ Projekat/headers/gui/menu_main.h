#include <string>
#include <utility>

#include "image.h"
#include "menu.h"

class PathNotExists : public std::exception{
    const char* what() const noexcept override {
        return "Path does not exists";
    }
};

class Menu_Main : public Menu{
public:
    Menu_Main() : Menu({
        "Exit",
        "Create new Project", 
        "Open existing project"
    }) {}
private:
    std::string path_= "";
    void functionCall(std::string x) override;

    std::pair<std::string, std::string> getProjectNameAndPath();

    std::string getProjectPath();
    Image* createProject();
    Image* loadProject();
};
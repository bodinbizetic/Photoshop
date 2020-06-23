#ifndef _MENU_EXPORT_H_
#define _MENU_EXPORT_H_

#include "image.h"
#include "menu.h"

class Menu_Export : public Menu {
public:
    Menu_Export(Image& project_) : project(project_), Menu({
        "Exit",
        "Export as BMP",
        "Export as PAM",
        }) {
    }
private:
    Image& project;

    void exportImage(std::string extension);
    void functionCall(std::string x) override;
};

#endif // !_MENU_EXPORT_H_

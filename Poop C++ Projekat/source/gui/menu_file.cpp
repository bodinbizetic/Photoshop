#include "menu_file.h"
#include "menu_export.h"

void Menu_File::functionCall(std::string x) {
    if (x == "0")
        running = false;
    else if (x == "1") {
        project.saveAll();
    }
    else if (x == "2") {
        Menu_Export m(project);
        m.start();
    }
    else if (x == "3") {
        //
    }
    else {
        throw WrongCommand();
    }
}
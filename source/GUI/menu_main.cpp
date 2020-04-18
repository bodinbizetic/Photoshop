#include <vector>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <exception>

#include "menu_main.h"
#include "menu_image.h"
#include "utilities.h"

void Menu_Main::functionCall(std::string x) {
    if(x == "0")
        running = false;
    else if(x == "1"){
        // initProject(); TODO: Uncoment
        Menu_Image mi;
        mi.start();
    } else if(x == "2") {
        // TODO: image open
    } else {
        throw WrongCommand();
    }
}

void Menu_Main::initProject() {
    createProjectFolder();
    createProjectResource();
}

void Menu_Main::createProjectFolder() {
    std::string name;
    std::cout << "Enter new name:\n>>> ";
    std::cin >> name;
    std::cout << "Enter new path:\n>>> ";
    std::string path;
    std::cin >> path;
    std::ofstream test(path + OS_SEP + "testtest123.txt");
    if(!test) {
        test.close();
        throw PathNotExists();
    }else{
        test.close();
        std::string command = DELETE_FILE + path + OS_SEP + "testtest123.txt";
        system(command.c_str());
    }
    std::string command = CHANGE_DIR + path;
    system(command.c_str());

    path_ = path + OS_SEP + name;
    command = MAKE_DIR + path_;
    system(command.c_str());

    command = CHANGE_DIR + path_;
    system(command.c_str());
}

void Menu_Main::createProjectResource() {
    std::string command = MAKE_DIR + path_ + OS_SEP + "resource";
    system(command.c_str());
}


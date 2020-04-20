#include <vector>
#include <iostream>
#include <fstream>
#include <utility>

#include "menu_main.h"
#include "menu_image.h"
#include "utilities.h"

void Menu_Main::functionCall(std::string x) {
    if(x == "0")
        running = false;
    else if(x == "1"){
        std::pair<std::string, std::string> p = createProject();
        Image project(p.first, p.second);
        project.getProjectManager().createProject();
        Menu_Image mi(project);
        mi.start();
    } else if(x == "2") {
        std::pair<std::string, std::string> p = openProject();
        Image project(p.first, p.second);
        Menu_Image mi(project);
        mi.start();
    } else {
        throw WrongCommand();
    }
}

std::pair<std::string, std::string> Menu_Main::createProject() {
    std::string name;
    std::cout << "Enter new name:\n>>> ";
    std::getline(std::cin, name);
    std::cout << "Enter new path:\n>>> ";
    std::string path;
    std::getline(std::cin, path);
    std::ofstream test(path + OS_SEP + "testtest123.txt");
    if(!test) {
        test.close();
        throw PathNotExists();
    }else{
        test.close();
        std::string command = DELETE_FILE + path + OS_SEP + "testtest123.txt";
        system(command.c_str());
    }
    return { path, name };
}

std::pair<std::string, std::string> Menu_Main::openProject() {
    std::string path;
    std::cout << "Insert project location:\n>>> ";
    std::getline(std::cin, path); // TODO: check validity - project file
    return { path, "name" }; // TODO: add name
}
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
        Image* project = createProject();
        Menu_Image mi(*project);
        mi.start();
        delete project;
    } else if(x == "2") {
        Image *project(loadProject());
        Menu_Image mi(*project);
        mi.start();
    } else {
        throw WrongCommand();
    }
}

std::pair<std::string, std::string> Menu_Main::getProjectNameAndPath() {
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

std::string Menu_Main::getProjectPath() {
    std::string path;
    std::cout << "Insert project location:\n>>> ";
    std::getline(std::cin, path);
    return path;
}

Image* Menu_Main::createProject() {
    std::pair<std::string, std::string> p = getProjectNameAndPath();
    Image *project = new Image(p.first);
    project->createProject(p.second);
    return project;
}

Image* Menu_Main::loadProject() {
    Image* project = new Image(getProjectPath());
    project->openProject();
    return project;
}

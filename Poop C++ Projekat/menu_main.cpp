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
        std::pair<std::string, std::string> p = createProjectFolder();
        Image project(p.first, p.second);
        createProjectResource(project);
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

std::pair<std::string, std::string> Menu_Main::createProjectFolder() {
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
    return { path, name };
}

void Menu_Main::createProjectResource(Image& project) {
    project.getProjectManager().createResourceFolder();
}

std::pair<std::string, std::string> Menu_Main::openProject() {
    std::string path;
    std::cout << "Insert project location:\n>>> ";
    std::cin >> path; // TODO: check validity - project file
    return { path, "name" }; // TODO: add name
}
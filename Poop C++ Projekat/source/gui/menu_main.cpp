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
        std::pair<std::string, std::string> p = getProjectNameAndPath();
        Image project(p.first);
        project.createProject(p.second);
        Menu_Image mi(project);
        mi.start();
    } else if(x == "2") {
        std::string path = getProjectPath();
        Image project(path);
        Menu_Image mi(project);
        try {
            project.openProject();
        }
        catch (Information& i) {
            mi.addHeader(i.what());
        }
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
    std::cout << "Insert project file location:\n>>> ";
    std::getline(std::cin, path); // TODO: check validity - project file
    return path; // TODO: add name
}
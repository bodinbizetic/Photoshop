#include <iostream>
#include <filesystem>
#define _TEST_
#include "menu_main.h"
#include "image.h"
#include <formater.h>
using std::cout;
using std::endl;

enum commands {SAVE_ALL, EXPORT};

std::string export_path = "";
commands returnCode = SAVE_ALL;
void loadImage(Image& project, int argc, char const* argv[]) {
    for (int i = 1; i < argc; i++) {
        if (argv[i] == "-e") {
            returnCode = EXPORT;
            export_path = argv[i + 1];
            i++;
            continue;
        }
        else if (!std::filesystem::exists(argv[i]))
            throw PathNotExists();
        if (std::filesystem::path(argv[i]).extension() == ".bmp" || std::filesystem::path(argv[i]).extension() == ".pam") {
            project.getLayerCollection().addLayer("ConsoleLayer" + std::to_string(i), argv[i], 100, 1);
        }
        else if (std::filesystem::path(argv[i]).extension() == ".fun") {
            Project_Manager_Formater formater(argv[i], "CustomOperation", "Operation");
            project.loadOperations({ formater.load() });
        }
        else if (std::filesystem::path(argv[i]).extension() == ".sel") {
            Project_Manager_Formater formater(argv[i], "Selection", "Rectangle");
            project.loadSelections({ formater.load() });
        }
        else {
            throw WrongCommand();
        }
    }
}

void exportTemp(std::string path, Image& project) {
    std::shared_ptr<Formater> formater(Formater::getFormater(path));
    formater->store(project.getFinalResult(), project.Dimensions());
}

int createCustomOperation(Image& project) {
    OperationCollection& oc = project.getOperationCollection();
    std::vector<std::pair<int, int>> new_op;
    for (int i = oc.getDefaultOpNum(); i < oc.getOperationNames().size(); i++)
        new_op.push_back({ i, 0 });
    oc.createOperation(new_op, "CurrentOperation");
    return oc.getOperationNames().size() - 1;
}

int main(int argc, char const *argv[]) {
    /*argc = 5;
    argv[1] = "-e";
    argv[2] = "C:\\Users\\Dinbo\\Desktop\\Paint\\Projekat\\resource\\test5.bmp";
    argv[3] = "C:\\Users\\Dinbo\\Desktop\\Paint\\Projekat\\resource\\L1.bmp";
    argv[4] = "C:\\Users\\Dinbo\\Desktop\\Paint\\Projekat\\resource\\L2.bmp";
   */
    if (argc <= 1) {
        Menu& m = *new Menu_Main();
        m.start();
        delete& m;
        return 0;
    }
    Image project("");
    try {
        loadImage(project, argc, argv);
        int op_id = createCustomOperation(project);
        project.useOperation({ op_id, 0 });
        if(returnCode == SAVE_ALL)
            project.getLayerCollection().saveAllLayers();
        else if (returnCode == EXPORT) {
            exportTemp(export_path, project);
        }
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return -1;
    }

    return 0;
}
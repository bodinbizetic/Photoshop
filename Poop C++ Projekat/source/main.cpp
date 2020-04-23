#include <iostream>
#include <filesystem>
#define _TEST_
#include "menu_main.h"
#include "image.h"
using std::cout;
using std::endl;

void loadImage(Image& project, int argc, char const* argv[]) {
    for (int i = 1; i < argc; i++) {
        if (!std::filesystem::exists(argv[i]))
            throw PathNotExists();
        if (std::filesystem::path(argv[i]).extension() == ".bmp" || std::filesystem::path(argv[i]).extension() == ".pam") {
            project.getLayerCollection().addLayer("ConsoleLayer", argv[i], 100, 1);
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

int createCustomOperation(Image& project) {
    OperationCollection& oc = project.getOperationCollection();
    std::vector<std::pair<int, int>> new_op;
    for (int i = oc.getDefaultOpNum(); i < oc.getOperationNames().size(); i++)
        new_op.push_back({ i, 0 });
    oc.createOperation(new_op, "CurrentOperation");
    return oc.getOperationNames().size() - 1;
}

int main(int argc, char const *argv[]) {
    argc = 3;
    argv[1] = "C:\\Users\\Dinbo\\Desktop\\MyProj\\Test1\\resource\\Layer2.bmp";
    argv[2] = "C:\\Users\\Dinbo\\Desktop\\MyProj\\Test1\\operations\\BB.fun";

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
        project.getLayerCollection().saveAllLayers();
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return -1;
    }

    return 0;
}
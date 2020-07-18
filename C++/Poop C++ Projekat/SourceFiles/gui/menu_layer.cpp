#include <algorithm>
#include <regex>
#include <fstream>
#include <string>
#include <iostream>
#include <filesystem>
#include "menu_layer.h"
#include "menu_main.h"
#include "utilities.h"
#include "project_manager.h"

void Menu_Layer::functionCall(std::string x) {
    if(x == "0")
        running = false;
    else if(x == "1"){
        addLayer();
    } else if(x == "2") {
        deleteLayer();
    } else if(x == "3") {
        printLayers();
    } else if(x == "4"){
        toggleLayer();
    } else if(x == "5") {
        setOpacity();
    } else if(x == "6") {
        draw();
    } else if(x == "7") {
        swapLayers();
    } else if(x == "8") {
        showCombined();
    } else if(x == "9") {
        saveAll("bmp");
    } else {
        throw WrongCommand();
    }
}

void Menu_Layer::addLayer() {
    LayerCollection &layers = project.getLayerCollection();
    std::string name;
    std::cout << "Layer name:\n>>> ";
    std::getline(std::cin, name);

    checkIfLayerExists(layers, name);

    std::string path;
    std::cout << "Path of BMP/PAM file to be loaded:\n>>> ";
    std::getline(std::cin, path);
    std::ifstream file(path);
    if(!file){
        file.close();
        addHeader("Not valid path: created empty layer");
        path="";
    }else {
        
        std::string newPath = getRelativePath(path);
        newPath = ProjectManager::resource_folder + OS_SEP + name + std::filesystem::path(path).extension().string();
        if(path != project.getProjectManager().getCwd() + OS_SEP + newPath)
            ProjectManager::copy(path, newPath);
        path = newPath;
    }
    
    if(layers.getLayerNames().size() == 0 && path == "") {
        int w = inputIntMsg("Width:\n>>> ");
        if(w < 1) addHeader("Not valid number");
        int h = inputIntMsg("Height:\n>>> ");
        if(h < 1) addHeader("Not valid number");
        
        layers.addLayer({w, h}, name); 
    } else
        layers.addLayer(-1, name, path);
}

void Menu_Layer::checkIfLayerExists(const LayerCollection& layers, std::string name) {
    auto names = layers.getLayerNames();
    if(std::find_if(names.begin(), names.end(), [&name](std::pair<std::string, std::string> s)->bool {
        return s.first == name;
        
    }) != names.end()){
        throw LayerNameAlreadyExists();
    }
}

std::string Menu_Layer::getRelativePath(std::string path) {
    std::regex reg(".*\\\\(.+\\.(?:(?:bmp)|(?:pam)))");
    std::cmatch match;
    std::regex_match(path.c_str(), match, reg);
    // std::cout << match[0] << std::endl;
    if(match[1] == "")
        throw ExtensionError();
    return match[1];
}

void Menu_Layer::deleteLayer() {
    printLayers();
    clClean();
    LayerCollection &layers = project.getLayerCollection();
    layers.removeLayer(inputIntMsg("Insert position of layer to be removed:\n>>> "));
}

void Menu_Layer::printLayers() {
    LayerCollection &layers = project.getLayerCollection();
    std::vector< std::pair<std::string, std::string> > names = layers.getLayerNames();
    int x=0;
    for(const std::pair<std::string, std::string>& n : names)
        std::cout << x++ << ". " << n.first << "\t" << n.second << std::endl;
    setClean();
}

void Menu_Layer::toggleLayer() {
    printLayers();
    clClean();
    LayerCollection &layers = project.getLayerCollection();
    layers.toggleLayer(inputIntMsg("Insert position of layer to be toggled:\n>>> "));
    
}

void Menu_Layer::setOpacity() {
    printLayers();
    clClean();
    int pos = inputIntMsg("Insert position of layer:\n>>> ");
    int val = inputIntMsg("Insert value of opacity [0-100]:\n>>> ");
    if(val > Layer::MAX_OPACITY){
        val = Layer::MAX_OPACITY;
    }
    if(val < Layer::MIN_OPACITY)
        val = Layer::MIN_OPACITY;
        LayerCollection &layers = project.getLayerCollection();
    layers.setOpacity(pos, val);
    std::cout << "Opacity set to " << val << std::endl;
    
}

void Menu_Layer::draw() {
    int pos = inputIntMsg("Insert position of layer to be drawn:\n>>> ");
    LayerCollection &layers = project.getLayerCollection();
    std::vector<int> matrix = layers.getLayerMatrix(pos);
    std::pair<int, int> dim = layers.Dimensions();
    system("cls");
    consoleDraw(matrix, dim);
    std::string unused;
    std::getline(std::cin, unused);
}

void Menu_Layer::swapLayers() {
    int l1 = inputIntMsg("Input first layer id:\n>>> ");
    int l2 = inputIntMsg("Input second layer id:\n>>> ");
    LayerCollection &layers = project.getLayerCollection();
    layers.swapLayers(l1, l2);
}

void Menu_Layer::showCombined() {
    consoleDraw(project.getFinalResult(), project.Dimensions());
    std::string x;
    std::getline(std::cin, x);
}

void Menu_Layer::saveAll(std::string ext) {
    LayerCollection& layers = project.getLayerCollection();
    if(ext == "bmp")
        layers.saveAllLayers(ProjectManager::resource_folder);
}

/* Create empty layer and show
1
1
1
Name2
C:\Users\Dinbo\Desktop\PROJEKAT1\bmp_24.bmp
1
Name3
C:\Users\Dinbo\Desktop\PROJEKAT1\bmp_24_2.bmp
8


*/
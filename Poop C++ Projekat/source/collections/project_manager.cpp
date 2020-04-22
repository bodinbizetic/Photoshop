#include <iostream>
#include <direct.h>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <memory>
#include <windows.h>
#include "utilities.h"
#include "project_manager.h"
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"

const std::string ProjectManager::resource_folder   = "resource";
const char *ProjectManager::project_file_name = "Project.xml";
const char *ProjectManager::xml_project_name = "Project";
const char *ProjectManager::xml_layers_name   = "Layers";



ProjectManager::ProjectManager(std::string cwd_) : current_working_directory(cwd_) {
    if(!std::filesystem::exists(current_working_directory))
        throw DirectoryNotFound(); // TODO: somewhere there is substr for BMP and PAM: fix it
}

void ProjectManager::createProject(std::string name_) {
    name = name_;
    createProjectFolderAndMove();
    createResourceFolder();
    
    std::ofstream file(project_file_name);
    file << *createProjectFile();
    file.close();
}

void ProjectManager::saveLayers(std::shared_ptr<xml::xml_document<>> doc, const std::vector<LayerInfo>& all_layer_info) {
    xml::xml_node<char>* layers_node = doc->allocate_node(xml::node_element, xml_layers_name);
    doc->first_node(xml_project_name)->append_node(layers_node);
    for (const LayerInfo& info : all_layer_info) {
        saveLayer(doc, info);
    }
}

void ProjectManager::createProjectFolderAndMove() {
    std::string project_path = current_working_directory + OS_SEP + name;

    _mkdir(project_path.c_str());
    _chdir(project_path.c_str());
    current_working_directory = project_path;
}

void ProjectManager::createResourceFolder() {
    if(std::filesystem::exists(resource_folder))
        return;
    _mkdir(resource_folder.c_str());
}

std::shared_ptr<xml::xml_document<>> ProjectManager::createProjectFile() {
    std::shared_ptr< xml::xml_document<> > doc(new xml::xml_document<>(), [](xml::xml_document<>* doc) { doc->clear(); });
    xml::xml_node<char>* root = doc->allocate_node(xml::node_element, xml_project_name);
    root->append_attribute(doc->allocate_attribute("name", name.c_str()));
    doc->append_node(root);

    return doc;
}

ProjectInfo ProjectManager::openProject() {
    _chdir(current_working_directory.c_str());
    checkProjectFile();
    return loadProject();
}

void ProjectManager::checkProjectFile() {
    if (!std::filesystem::exists(project_file_name))
        throw ProjectFileNotFound(project_file_name);
}

ProjectInfo ProjectManager::loadProject() {
    ProjectInfo project_info;
    std::shared_ptr< xml::xml_document<> > doc(initXmlReader(), [](xml::xml_document<>* doc) { doc->clear(); });
    loadProjectInfo(doc);
    project_info.layer_info = loadLayersInfo(doc);

    return project_info;
}

xml::xml_document<>* ProjectManager::initXmlReader() {
    xml::xml_document<>* doc = new xml::xml_document<>();
    std::stringstream buffer;

    std::ifstream xml_file(project_file_name);
    buffer << xml_file.rdbuf();
    static char content[100000];
    strcpy_s(content, buffer.str().c_str());
    try {
        doc->parse<0>(&content[0]);
    }
    catch (...) { throw ProjectFileCorrupted(); }
    xml_file.close();
    return doc;
}

void ProjectManager::loadProjectInfo(std::shared_ptr< xml::xml_document<> > doc) {
    name = doc->first_node()->first_attribute()->value();
}

std::vector<LayerInfo> ProjectManager::loadLayersInfo(std::shared_ptr<xml::xml_document<>> doc) {
    std::vector<LayerInfo> all_info;
    xml::xml_node<char>* root = doc->first_node("Project");
    xml::xml_node<char>* layers_node = root->first_node("Layers");   
    for (xml::xml_node<char>* layer = layers_node->first_node();
        layer; layer = layer->next_sibling()) {

        LayerInfo newInfo;
        newInfo.name = layer->first_attribute("name")->value();
        newInfo.path = layer->first_attribute("path")->value();
        newInfo.opacity = atoi(layer->first_attribute("opacity")->value());
        std::string active = layer->first_attribute("active")->value();
        newInfo.active = (active == "true" ? true : false);
        all_info.push_back(newInfo);
    }
    return all_info;
}

void ProjectManager::storeProjectInfo(std::shared_ptr<xml::xml_document<>> doc) {
    xml::xml_node<char>* project = doc->allocate_node(xml::node_element, "Project");
    project->append_attribute(doc->allocate_attribute("name", name.c_str()));
    doc->append_node(project);
}

void ProjectManager::saveLayer(std::shared_ptr<xml::xml_document<>> doc, const LayerInfo& layer_info) {
    xml::xml_node<char> *layer_node = doc->first_node("Project")->first_node(xml_layers_name);
    xml::xml_node<char> *curr_layer = doc->allocate_node(xml::node_element, "Layer");
    char buff[20];
    _itoa_s(layer_info.opacity, buff, 10);
    char active[6];
    strcpy_s(active, (layer_info.active ? "true" : "false"));

    curr_layer->append_attribute(doc->allocate_attribute("name", layer_info.name.c_str()));
    curr_layer->append_attribute(doc->allocate_attribute("path", layer_info.path.c_str()));
    curr_layer->append_attribute(doc->allocate_attribute("opacity", doc->allocate_string(buff)));
    curr_layer->append_attribute(doc->allocate_attribute("active", doc->allocate_string(active)));
    layer_node->append_node(curr_layer);
}

void ProjectManager::copy(std::string src, std::string dst) {
    if (src == dst || src == std::filesystem::current_path().string() + OS_SEP + dst)
        return;
    std::ifstream input(src, std::ios::binary);
    std::ofstream output(dst, std::ios::binary);
    if(input.fail() || output.fail()){
        throw DirectoryNotFound();
    }
    char c;
    while(!input.eof()){
        input.read(&c, 1);
        output.write(&c, 1);
    }

    output.close();
    input.close();
}
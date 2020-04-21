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

const std::string ProjectManager::resource_folder = "resource";
const std::string ProjectManager::project_file_name = "Project.xml";


ProjectManager::ProjectManager(std::string cwd_) : current_working_directory(cwd_) {
    if(!std::filesystem::exists(current_working_directory))
        throw DirectoryNotFound(); // TODO: somewhere there is substr for BMP and PAM: fix it
}

void ProjectManager::createProject(std::string name_) {
    name = name_;
    createProjectFolderAndMove();
    createResourceFolder();
    createProjectFile();
}

void ProjectManager::openProject() {
    _chdir(current_working_directory.c_str());
    checkProjectFile();
    loadProject();
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

void ProjectManager::createProjectFile() {
    std::shared_ptr< xml::xml_document<> > doc(new xml::xml_document<>(), [](xml::xml_document<>* doc) { doc->clear(); });
    storeProjectInfo(doc);
    std::ofstream xml_file(project_file_name);
    xml_file << *doc;
    xml_file.close();
    
}

void ProjectManager::checkProjectFile() {
    if (!std::filesystem::exists(project_file_name))
        throw ProjectFileNotFound(project_file_name);
}

void ProjectManager::loadProject() {
    std::shared_ptr< xml::xml_document<> > doc(initXmlReader(), [](xml::xml_document<>* doc) { /*doc->clear();*/ });
    loadProjectInfo(doc);
    
}

xml::xml_document<>* ProjectManager::initXmlReader() {
    xml::xml_document<>* doc = new xml::xml_document<>();
    std::ifstream xml_file(project_file_name);
    std::stringstream buffer;
    buffer << xml_file.rdbuf();
    static std::string content = buffer.str();
    doc->parse<0>(&content[0]);
    name = doc->first_node()->name();
    xml_file.close();
    return doc;
}

void ProjectManager::loadProjectInfo(std::shared_ptr< xml::xml_document<> > doc) {
    name = doc->first_node()->name();
}

void ProjectManager::storeProjectInfo(std::shared_ptr<xml::xml_document<>> doc) {
    xml::xml_node<char>* project = doc->allocate_node(xml::node_element, "Project");
    project->append_attribute(doc->allocate_attribute("name", name.c_str()));
    doc->append_node(project);
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
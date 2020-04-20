#include <direct.h>
#include <fstream>
#include <filesystem>
#include <windows.h>
#include "utilities.h"
#include "project_manager.h"
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
namespace xml = rapidxml;

const std::string ProjectManager::resource_folder = "resource";
ProjectManager::ProjectManager(std::string cwd_, std::string name_) : name(name_), current_working_directory(cwd_) {
    if(!std::filesystem::exists(current_working_directory))
        throw DirectoryNotFound(); // TODO: somewhere there is substr for BMP and PAM: fix it
}

void ProjectManager::createProject() {
    createProjectFolderAndMove();
    createResourceFolder();
    createProjectFile();
}

void ProjectManager::createProjectFolderAndMove() {
    std::string project_path = current_working_directory + OS_SEP + name;
    /*if(!std::filesystem::exists(current_working_directory))
        throw DirectoryAlreadyExists();*/
    

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
    xml::xml_document<> *doc = new xml::xml_document<>;
    xml::xml_node<char>* project = doc->allocate_node(xml::node_element, "Project");
    project->append_attribute(doc->allocate_attribute("name", name.c_str()));
    doc->append_node(project);
    std::ofstream xml_file(name + ".proj");
    xml_file << *doc;
    xml_file.close();
    doc->clear();
    delete doc;
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
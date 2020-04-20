#include <direct.h>
#include <fstream>
#include <filesystem>
#include <windows.h>
#include "utilities.h"
#include "project_manager.h"

const std::string ProjectManager::resource_folder = "resource";

ProjectManager::ProjectManager(std::string cwd_, std::string name_) : name(name_), current_working_directory(cwd_) {
    if(!std::filesystem::exists(current_working_directory))
        throw DirectoryNotFound();
    _chdir(current_working_directory.c_str());
    createProjectFolder();
}

void ProjectManager::createProjectFolder() {
    std::string project_path = current_working_directory + OS_SEP + name;
    if(!std::filesystem::exists(current_working_directory))
        throw DirectoryAlreadyExists();
    
    _mkdir(project_path.c_str()); 
    _chdir(project_path.c_str());
}

void ProjectManager::createResourceFolder() {
    if(std::filesystem::exists(resource_folder))
        return;
    _mkdir(resource_folder.c_str());
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
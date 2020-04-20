#ifndef __PROJECT_MANAGER_H__
#define __PROJECT_MANAGER_H__

#include <string>
#include "rapidxml.hpp"

namespace xml = rapidxml;


class DirectoryNotFound : public std::exception {
    const char * what() const noexcept override{
        return "Directory with that name does not exists";
    }
};

class DirectoryAlreadyExists : public std::exception {
    const char * what() const noexcept override{
        return "Directory with that name already exists";
    }
};

class ProjectFileNotFound : public std::exception {
public:
    ProjectFileNotFound(std::string path_) : path(path_) {}
    const char* what() const noexcept override {
        std::string ret = "Could not find project file at " + path;
        return ret.c_str();
    }
private:
    std::string path;
};

class ProjectManager {
public:
    static const std::string resource_folder;
    static const std::string project_file_name;

    static void copy(std::string src, std::string dst);

    ProjectManager(std::string cwd_);
    std::string getCwd() { return current_working_directory; }
    void createProject(std::string name_);
    void openProject();
private:
    std::string current_working_directory;
    std::string name;

    void createProjectFolderAndMove();
    void createResourceFolder();
    void createProjectFile();

    void checkProjectFile();
    void loadProject();
    xml::xml_document<>* initXmlReader();
    void loadProjectInfo(std::shared_ptr< xml::xml_document<> > doc);
};

#endif // __PROJECT_MANAGER_H__

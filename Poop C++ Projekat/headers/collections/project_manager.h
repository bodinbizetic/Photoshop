#ifndef __PROJECT_MANAGER_H__
#define __PROJECT_MANAGER_H__

#include <string>
#include <vector>
#include "rapidxml.hpp"

namespace xml = rapidxml;

class ProjectFileCorrupted : public std::exception {
    const char* what() const noexcept override {
        return "Project file is corrupted";
    }
};

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
        return "Could not find project file";
    }
private:
    std::string path;
};

struct LayerInfo {
    std::string name;
    std::string path;
    int opacity;
    bool active;
};

struct ProjectInfo {
    std::vector<LayerInfo> layer_info;
};

class ProjectManager {
public:
    static const std::string resource_folder;
    static const char *project_file_name;
    static const char *xml_project_name;
    static const char *xml_layers_name;

    static void copy(std::string src, std::string dst);

    ProjectManager(std::string cwd_);
    std::string getCwd() { return current_working_directory; }
    void createProject(std::string name_);
    xml::xml_document<>* initXmlReader();
    ProjectInfo openProject();

    std::shared_ptr<xml::xml_document<>> createProjectFile();
    void saveLayers(std::shared_ptr<xml::xml_document<>> doc, const std::vector<LayerInfo>& all_layer_info);
    std::vector<LayerInfo> loadLayersInfo(std::shared_ptr<xml::xml_document<>> doc);
private:
    std::string current_working_directory;
    std::string name;

    void checkProjectFile();
    void createProjectFolderAndMove();
    void createResourceFolder();

    ProjectInfo loadProject();
    void loadProjectInfo(std::shared_ptr< xml::xml_document<> > doc);

    void storeProjectInfo(std::shared_ptr< xml::xml_document<> > doc);
    void saveLayer(std::shared_ptr<xml::xml_document<>> doc, const LayerInfo& layer_info);

};

#endif // __PROJECT_MANAGER_H__

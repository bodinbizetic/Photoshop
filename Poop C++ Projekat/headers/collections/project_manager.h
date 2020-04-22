#ifndef __PROJECT_MANAGER_H__
#define __PROJECT_MANAGER_H__

#include <string>
#include <vector>
#include "rectangle.h"
#include "rapidxml.hpp"
#include "project_manager_formater.h"

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
    static const std::string selection_folder;
    static const char *project_file_name;
    static const char *xml_project_name;
    static const char* xml_layers_name;
    static const char *xml_selection_name;

    static void copy(std::string src, std::string dst);

    ProjectManager(std::string cwd_);
    std::string getCwd() { return current_working_directory; }
    ProjectInfo openProject();
    std::vector<LayerInfo> loadLayersInfo(std::shared_ptr<xml::xml_document<>> doc);

    void saveLayers(std::shared_ptr<xml::xml_document<>> doc, const std::vector<LayerInfo>& all_layer_info);
    void saveSelections(std::shared_ptr<xml::xml_document<>> doc, const std::vector<PM_Formater_info>& all_selection_info);

    void createProject(std::string name_);
    std::shared_ptr<xml::xml_document<>> createProjectFile();
    xml::xml_document<>* initXmlReader();
private:
    std::string current_working_directory;
    std::string name;

    void checkProjectFile();
    void createProjectFolderAndMove();
    void createResourceFolder();
    void createSelectionFolder();

    ProjectInfo loadProject();
    void loadProjectInfo(std::shared_ptr< xml::xml_document<> > doc);

    void storeProjectInfo(std::shared_ptr< xml::xml_document<> > doc);
    void saveLayer(std::shared_ptr<xml::xml_document<>> doc, const LayerInfo& layer_info);

};

#endif // __PROJECT_MANAGER_H__

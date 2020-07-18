#ifndef _PROJECT_MANAGER_SELECTION_H_
#define _PROJECT_MANAGER_SELECTION_H_

#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>  
#include <filesystem>
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"

namespace xml = rapidxml;

class FileCorrupted : public std::exception {
    const char* what() const noexcept override {
        return "Project is corrupted";
    }
};

class PMFormaterFileNotExists : public std::exception {
    const char* what() const noexcept override {
        return "Corrupted project files";
    }
};

struct PM_Formater_info {
    std::string name;
    std::map<std::string, std::string> header;
    std::vector<std::map<std::string, std::string>> body;
};

class Project_Manager_Formater {
public:
    Project_Manager_Formater(std::string path_, std::string header_name_ = "Header", std::string body_name_ = "Body");
    ~Project_Manager_Formater() { doc->clear(); delete doc; }

    void store(const PM_Formater_info& toStore);
    PM_Formater_info load();

private:
    std::string path;
    std::string header_name;
    std::string body_name;
    xml::xml_document<>* doc;

    void storeHeader(const std::map<std::string, std::string>& header);
    void storeBody(const std::vector<std::map<std::string, std::string>>& body);
    
    void loadDocument();
    std::map<std::string, std::string> loadHeader();
    std::vector<std::map<std::string, std::string>> loadBody();
};

#endif // !_PROJECT_MANAGER_SELECTION_H_


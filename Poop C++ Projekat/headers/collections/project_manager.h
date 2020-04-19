#ifndef __PROJECT_MANAGER_H__
#define __PROJECT_MANAGER_H__

#include <string>

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

class ProjectManager {
public:
    static const std::string resource_folder;
    static void copy(std::string src, std::string dst);

    ProjectManager(std::string cwd_, std::string name);
    std::string getCwd() { return current_working_directory; }
    void createProjectFolder();
    void createResourceFolder();
private:
    std::string current_working_directory;
    std::string name;
};

#endif // __PROJECT_MANAGER_H__

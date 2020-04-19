#ifndef __FORMATER_H__
#define __FORMATER_H__

#include <vector>
#include <string>

class FileDoesNotExist : public std::exception{
    const char* what() const noexcept override {
        return "Could not find the file requested";
    }
};

class FilePermissionDenied : public std::exception {
    const char* what() const noexcept override {
        return "Could not open the file requested";
    }
};

class Formater {
public:
    Formater(std::string path_) : path(path_) {}
    virtual std::vector<int> load() = 0;
    virtual void store(std::vector<int>, std::pair<int, int> dimensions) = 0;
    virtual std::pair<int, int> Dimensions() const = 0;
protected:
    std::string path;
};

#endif // __FORMATER_H__
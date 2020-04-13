#ifndef __FORMATER_H__
#define __FORMATER_H__

#include <vector>
#include <string>

class FileDoesNotExist {

};

class Formater {
public:
    Formater(std::string path_) : path(path_) {}
    virtual std::vector< std::vector<int> > load() = 0;
    virtual void store(std::vector< std::vector<int> >) = 0;
protected:
    std::string path;
};

#endif // __FORMATER_H__
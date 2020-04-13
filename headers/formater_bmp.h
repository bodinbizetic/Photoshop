#ifndef __FORMATER_BMP_H__
#define __FORMATER_BMP_H__

#include <fstream>

#include "formater.h"

class Formater_BMP : public Formater {
public:
    Formater_BMP(std::string path_);
    std::vector< std::vector<int> > load();
    void store(std::vector< std::vector<int> >) {};
private:
    std::pair<unsigned int, unsigned int> dimension;
    bool hasAlfa;
    unsigned int size_with_padding;
    unsigned int size_with_header;
    unsigned int offset_for_pixels;

    void loadAlfa(std::ifstream& file);
    void loadDimensions(std::ifstream& file);
    void loadOff_Pixels(std::ifstream& file);

    int readByte_1(std::ifstream& file);
    int readBytes(std::ifstream& file, int n);
};

#endif // __FORMATER_BMP_H__

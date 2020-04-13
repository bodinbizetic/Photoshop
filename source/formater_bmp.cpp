#include <iostream>
#include <algorithm>

#include "formater_bmp.h"

const unsigned int OFFSET_NUMBER_OF_BITS_PER_PIXEL = 0x1C; 
const unsigned int OFFSET_WIDTH = 0x12;
const unsigned int OFFSET_HEIGHT =  0x16;
const unsigned int OFFSET_SIZE_PADDING = 0x22;
const unsigned int OFFSET_PIXELS = 0xA;

std::vector <std::vector<int>> Formater_BMP::load() {
    std::ifstream file(path, std::ios::binary);
    
    std::cout << dimension.first << " " << dimension.second << std::endl;

    std::vector <std::vector<int>> matrix(dimension.second, std::vector<int>(dimension.first, 0));
    file.seekg(offset_for_pixels);
    std::for_each(matrix.rbegin(), matrix.rend(), [&file, this](std::vector<int> &vi) {
        for(int &i : vi){ 
            i = this->readBytes(file, (this->hasAlfa ? 32 : 24));
            if(this->hasAlfa == false){
                i += 255 << 24;
            }
        }
    });

    file.close();

    return matrix;
}

Formater_BMP::Formater_BMP(std::string path_) : Formater(path_) {
    std::ifstream file;
    file.open(path, std::ios::binary);

    if(file.fail()) throw FileDoesNotExist();
    
    loadAlfa(file);
    loadDimensions(file);
    loadOff_Pixels(file);
    
    std::cout << dimension.first << " " << dimension.second << std::endl;
    file.close();
}

void Formater_BMP::loadAlfa(std::ifstream& file) {
    file.seekg(OFFSET_NUMBER_OF_BITS_PER_PIXEL);
    if(readBytes(file, 2) == 32)
        hasAlfa = true;
    else 
        hasAlfa = false;
}

void Formater_BMP::loadDimensions(std::ifstream& file) {
    file.seekg(OFFSET_WIDTH);
    dimension.first =  readBytes(file, 4);
    file.seekg(OFFSET_HEIGHT);
    dimension.second = readBytes(file, 4);
    // char byte[2];
    // for(int i=0; i<10; i++){

    //     file.read(byte, 1);
    // }
}

void Formater_BMP::loadOff_Pixels(std::ifstream& file) {
    file.seekg(OFFSET_PIXELS);
    offset_for_pixels = readBytes(file, 4);
}

int Formater_BMP::readByte_1(std::ifstream& file) {
    char byte;
    file.read(&byte, 1);
    return (unsigned char)byte;
}

int Formater_BMP::readBytes(std::ifstream& file, int n) {
    unsigned int input=0;
    int shift_count = 0;
    for(int i=0; i<n; i++) {
        input += readByte_1(file) << shift_count;
        shift_count += 8;
    }
    return input;
}


#include <iostream>
#include <algorithm>

#include "formater_bmp.h"

const unsigned int OFFSET_NUMBER_OF_BITS_PER_PIXEL = 0x1C; 
const unsigned int OFFSET_WIDTH = 0x12;
const unsigned int OFFSET_HEIGHT =  0x16;
const unsigned int OFFSET_SIZE_PADDING = 0x22;
const unsigned int OFFSET_PIXELS = 0xA;

std::vector<int> Formater_BMP::load() {
    std::ifstream file(path, std::ios::binary);
    std::vector <int> matrix(dimension.second*dimension.first, 0);

    file.seekg(offset_for_pixels, std::ios::beg);
    // char c;
    // file.read(&c, 1);
    int x=0;
    for(int i=0; i<dimension.second; i++) {
        for(int j=0; j<dimension.first; j++){
            int newElement = readBytes(file, 3) | 0xff000000; // TODO: Make to work with 32 bit BMP
            matrix[i * dimension.first + j] = newElement;
        }
        readBytes(file, 4 - dimension.first * 3 % 4);
    }

    file.close();
    
    return matrix;
}

void Formater_BMP::store(std::vector<int> matrix) {
    std::ofstream file("output.bmp", std::ios::binary | std::ios::out);

    std::ifstream input(path, std::ios::binary);
    int i;
    for(i=0; i < offset_for_pixels; i++) {
        char c;
        int temp = readByte_1(input);
        // file.write(&c, 1);
        storeByte_1(file, temp);
    }
    std::cout << i << std::endl;
    for(int i=0; i<dimension.second; i++){
        int j;
        for(j=0; j<dimension.first; j++){
            storeBytes(file, matrix[i*dimension.first + j], 3);
        }
        for(int k=0; k < 4 - dimension.first*3 % 4; k++)
            storeByte_1(file, 0);
    }
    
    file.close();
    input.close();
}

Formater_BMP::Formater_BMP(std::string path_) : Formater(path_) {
    std::ifstream file;
    file.open(path, std::ios::binary);

    if(file.fail()) throw FileDoesNotExist();
    
    loadAlfa(file);
    loadDimensions(file);
    loadOff_Pixels(file);
    
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

void Formater_BMP::storeByte_1(std::ostream& file, unsigned char c) {
    file << c;
}

void Formater_BMP::storeBytes(std::ostream& file, int num, int n) {
    
    for(int i=0; i<n; i++) {
        char c = num & 0xff;
        file.write(&c, 1);
        num >>= 8;
    }
}



#include <iostream>
#include <algorithm>

#include "formater_bmp.h"

const unsigned int OFFSET_NUMBER_OF_BITS_PER_PIXEL = 0x1C; 
const unsigned int OFFSET_WIDTH = 0x12;
const unsigned int OFFSET_HEIGHT =  0x16;
const unsigned int OFFSET_SIZE_PADDING = 0x22;
const unsigned int OFFSET_PIXELS = 0xA;

std::vector<int> Formater_BMP::load() {
    loadInit();

    std::ifstream file(path, std::ios::binary);
    std::vector <int> matrix(dimension.second*dimension.first, 0);

    file.seekg(offset_for_pixels, std::ios::beg);
    int alfa = (hasAlfa ? 4 : 3);
    int x=0;
    for(int i=0; i<dimension.second; i++) {
        for(int j=0; j<dimension.first; j++){
            int newElement = readBytes(file, alfa) | (hasAlfa ? 0 :0xff000000); // TODO: Load check for anomalities
            matrix[i * dimension.first + j] = newElement;
        }
        readBytes(file, dimension.first * alfa % 4);
    }

    file.close();
    
    return matrix;
}

void Formater_BMP::store(std::vector<int> matrix, std::pair<int, int> dimensions) {
    std::ofstream file(path, std::ios::binary | std::ios::out);

    dimension = dimensions;
    hasAlfa = false;
    BMP_Header header = configureHeader();
    storeHeader(file, header);

    int alfaSize = (hasAlfa ? 4 : 3);

    for(int i=0; i<dimension.second; i++){
        int j;
        for(j=0; j<dimension.first; j++){
            storeBytes(file, matrix[i*dimension.first + j], alfaSize);
        }
        for(int k=0; k < dimension.first*alfaSize % 4; k++)
            storeByte_1(file, 0);
    }
    
    file.close();
}

Formater_BMP::Formater_BMP(std::string path_) : Formater(path_) {
}

void Formater_BMP::loadInit() {
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

int Formater_BMP::invertNumber(int number, int size) const {
    int result = 0;
    int mask = 0xff;
    for(int i=0; i<size; i++) {
        result += number & mask;
        number >>= 8;
        result <<= 8;
    }
    return result;
}

BMP_Header Formater_BMP::configureHeader() const {
    BMP_Header header;
    header.image_width = dimension.first;
    header.image_height = dimension.second;
    header.size_bmp = dimension.first * dimension.second * (hasAlfa ? 4 : 3);
    header.size_bmp_file = dimension.first * dimension.second * (hasAlfa ? 4 : 3) + sizeof(BMP_Header)-2;
    header.bits_per_pixel = (hasAlfa ? 32 : 24);
    return header;
}

void Formater_BMP::storeHeader(std::ofstream& file, const BMP_Header& header) const {
    file.write((char*)&header.ID_field, sizeof(header.ID_field));
    file.write((char*)&header.size_bmp_file, sizeof(header.size_bmp_file));
    file.write((char*)&header.unused_0, sizeof(header.unused_0));
    file.write((char*)&header.unused_1, sizeof(header.unused_1));
    file.write((char*)&header.offset_pixels, sizeof(header.offset_pixels));
    file.write((char*)&header.num_of_bytes_dib, sizeof(header.num_of_bytes_dib));
    file.write((char*)&header.image_width, sizeof(header.image_width));
    file.write((char*)&header.image_height, sizeof(header.image_height));
    file.write((char*)&header.color, sizeof(header.color));
    file.write((char*)&header.bits_per_pixel, sizeof(header.bits_per_pixel));
    file.write((char*)&header.commpression, sizeof(header.commpression));
    file.write((char*)&header.size_bmp, sizeof(header.size_bmp));
    file.write((char*)&header.pixels_per_meter_1, sizeof(header.pixels_per_meter_1));
    file.write((char*)&header.pixels_per_meter_2, sizeof(header.pixels_per_meter_2));
    file.write((char*)&header.unused_dib_1, sizeof(header.unused_dib_1));
    file.write((char*)&header.unused_dib_2, sizeof(header.unused_dib_2));
}
#ifndef __FORMATER_BMP_H__
#define __FORMATER_BMP_H__

#include <fstream>

#include "formater.h"

struct BMP_Header {
    short ID_field = 0x4d42;
    uint32_t size_bmp_file;
    uint16_t unused_0 = 0;
    uint16_t unused_1 = 0;
    uint32_t offset_pixels = 0x36;

    uint32_t num_of_bytes_dib = 0x28;
    uint32_t image_width;
    uint32_t image_height;
    uint16_t color = 0x01;
    uint16_t bits_per_pixel = 32;
    uint32_t commpression = 0;
    uint32_t size_bmp;
    uint32_t pixels_per_meter_1 = 0x0B13;
    uint32_t pixels_per_meter_2 = 0x0B13;
    uint32_t unused_dib_1=0;
    uint32_t unused_dib_2=0;
};

class Formater_BMP : public Formater {
public:
    Formater_BMP(std::string path_);
    std::vector<int> load();
    void store(std::vector<int>, std::pair<int, int> dimensions) override;
    std::pair<int, int> Dimensions() const override { return dimension; }

    int invertNumber(int number, int size) const;
private:
    std::pair<unsigned int, unsigned int> dimension;

    void loadHeader(std::ifstream& file);

    bool hasAlfa;
    unsigned int size_with_padding;
    unsigned int size_with_header;
    unsigned int offset_for_pixels;

    void loadInit();
    void loadAlfa(std::ifstream& file);
    void loadDimensions(std::ifstream& file);
    void loadOff_Pixels(std::ifstream& file);

    int readByte_1(std::ifstream& file);
    int readBytes(std::ifstream& file, int n);

    void storeByte_1(std::ostream& file, unsigned char c);
    void storeBytes(std::ostream& file, int i, int n);

    BMP_Header configureHeader() const;
    void storeHeader(std::ofstream& file, const BMP_Header&) const;
};

#endif // __FORMATER_BMP_H__

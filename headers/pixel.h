#ifndef _pixel_h_
#define _pixel_h_

#include <functional>
#include <iostream>
#include "operation.h"

class Pixel {
public:
    static const int MAX_VALUE = 255;
    static const int MIN_VALUE = 0;

    Pixel(int red_, int green_, int blue_, int alfa_=255)
    : red(red_), green(green_), blue(blue_), alfa(alfa_) {};
    Pixel(int ARGB = 0xff000000) : alfa((ARGB & 0xff000000) >> 24), red((ARGB & 0x00ff0000) >> 16), green((ARGB & 0x0000ff00) >> 8), blue((ARGB & 0x000000ff) >> 0){}
    int Red() const {return red;}
    int Blue() const {return blue;}
    int Green() const {return green;}
    int Alfa() const {return alfa;}

    void setRed(int newVal) { red = setColor(newVal);}
    void setGreen(int newVal) { green = setColor(newVal); }
    void setBlue(int newVal) { blue = setColor(newVal); }
    void setAlfa(int newVal) { alfa = setColor(newVal); }

    Pixel getBlackWhite() const;
    Pixel getGray() const;
    operator int();
    friend Pixel operator+(Pixel p1, Pixel p2);
    friend int combineAlfa(int aA, int aB) { return aA + (aB * (255 - aA) / 255); }
private:
    int red;
    int blue;
    int green;
    int alfa;
    static const int MAX_COLOR_VALUE = 255;
    static const int MIN_COLOR_VALUE = 0;
    int setColor(int newVal);

    #ifdef _TEST_
        friend std::ostream& operator<< (std::ostream& os, Pixel& l){
            os << "(" << l.red << ", " << l.green << ", " << l.blue << ")";
            return os;
        }
    #endif
};

#endif
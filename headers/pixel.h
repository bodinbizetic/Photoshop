#ifndef _pixel_h_
#define _pixel_h_

#include <functional>
#include <iostream>

class Pixel {
public:
    explicit Pixel(int red_=0, int green_=0, int blue_=0, int alfa_=255)
    : red(red_), green(green_), blue(blue_), alfa(alfa_) {};

    int Red() const {return red;}
    int Blue() const {return blue;}
    int Green() const {return green;}
    int Alfa() const {return alfa;}

    void setRed(int newVal) { red = setColor(newVal);}
    void setGreen(int newVal) { green = setColor(newVal); }
    void setBlue(int newVal) { blue = setColor(newVal); }
    void setAlfa(int newVal) { alfa = setColor(newVal); }
    void setRed(std::function<int(int x)> fun) { red = setColor(fun(red));}
    void setGreen(std::function<int(int x)> fun) { green = setColor(fun(green)); }
    void setBlue(std::function<int(int x)> fun) { blue = setColor(fun(blue)); }
    void setAlfa(std::function<int(int x)> fun) { alfa = setColor(fun(alfa)); }
    void setRGB(std::function<int(int x)> fun);
    void setRGBA(std::function<int(int x)> fun);

    Pixel getBlackWhite() const;
    Pixel getGray() const;
    operator int(){};
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
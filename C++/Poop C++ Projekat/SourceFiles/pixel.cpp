#include <iostream>
#include <functional>
#include "pixel.h"

Pixel Pixel::getBlackWhite() const {
    int val = (red + green + blue) / 3;
    val = (val > 127 ? 255 : 0);
    return Pixel(val, val, val, alfa);
}

Pixel Pixel::getGray() const {
    int val = (red + green + blue) / 3;
    return Pixel(val, val, val, alfa);
}

Pixel::operator int() {
    return (red << 16) + (green << 8) + (blue << 0) + (alfa << 24);
}

Pixel operator+(Pixel p2, Pixel p1) {
    int alfa = p1.Alfa() + (p2.Alfa() * (255 - p1.Alfa()) / 255);
    if (alfa == 0) alfa = 256;
    std::function<int(int, int, int, int)> calc = [alfa](int rA, int aA, int rB, int aB) -> int {
        return (rA * aA / alfa) + (rB * (255 - aA) * aB / (alfa * 255));
    };

    int red = calc(p1.Red(), p1.Alfa(), p2.Red(), p2.Alfa());
    int green = calc(p1.Green(), p1.Alfa(), p2.Green(), p2.Alfa());
    int blue = calc(p1.Blue(), p1.Alfa(), p2.Blue(), p2.Alfa());

    return Pixel(red, green, blue, alfa);
}


int Pixel::setColor(int newVal){
    if(newVal > MAX_COLOR_VALUE) newVal = MAX_COLOR_VALUE;
    if(newVal < MIN_COLOR_VALUE) newVal = MIN_COLOR_VALUE;
    return newVal;
}

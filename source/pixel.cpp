#include "pixel.h"
#include <iostream>

void Pixel::setRGBA(std::function<int(int x)> fun){
    setRGB(fun);
    setAlfa(fun);
}


void Pixel::setRGB(std::function<int(int x)> fun){
    setRed(fun);
    setGreen(fun);
    setBlue(fun);
}


int Pixel::setColor(int newVal){
    if(newVal > MAX_COLOR_VALUE) newVal = MAX_COLOR_VALUE;
    if(newVal < MIN_COLOR_VALUE) newVal = MIN_COLOR_VALUE;
    return newVal;
}

#include <string>
#include <stdlib.h>
#include <iostream>
#include <windows.h>

#include "pixel.h"
#include "menu.h"

bool isInteger(std::string s) {
    for(auto c : s)
        if(!isdigit(c))
            return false;
    return true;
}

int inputIntMsg(std::string x) {
    std::string command;
    std::cout << "Insert position of layer to be toggled:\n>>> ";
    std::cin >> command;
    if(!isInteger(command))
        throw WrongCommand();
    
    return atoi(command.c_str());
}

void consoleDraw(std::vector<int> vvi, std::pair<int, int> dim) {
    HWND myconsole = GetConsoleWindow();
    HDC mydc = GetDC(myconsole);
    
    for(int i=0; i<dim.second; i++)
        for(int j=0; j<dim.first; j++)
        {   
            Pixel p = vvi[i * dim.first + j];
            COLORREF COLOR= RGB(p.Red(), p.Green(), p.Blue()); 
            SetPixel(mydc,j,dim.second - 1 - i,COLOR);
        }

    ReleaseDC(myconsole, mydc);
}


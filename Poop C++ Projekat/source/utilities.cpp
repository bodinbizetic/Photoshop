#include <string>
#include <stdlib.h>
#include <iostream>
#include <windows.h>
#include <fstream>

#include "pixel.h"
#include "menu.h"

bool isInteger(std::string s) {
    if(s[0] == '-' || s[0] == '+')
        s = s.substr(1, s.size()-1);
    for(auto c : s)
        if(!isdigit(c))
            return false;
    return true;
}

int inputIntMsg(std::string x) {
    std::string command;
    std::cout << x;
    std::getline(std::cin, command);
    if(!isInteger(command))
        throw WrongCommand();
    
    return atoi(command.c_str());
}

void consoleDraw(std::vector<int> vvi, std::pair<int, int> dim) {
    system("cls");
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

bool fileExists(std::string path) {
    std::ifstream file(path);
    if(file.fail()) {
        file.close();
        return false;
    }
    file.close();
    return true;
}

bool copyPath(std::string src, std::string dst) {
    std::ifstream input(src, std::ios::binary);
    std::ofstream output(dst, std::ios::binary);
    if(input.fail() || output.fail()){
        std::cout << "Failed";
    }
    char c;
    while(!input.eof()){
        input.read(&c, 1);
        output.write(&c, 1);
    }

    output.close();
    input.close();
    return input && output;
}
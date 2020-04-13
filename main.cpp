#include <stdio.h>
#include <iostream>
#include <windows.h>
#define _TEST_
#include "menu.h"
#include "layer.h"
#include "selection.h"
#include "simple_operation.h"
#include "complex_operation.h"
#include "formater_bmp.h"
#include "menu_main.h"

using std::cout;
using std::endl;

int main(int argc, char const *argv[])
{
    
    Menu &m = *new Menu_Main();
    m.start();
    // Formater_BMP f1("bmp_24.bmp");
    // std::vector<int> vvi = f1.load();
    // cout << vvi.size() << endl;
    // f1.store(vvi);
    // // for(std::vector<int> vi : vvi) {
    // //     for(int i : vi){
    // //         Pixel p(i);
    // //         cout << p << " ";
    // //     }
    // //     cout << endl;
    // // }

    // HWND myconsole = GetConsoleWindow();
    // //Get a handle to device context
    // HDC mydc = GetDC(myconsole);

    // int pixel =0;

    // //Choose any color
    

    // //Draw pixels
    // std::pair<int, int> temp = f1.getDimension();
    // for(int i=0; i<temp.second; i++)
    //     for(int j=0; j<temp.first; j++)
    //     {   
    //         Pixel p = vvi[i * temp.first + j];
    //         COLORREF COLOR= RGB(p.Red(), p.Green(), p.Blue()); 
    //         SetPixel(mydc,j,temp.second - 1 - i,COLOR);
    //     }

    // ReleaseDC(myconsole, mydc);
    // // std::cin.ignore();
    // HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // SetConsoleCursorPosition(hConsole, {0, -1});
    // int x=2;
    // while(x != 0) {
    //     std::cout << "Input: ";
    //     std::cin >> x;
    // }
    
    return 0;
}
#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <fstream>
#include <iostream>
#define _TEST_
#include "formater_pam.h"
#include "menu_main.h"
#include "utilities.h"

using std::cout;
using std::endl;

int main(int argc, char const *argv[])
{
    Menu &m = *new Menu_Main();
    m.start();
    delete &m;
    /*Formater& g = *Formater::getFormater("C:\\Users\\Dinbo\\Desktop\\temp\\sample_640426.pam");
    Formater& f = *Formater::getFormater("C:\\Users\\Dinbo\\Desktop\\temp\\copy2.bmp");*/
    // f.load();
    /*auto p = f.load();
    auto dim = f.Dimensions();
    consoleDraw(p, dim);
    g.store(p, dim);*/
    
    
    // system("pause");
    return 0;
}
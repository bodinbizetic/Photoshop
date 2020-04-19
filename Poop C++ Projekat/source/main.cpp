#include <stdio.h>
#include <iostream>
#include <windows.h>
#define _TEST_
#include "menu.h"
#include "image.h"
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

    // Formater_BMP b("resource/leopard.bmp");

    // b.store(b.load(), b.Dimensions());
    
    // system("pause");
    return 0;
}
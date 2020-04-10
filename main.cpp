#include <iostream>
#define _TEST_
#include "layer.h"

using std::cout;
using std::endl;

int main(int argc, char const *argv[])
{
    Layer l1(10, 5);
    cout << l1;
    cout << endl << endl;
    l1.fitLayer({15, 10});
    cout << l1;
    
    return 0;
}
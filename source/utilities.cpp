#include <string>
#include <stdlib.h>

bool isInteger(std::string s) {
    for(auto c : s)
        if(!isdigit(c))
            return false;
    return true;
}

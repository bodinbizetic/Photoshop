#ifndef __UTILITIES_H__
#define __UTILITIES_H__

#include <string>

#define CHANGE_DIR "chdir "
#define MAKE_DIR "mkdir "
#define OS_SEP "\\"
#define DELETE_FILE "del "

bool isInteger(std::string);
int inputIntMsg(std::string x);
void consoleDraw(std::vector<int>, std::pair<int, int>);
bool fileExists(std::string path);
bool copyPath(std::string src, std::string dst);

#endif // __UTILITIES_H__

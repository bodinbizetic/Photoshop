#ifndef __MENU_H__
#define __MENU_H__

#include <string>

class WrongCommand {

};

class Menu {
public:
    Menu() {};
    ~Menu() {};
    void start();
private:
    void loopMenu();
    virtual void showMenu() {};
    virtual void functionCall(std::string x) {};

};

#endif // __MENU_H__

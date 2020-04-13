#ifndef __MENU_H__
#define __MENU_H__

#include <string>
#include <vector>

class Terminate {

};

class WrongCommand {

};

class Menu {
public:
    Menu(std::vector<std::string> commands_) : commands(commands_) {};
    ~Menu() {};
    void start();
protected:
    void setClean() { clean = false; }
    bool running = true;
    const std::vector<std::string> commands;
private:
    bool clean = true;
    void loopMenu();
    void showMenu();
    virtual void functionCall(std::string x) = 0;

};

#endif // __MENU_H__

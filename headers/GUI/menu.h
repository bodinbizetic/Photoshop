#ifndef __MENU_H__
#define __MENU_H__

#include <string>
#include <vector>
#include <exception>

class Terminate : public std::exception {

};

class WrongCommand : public std::exception {
    const char* what() const noexcept override {
        return "The command you entered is not valid";
    }
};

class Menu {
public:
    Menu(std::vector<std::string> commands_) : commands(commands_) {};
    ~Menu() {};
    void start();
protected:
    void setClean() { clean = false; }
    void addHeader(std::string s) { header.push_back(s); }
    bool running = true;
    const std::vector<std::string> commands;
private:
    std::vector<std::string> header;
    bool clean = true;
    void loopMenu();
    void showMenu();
    void printHeader();
    virtual void functionCall(std::string x) = 0;

};

#endif // __MENU_H__

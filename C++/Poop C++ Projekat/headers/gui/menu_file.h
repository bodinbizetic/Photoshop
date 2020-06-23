#ifndef _MENU_FILE_H_
#define _MENU_FILE_H_

#include "image.h"
#include "menu.h"

class Menu_File : public Menu {
public:
	Menu_File(Image& project_) : project(project_), Menu({
		"Return",
		"Save all",
		"Export"
		}) {}
private:
	Image& project;
	void functionCall(std::string x);
};

#endif // !_MENU_FILE_H_


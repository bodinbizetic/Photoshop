#include <memory>
#include "menu_export.h"
#include "utilities.h"
#include "formater.h"

void Menu_Export::exportImage(std::string extension) {
	const std::string image_name = "MyImage";
	std::string export_path = image_name + extension;
	std::shared_ptr<Formater> formater(Formater::getFormater(export_path));
	formater->store(project.getFinalResult(), project.Dimensions());
}

void Menu_Export::functionCall(std::string x) {
    if (x == "0")
        running = false;
    else if (x == "1") {
        exportImage(".bmp");
    }
    else if (x == "2") {
        exportImage(".pam");
    }
    else {
        throw WrongCommand();
    }
}


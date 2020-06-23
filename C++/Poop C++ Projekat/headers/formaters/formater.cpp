#include "formater.h"
#include "formater_bmp.h";
#include "formater_pam.h"

Formater* Formater::getFormater(std::string path) {
	std::string extension = path.substr(path.find_last_of(".") + 1);
	if (extension == "bmp")
		return new Formater_BMP(path);
	if (extension == "pam")
		return new Formater_PAM(path);
	throw FileNotSupported();
}

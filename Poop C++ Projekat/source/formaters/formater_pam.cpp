#include <iostream>
#include <fstream>
#include <regex>
#include "formater_pam.h"

std::vector<int> Formater_PAM::load() {
	std::ifstream file(path);
	if (file.fail())
		throw FilePermissionDenied();
	loadHeader(file);
	file.close();
}

PAM_Header Formater_PAM::loadHeader(std::ifstream& file) {
	std::string line;
	int num = 0;
	while (std::getline(file, line)) {
		if (num++ > 10000)
			throw CorruptedPamFile();
		std::regex p7("[^#]*(P7)");
		std::cmatch cm;
		std::regex_match(line.c_str(), cm, p7);
		if (cm[1] == "P7")
			continue;

		std::regex end("[^#]*(ENDHDR)");
		std::regex_match(line.c_str(), cm, end);
		if (cm[1] == "ENDHDR")
			break;

		std::regex r("([^\\s#]+)\\s([^\\s#]+).*");
		std::regex_match(line.c_str(), cm, r);
		if (pam_attributes.find(cm[1]) == pam_attributes.end())
			throw CorruptedPamFile();
		pam_attributes[cm[1]] = cm[2].str();
	}
	PAM_Header header;
	header.tupltype = pam_attributes["TUPLTYPE"];
	header.maxval   = atoi(pam_attributes["MAXVAL"].c_str());
	header.depth    = atoi(pam_attributes["DEPTH"].c_str());
	header.width	= atoi(pam_attributes["WIDTH"].c_str());
	header.height	= atoi(pam_attributes["HEIGHT"].c_str());
	return header;
}

void Formater_PAM::initAttributes() {
	pam_attributes["HEIGHT"] = "1";
	pam_attributes["WIDTH"] = "1";
	pam_attributes["DEPTH"] = "1";
	pam_attributes["MAXVAL"] = "1";
	pam_attributes["TUPLTYPE"] = "RGB";
}

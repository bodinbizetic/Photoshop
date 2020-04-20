#include <iostream>
#include <fstream>
#include <regex>
#include "formater_pam.h"

Formater_PAM::Formater_PAM(std::string path) : Formater(path) {
	initAttributes();
}

std::vector<int> Formater_PAM::load() {
	std::ifstream file(path, std::ios::binary);
	if (file.fail())
		throw FilePermissionDenied();
	loadHeader(file);
	std::vector<int> vi = readMatrix(file);
	file.close();
	return vi;
}

void Formater_PAM::store(std::vector<int> matrix, std::pair<int, int> dimensions) {
	std::ofstream output(path, std::ios::binary);
	header = PAM_Header();
	header.width = dimensions.first;
	header.height = dimensions.second;
	storeHeader(output);
	flipImage(matrix);
	storeMatrix(output, matrix);

	output.close();
}

std::pair<int, int> Formater_PAM::Dimensions() const {
	
	return { header.width, header.height};
}

void Formater_PAM::loadHeader(std::ifstream& file) {
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
	
	configureHeader();
}

void Formater_PAM::configureHeader() {

	std::regex p7("[^#]*(ALPHA)");
	std::cmatch cm;
	std::regex_match(pam_attributes["TUPLTYPE"].c_str(), cm, p7);
	if (cm[1] == "ALPHA")
		header.hasAlfa = true;
	else
		header.hasAlfa = false;


	header.tupltype = pam_attributes["TUPLTYPE"];
	header.maxval = atoi(pam_attributes["MAXVAL"].c_str());
	header.depth = atoi(pam_attributes["DEPTH"].c_str());
	header.width = atoi(pam_attributes["WIDTH"].c_str());
	header.height = atoi(pam_attributes["HEIGHT"].c_str());

}

std::vector<int> Formater_PAM::readMatrix(std::ifstream& file) {
	std::vector<int> pixels;
	for (int i = 0; i < header.width; i++) {
		for (int j = 0; j < header.height; j++) {
			int in = 0;
			
			file.read((char*)&in, (header.hasAlfa ? 4 : 3));
			if (!header.hasAlfa) in |= 0xff000000;
			int blue = in & 0x00ff0000;
			int red = in & 0x000000ff;
			blue >>= 16;
			red <<= 16;
			std::swap(blue, red);
			in = (in & 0xff00ff00) + blue + red;
			pixels.push_back(in);
		}
	}
	flipImage(pixels);
	return pixels;
}

void Formater_PAM::flipImage(std::vector<int>& image) {
	for (int i = 0; i < header.height / 2; i++) {
		for (int j = 0; j < header.width; j++)
			std::swap(image[i * header.width + j], image[(header.height - i - 1) * header.width + j]);
	}
}

void Formater_PAM::initAttributes() {
	pam_attributes["HEIGHT"] = "1";
	pam_attributes["WIDTH"] = "1";
	pam_attributes["DEPTH"] = "1";
	pam_attributes["MAXVAL"] = "1";
	pam_attributes["TUPLTYPE"] = "RGB";
}

void Formater_PAM::storeHeader(std::ofstream& output) {
	output << "P7" << "\n";
	output << "WIDTH " << header.width << "\n";
	output << "HEIGHT " << header.height << "\n";
	output << "DEPTH " << header.depth << "\n";
	output << "MAXVAL " << header.maxval << "\n";
	output << "TUPLTYPE " << header.tupltype << "\n";
	output << "ENDHDR" << "\n";
}

void Formater_PAM::storeMatrix(std::ofstream& output, std::vector<int> matrix) {
	for (int out : matrix) {
		int blue = out & 0x00ff0000;
		int red = out & 0x000000ff;
		blue >>= 16;
		red <<= 16;
		out = (out & 0xff00ff00) + blue + red;
		output.write((char*)&out, (header.hasAlfa ? 4 : 3));
	}
}

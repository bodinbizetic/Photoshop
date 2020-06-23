#ifndef _FORMATER_PAM_H_
#define _FORMATER_PAM_H_

#include <map>

#include "formater.h"

class CorruptedPamFile : public std::exception {
	const char* what() const noexcept override {
		return "File that you are trying to open was corrupted";
	}
};

struct PAM_Header {
	int width;
	int height;
	int depth=4;
	int maxval=255;
	std::string tupltype="RGB_ALPHA";
	bool hasAlfa=true;
};

class Formater_PAM : public Formater {
public:
	Formater_PAM(std::string path);
	virtual std::vector<int> load();
	virtual void store(std::vector<int>, std::pair<int, int> dimensions);
	virtual std::pair<int, int> Dimensions() const;
protected:
	std::map<std::string, std::string> pam_attributes;
	PAM_Header header;
private:
	void loadHeader(std::ifstream& file);
	void configureHeader();

	std::vector<int> readMatrix(std::ifstream& file);
	void flipImage(std::vector<int>& image);
	void initAttributes();

	void storeHeader(std::ofstream& output);
	void storeMatrix(std::ofstream& output, std::vector<int> matrix);
};

#endif // !_FORMATER_PAM_H_

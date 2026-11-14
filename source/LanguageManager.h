#pragma once

#include <iostream>
#include <fstream>
#include <vector>

class LanguageManager
{
private:
	std::vector<char*> m_languages;
	std::vector<std::vector<char*>> m_labels;

	int m_activeLanguage = 0;

public:
	LanguageManager(const std::string& fileName);
	~LanguageManager();
	
	void clearConfiguration();
	void loadConfiguration(const std::string& fileName);

	int getActiveLanguage() const;
	char* getLabel(int language, int label) const;

	void changeLanguage(int language);
};
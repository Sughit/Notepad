
#include "LanguageManager.h"
#include <sstream>
#include <cstring>

LanguageManager::LanguageManager(const std::string& fileName)
{
    loadConfiguration(fileName);
}

LanguageManager::~LanguageManager()
{
    clearConfiguration();
}

void LanguageManager::clearConfiguration()
{
    for (char* language : m_languages)
        delete[] language;

    for (auto& labels : m_labels)
        for (char* label : labels)
            delete[] label;

    m_languages.clear();
    m_labels.clear();
}

void LanguageManager::loadConfiguration(const std::string& fileName)
{
    std::ifstream fin(fileName);

    if (!fin)
    {
        std::cerr << "Nu putem gasi fisierul: " << fileName << "\n";
        return;
    }

    clearConfiguration();

    std::string line;
    size_t lineNumber = 0;

    while (std::getline(fin, line))
    {
        lineNumber++;

        std::istringstream input(line);
        std::string type;

        if (!(input >> type)) continue;
        if (type[0] == '#') continue;

        if (type == "Language")
        {
            std::string language;

            if (!(input >> language))
            {
                std::cerr << "Eroare la linia: " << lineNumber << "\n";
                continue;
            }

            char* text = new char[language.size() + 1];
            strcpy_s(text, language.size() + 1, language.c_str());

            m_languages.push_back(text);
            m_labels.emplace_back();
        }
        else
        {
            if (m_labels.empty())
            {
                std::cerr << "Nu exista o limba definita\n";
                continue;
            }

            do
            {
                char* text = new char[type.size() + 1];
                strcpy_s(text, type.size() + 1, type.c_str());

                m_labels.back().push_back(text);

            } while (input >> type);
        }
    }
}

int LanguageManager::getActiveLanguage() const
{
    return m_activeLanguage;
}

char* LanguageManager::getLabel(int language, int label) const
{
    return m_labels.at(language).at(label);
}

void LanguageManager::changeLanguage(int language)
{
    if (language < 0 || language >= m_languages.size())
    {
        std::cerr << "Indice de limbaj invalid\n";
        return;
    }

    m_activeLanguage = language;
}

#include "LanguageManager.h"
#include <fstream>
#include <sstream>
#include <utility>
#include <iostream>

namespace
{
    const std::vector<std::string> DefaultLabels = {"File", "Edit", "View"};
}

LanguageManager::LanguageManager(const std::string& configPath)
{
    load(configPath);
}

bool LanguageManager::load(const std::string& configPath)
{
    m_languages.clear();
    std::ifstream file(configPath);
    std::vector<Language> parsed;
    std::string line;

    if (!file)
    {
        std::cerr << "Eroare la incarcarea fisierului: " << configPath << "\n";
        return false;
    }

    while (std::getline(file, line))
    {
        std::istringstream input(line);
        std::string first;
        if (!(input >> first) || first.front() == '#')
            continue;

        if (first == "Language")
        {
            std::string name;
            std::getline(input >> std::ws, name);
            if (!name.empty())
                parsed.push_back({ name, {} });
        }
        else if (!parsed.empty())
        {
            parsed.back().labels.push_back(first);
            std::string word;
            while (input >> word)
            {
                parsed.back().labels.push_back(word);
            }
        }
    }

    for (auto& language : parsed)
    {
        if (language.labels.size() >= DefaultLabels.size())
        {
            m_languages.push_back(std::move(language));
        }
    }
    if (m_languages.empty())
    {
        m_languages.push_back({"English", DefaultLabels});
    }

    m_activeIndex = 0;
    return file.is_open() && !parsed.empty();
}

int LanguageManager::count() const
{
    return static_cast<int>(m_languages.size());
}

int LanguageManager::activeIndex() const
{
    return m_activeIndex;
}

bool LanguageManager::select(int index)
{
    if (index < 0 || index >= count()) { return false; }
    m_activeIndex = index;

    return true;
}

const std::string& LanguageManager::languageName(int index) const
{
    return m_languages.at(index).name;
}

const std::string& LanguageManager::label(int index) const
{
    return m_languages.at(m_activeIndex).labels.at(index);
}

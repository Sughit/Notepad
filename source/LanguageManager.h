#pragma once
#include <string>
#include <vector>

class LanguageManager
{
private:
    struct Language
    {
        std::string name;
        std::vector<std::string> labels;
    };

    std::vector<Language> m_languages;
    int m_activeIndex = 0;

public:
    explicit LanguageManager(const std::string& configPath);

    bool load(const std::string& configPath);
    int count() const;
    int activeIndex() const;
    bool select(int index);

    const std::string& languageName(int index) const;
    const std::string& label(int index) const;
};
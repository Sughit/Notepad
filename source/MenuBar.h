#pragma once
#include "Geometry.h"
#include "SubMenu.h"
#include <array>
#include <string>

class LanguageManager;
class TextRenderer;

class MenuBar
{
private:
    static constexpr int ButtonCount = 3;
    static constexpr int ViewButton = 2;
    std::array<Rect, ButtonCount> m_buttonBounds = {};
    std::array<std::string, ButtonCount> m_labels = {};
    SubMenu m_languageMenu;

public:
    enum class ClickResult { Outside, Consumed };

    void refresh(const LanguageManager& language, TextRenderer& text);
    ClickResult click(Point point, LanguageManager& language, TextRenderer& text);
    void drawBackground(int windowWidth, TextRenderer& text) const;
    void drawText(TextRenderer& text) const;
};

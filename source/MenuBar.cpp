#include "MenuBar.h"
#include "AppStyle.h"
#include "LanguageManager.h"
#include "TextRenderer.h"
#include <vector>

void MenuBar::refresh(const LanguageManager& language, TextRenderer& text)
{
    int x = AppStyle::MenuLeftPadding;
    for (int index = 0; index < ButtonCount; index++)
    {
        m_labels[index] = language.label(index);
        const int width = text.width(m_labels[index]) + 2 * AppStyle::MenuButtonPadding;
        m_buttonBounds[index] = {x, 0, width, AppStyle::MenuHeight};
        x += width + AppStyle::MenuButtonGap;
    }

    std::vector<std::string> names;
    for (int index = 0; index < language.count(); index++)
    {
        names.push_back(language.languageName(index));
    }

    m_languageMenu.setItems(names);
    m_languageMenu.setSelected(language.activeIndex());

    if (m_languageMenu.isOpen())
    {
        const auto& view = m_buttonBounds[ViewButton];
        m_languageMenu.open(view.x, AppStyle::MenuHeight, text);
    }
}

MenuBar::ClickResult MenuBar::click(Point point, LanguageManager& language, TextRenderer& text)
{
    if (m_languageMenu.contains(point))
    {
        const int selected = m_languageMenu.itemAt(point);
        if (selected >= 0)
        {
            language.select(selected);
        }

        m_languageMenu.close();
        return ClickResult::Consumed;
    }

    if (point.y >= 0 && point.y < AppStyle::MenuHeight)
    {
        const bool viewClicked = m_buttonBounds[ViewButton].contains(point);
        if (viewClicked && !m_languageMenu.isOpen())
        {
            const auto& view = m_buttonBounds[ViewButton];
            m_languageMenu.open(view.x, AppStyle::MenuHeight, text);
        }
        else
        {
            m_languageMenu.close();
        }
        return ClickResult::Consumed;
    }

    m_languageMenu.close();
    return ClickResult::Outside;
}

void MenuBar::drawBackground(int windowWidth, TextRenderer& text) const
{
    text.fillRect(0, 0, windowWidth, AppStyle::MenuHeight, AppStyle::MenuBackground);
    if (m_languageMenu.isOpen())
    {
        const auto& view = m_buttonBounds[ViewButton];
        text.fillRect(view.x, view.y, view.width, view.height, AppStyle::EditorBackground);
    }
    text.drawLine(0, AppStyle::MenuHeight, windowWidth, AppStyle::MenuHeight, AppStyle::BorderColor);
    m_languageMenu.drawBackground(text);
}

void MenuBar::drawText(TextRenderer& text) const
{
    for (int index = 0; index < ButtonCount; index++)
    {
        const Rect& bounds = m_buttonBounds[index];
        text.draw(bounds.x + AppStyle::MenuButtonPadding, (bounds.height - text.height()) / 2, m_labels[index]);
    }
    m_languageMenu.drawText(text);
}

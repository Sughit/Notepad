#include "SubMenu.h"
#include "AppStyle.h"
#include "TextRenderer.h"
#include <algorithm>
#include <utility>

void SubMenu::setItems(std::vector<std::string> items)
{
    m_items = std::move(items);
}

void SubMenu::setSelected(int index)
{
    m_selected = index;
}

void SubMenu::open(int x, int y, TextRenderer& text)
{
    int width = AppStyle::SubMenuMinWidth;
    for (const auto& item : m_items)
    {
        width = (std::max)(width, text.width(item) + 2 * AppStyle::SubMenuPadding + AppStyle::SubMenuCheckWidth);
    }
    m_bounds = {x, y, width, static_cast<int>(m_items.size()) * AppStyle::SubMenuRowHeight};
    m_open = true;
}

void SubMenu::close()
{
    m_open = false;
}

bool SubMenu::isOpen() const
{
    return m_open;
}

bool SubMenu::contains(Point point) const
{
    return m_open && m_bounds.contains(point);
}

int SubMenu::itemAt(Point point) const
{
    if (!contains(point)) { return -1; }
    return (point.y - m_bounds.y) / AppStyle::SubMenuRowHeight;
}

void SubMenu::drawBackground(TextRenderer& text) const
{
    if (!m_open) { return; }

    text.fillRect(m_bounds.x, m_bounds.y, m_bounds.width, m_bounds.height, AppStyle::MenuBackground);
    if (m_selected >= 0 && m_selected < static_cast<int>(m_items.size()))
    {
        const int y = m_bounds.y + m_selected * AppStyle::SubMenuRowHeight;
        text.fillRect(m_bounds.x + 1, y + 1, m_bounds.width - 2, AppStyle::SubMenuRowHeight - 2, 
                      AppStyle::SubMenuSelectedBackground);
    }
    text.frameRect(m_bounds.x, m_bounds.y, m_bounds.width, m_bounds.height, AppStyle::BorderColor);
}

void SubMenu::drawText(TextRenderer& text) const
{
    if (!m_open) { return; }

    for (int index = 0; index < static_cast<int>(m_items.size()); index++)
    {
        const int y = m_bounds.y + index * AppStyle::SubMenuRowHeight + (AppStyle::SubMenuRowHeight - text.height()) / 2;
        if (index == m_selected)
        {
            text.draw(m_bounds.x + AppStyle::SubMenuPadding, y, "*");
        }

        text.draw(m_bounds.x + AppStyle::SubMenuPadding + AppStyle::SubMenuCheckWidth, y, m_items[index]);
    }
}

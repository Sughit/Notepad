#pragma once
#include "Geometry.h"
#include <string>
#include <vector>

class TextRenderer;

class SubMenu
{
private:
    std::vector<std::string> m_items;
    Rect m_bounds;
    int m_selected = -1;
    bool m_open = false;

public:
    void setItems(std::vector<std::string> items);
    void setSelected(int index);
    void open(int x, int y, TextRenderer& text);
    void close();
    bool isOpen() const;
    bool contains(Point point) const;
    int itemAt(Point point) const; // -1 daca este in afara

    void drawBackground(TextRenderer& text) const;
    void drawText(TextRenderer& text) const;
};

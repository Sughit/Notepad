#include "TextDocument.h"

void TextDocument::insertChar(int row, int col, char character)
{
    m_lines.at(row).insert(col, 1, character);
}

void TextDocument::deleteRange(int row, int first, int last)
{
    m_lines.at(row).erase(first, last - first);
}

void TextDocument::insertLine(int row, int col)
{
    std::string rest = m_lines.at(row).substr(col);
    m_lines.at(row).erase(col);
    m_lines.insert(m_lines.begin() + row + 1, rest);
}

void TextDocument::mergeLines(int row)
{
    if (row <= 0 || row >= getLines())
        return;
    m_lines.at(row - 1) += m_lines.at(row);
    m_lines.erase(m_lines.begin() + row);
}

void TextDocument::clear()
{
    m_lines.assign(1, "");
}

const std::string& TextDocument::getLine(int row) const
{
    return m_lines.at(row);
}

int TextDocument::getLines() const
{
    return static_cast<int>(m_lines.size());
}

int TextDocument::getLineLength(int row) const
{
    return static_cast<int>(m_lines.at(row).size());
}

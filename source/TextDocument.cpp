#include "TextDocument.h"

void TextDocument::insertChar(int row, int col, char c)
{
	m_lines.at(row).insert(col, 1, c);
}

void TextDocument::deleteChar(int row, int col)
{
	if (row < 0 || row >= getLines()) return;
	if (col < 0 || col >= getLineLength(row)) return;

	m_lines.at(row).erase(col, 1);
}

void TextDocument::insertLine(int row, int col)
{
	std::string remaining = m_lines.at(row).substr(col);

	m_lines.at(row).erase(col);
	m_lines.insert(m_lines.begin() + row + 1, remaining);
}

void TextDocument::appendLine()
{
	if (m_lines.empty()) { m_lines.push_back(""); return; }

	m_lines.push_back("");
}

void TextDocument::mergeLines(int row)
{
	if (row <= 0 || row >= m_lines.size()) return;
	
	m_lines.at(row - 1) += m_lines.at(row);
	m_lines.erase(m_lines.begin() + row);
}

std::string TextDocument::getLine(int row) const
{
	return m_lines.at(row);
}

int TextDocument::getLines() const
{
	return m_lines.size();
}

int TextDocument::getLineLength(int row) const
{
	return m_lines.at(row).size();
}

void TextDocument::clear()
{
	m_lines.clear();
	m_lines.push_back("");
}
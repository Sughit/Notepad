#include "TextDocument.h"

void TextDocument::insertChar(int row, int col, char c)
{
	lines.at(row).insert(col, 1, c);
}

void TextDocument::deleteChar(int row, int col)
{
	if (row < 0 || row >= getLines()) return;
	if (col < 0 || col >= getLineLength(row)) return;

	lines.at(row).erase(col, 1);
}

void TextDocument::insertLine(int row, int col)
{
	std::string remaining = lines.at(row).substr(col);

	lines.at(row).erase(col);
	lines.insert(lines.begin() + row + 1, remaining);
}

void TextDocument::appendLine()
{
	if (lines.empty()) { lines.push_back(""); return; }

	lines.push_back("");
}

void TextDocument::mergeLines(int row)
{
	if (row <= 0 || row >= lines.size()) return;
	
	lines.at(row - 1) += lines.at(row);
	lines.erase(lines.begin() + row);
}

std::string TextDocument::getLine(int row) const
{
	return lines.at(row);
}

int TextDocument::getLines() const
{
	return lines.size();
}

int TextDocument::getLineLength(int row) const
{
	return lines.at(row).size();
}

void TextDocument::clear()
{
	lines.clear();
	lines.push_back("");
}
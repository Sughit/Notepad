#pragma once
#include <string>
#include <vector>

class TextDocument
{
private:
    std::vector<std::string> m_lines = { "" };

public:
    void insertChar(int row, int col, char character);
    void deleteRange(int row, int first, int last);
    void insertLine(int row, int col);
    void mergeLines(int row);
    void clear();

    const std::string& getLine(int row) const;
    int getLines() const;
    int getLineLength(int row) const;
};

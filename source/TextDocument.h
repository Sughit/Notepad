#pragma once
#include <vector>
#include <string>

using namespace std;

class TextDocument
{
private:
	std::vector<std::string> lines = { "" };

public:
	TextDocument() = default;

	void insertChar(int row, int col, char c);
	void deleteChar(int row, int col);

	void insertLine(int row, int col);
	void appendLine();
	void mergeLines(int row);

	std::string getLine(int row) const;
	int getLines() const;
	int getLineLength(int row) const;
	void clear();
};
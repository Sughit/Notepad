#pragma once

class TextCursor
{
private:
	int row = 0;
	int col = 0;

public:
	int getRow() const;
	int getCol() const;

	void setPosition(int r, int c);
};
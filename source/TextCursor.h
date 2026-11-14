#pragma once

class TextCursor
{
private:
	int m_row = 0;
	int m_col = 0;

public:
	int getRow() const;
	int getCol() const;

	void setPosition(int r, int c);
};
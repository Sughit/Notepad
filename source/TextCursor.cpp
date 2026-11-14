#include "TextCursor.h"

int TextCursor::getRow() const
{
	return m_row;
}

int TextCursor::getCol() const
{
	return m_col;
}

void TextCursor::setPosition(int r, int c)
{
	this->m_row = r;
	this->m_col = c;
}
#include "TextCursor.h"

int TextCursor::getRow() const
{
	return row;
}

int TextCursor::getCol() const
{
	return col;
}

void TextCursor::setPosition(int r, int c)
{
	this->row = r;
	this->col = c;
}
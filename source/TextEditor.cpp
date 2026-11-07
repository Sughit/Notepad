#include <algorithm>
#include "TextEditor.h"

const TextDocument& TextEditor::getDocument() const
{
	return doc;
}

const TextCursor& TextEditor::getCursor() const
{
	return cursor;
}

void TextEditor::insertChar(char c)
{
	int row = cursor.getRow();
	int col = cursor.getCol();

	doc.insertChar(row, col, c);
	cursor.setPosition(row, col + 1);
}

void TextEditor::backspace()
{
	int row = cursor.getRow();
	int col = cursor.getCol();

	if (col > 0)
	{
		doc.deleteChar(row, col - 1);
		cursor.setPosition(row, col - 1);
	}
	else if (row > 0)
	{
		int newCol = doc.getLineLength(row - 1);

		doc.mergeLines(row);
		cursor.setPosition(row - 1, newCol);
	}
}

void TextEditor::deleteChar()
{
	int row = cursor.getRow();
	int col = cursor.getCol();

	if (col < doc.getLineLength(row))
	{
		doc.deleteChar(row, col);
	}
	else if (row < doc.getLines() - 1)
	{
		doc.mergeLines(row + 1);
	}
}

void TextEditor::enter()
{
	int row = cursor.getRow();
	int col = cursor.getCol();

	doc.insertLine(row, col);
	cursor.setPosition(row + 1, 0);
}

void TextEditor::clear()
{
	doc.clear();
	cursor.setPosition(0, 0);
}

void TextEditor::moveLeft()
{
	int row = cursor.getRow();
	int col = cursor.getCol();

	if (col > 0)
	{
		cursor.setPosition(row, col - 1);
	}
	else if (row > 0)
	{
		cursor.setPosition(row - 1, doc.getLineLength(row - 1));
	}
}

void TextEditor::moveRight()
{
	int row = cursor.getRow();
	int col = cursor.getCol();

	if (col < doc.getLineLength(row))
	{
		cursor.setPosition(row, col + 1);
	}
	else if (row < doc.getLines() - 1)
	{
		cursor.setPosition(row + 1, 0);
	}
}

void TextEditor::moveUp()
{
	int row = cursor.getRow();
	int col = cursor.getCol();

	if (row <= 0) return;

	int newCol = std::min(col, doc.getLineLength(row - 1));
	cursor.setPosition(row - 1, newCol);
}

void TextEditor::moveDown()
{
	int row = cursor.getRow();
	int col = cursor.getCol();

	if (row >= doc.getLines() - 1) return;

	int newCol = std::min(col, doc.getLineLength(row + 1));
	cursor.setPosition(row + 1, newCol);
}

void TextEditor::moveHome()
{
	cursor.setPosition(cursor.getRow(), 0);
}

void TextEditor::moveEnd()
{
	int row = cursor.getRow();

	cursor.setPosition(row, doc.getLineLength(row));
}
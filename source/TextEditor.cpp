#include <algorithm>
#include "TextEditor.h"

const TextDocument& TextEditor::getDocument() const
{
	return m_doc;
}

const TextCursor& TextEditor::getCursor() const
{
	return m_cursor;
}

void TextEditor::insertChar(char c)
{
	int row = m_cursor.getRow();
	int col = m_cursor.getCol();

	m_doc.insertChar(row, col, c);
	m_cursor.setPosition(row, col + 1);
}

void TextEditor::backspace()
{
	int row = m_cursor.getRow();
	int col = m_cursor.getCol();

	if (col > 0)
	{
		m_doc.deleteChar(row, col - 1);
		m_cursor.setPosition(row, col - 1);
	}
	else if (row > 0)
	{
		int newCol = m_doc.getLineLength(row - 1);

		m_doc.mergeLines(row);
		m_cursor.setPosition(row - 1, newCol);
	}
}

void TextEditor::deleteChar()
{
	int row = m_cursor.getRow();
	int col = m_cursor.getCol();

	if (col < m_doc.getLineLength(row))
	{
		m_doc.deleteChar(row, col);
	}
	else if (row < m_doc.getLines() - 1)
	{
		m_doc.mergeLines(row + 1);
	}
}

void TextEditor::enter()
{
	int row = m_cursor.getRow();
	int col = m_cursor.getCol();

	m_doc.insertLine(row, col);
	m_cursor.setPosition(row + 1, 0);
}

void TextEditor::clear()
{
	m_doc.clear();
	m_cursor.setPosition(0, 0);
}

void TextEditor::moveLeft()
{
	int row = m_cursor.getRow();
	int col = m_cursor.getCol();

	if (col > 0)
	{
		m_cursor.setPosition(row, col - 1);
	}
	else if (row > 0)
	{
		m_cursor.setPosition(row - 1, m_doc.getLineLength(row - 1));
	}
}

void TextEditor::moveRight()
{
	int row = m_cursor.getRow();
	int col = m_cursor.getCol();

	if (col < m_doc.getLineLength(row))
	{
		m_cursor.setPosition(row, col + 1);
	}
	else if (row < m_doc.getLines() - 1)
	{
		m_cursor.setPosition(row + 1, 0);
	}
}

void TextEditor::moveUp()
{
	int row = m_cursor.getRow();
	int col = m_cursor.getCol();

	if (row <= 0) return;

	int newCol = std::min(col, m_doc.getLineLength(row - 1));
	m_cursor.setPosition(row - 1, newCol);
}

void TextEditor::moveDown()
{
	int row = m_cursor.getRow();
	int col = m_cursor.getCol();

	if (row >= m_doc.getLines() - 1) return;

	int newCol = std::min(col, m_doc.getLineLength(row + 1));
	m_cursor.setPosition(row + 1, newCol);
}

void TextEditor::moveHome()
{
	m_cursor.setPosition(m_cursor.getRow(), 0);
}

void TextEditor::moveEnd()
{
	int row = m_cursor.getRow();

	m_cursor.setPosition(row, m_doc.getLineLength(row));
}
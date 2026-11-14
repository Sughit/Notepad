#include "TextEditor.h"
#include "Utf8.h"
#include <algorithm>

const TextDocument& TextEditor::getDocument() const { return m_doc; }
const TextCursor& TextEditor::getCursor() const { return m_cursor; }
TextCursor& TextEditor::getCursor() { return m_cursor; }

void TextEditor::insertChar(char character)
{
    const int row = m_cursor.getRow();
    const int col = m_cursor.getCol();
    m_doc.insertChar(row, col, character);
    m_cursor.setPosition(row, col + 1);
}

void TextEditor::backspace()
{
    const int row = m_cursor.getRow();
    const int col = m_cursor.getCol();
    if (col > 0)
    {
        const int previous = Utf8::previous(m_doc.getLine(row), col);
        m_doc.deleteRange(row, previous, col);
        m_cursor.setPosition(row, previous);
    }
    else if (row > 0)
    {
        const int previousEnd = m_doc.getLineLength(row - 1);
        m_doc.mergeLines(row);
        m_cursor.setPosition(row - 1, previousEnd);
    }
}

void TextEditor::deleteChar()
{
    const int row = m_cursor.getRow();
    const int col = m_cursor.getCol();
    if (col < m_doc.getLineLength(row))
    {
        const int next = Utf8::next(m_doc.getLine(row), col);
        m_doc.deleteRange(row, col, next);
    }
    else if (row + 1 < m_doc.getLines())
    {
        m_doc.mergeLines(row + 1);
    }
}

void TextEditor::enter()
{
    const int row = m_cursor.getRow();
    m_doc.insertLine(row, m_cursor.getCol());
    m_cursor.setPosition(row + 1, 0);
}

void TextEditor::clear()
{
    m_doc.clear();
    m_cursor.setPosition(0, 0);
}

void TextEditor::moveLeft()
{
    const int row = m_cursor.getRow();
    const int col = m_cursor.getCol();
    if (col > 0)
    {
        m_cursor.setPosition(row, Utf8::previous(m_doc.getLine(row), col));
    }
    else if (row > 0)
    {
        m_cursor.setPosition(row - 1, m_doc.getLineLength(row - 1));
    }
}

void TextEditor::moveRight()
{
    const int row = m_cursor.getRow();
    const int col = m_cursor.getCol();
    if (col < m_doc.getLineLength(row))
    { 
        m_cursor.setPosition(row, Utf8::next(m_doc.getLine(row), col));
    }
    else if (row + 1 < m_doc.getLines())
    {
        m_cursor.setPosition(row + 1, 0);
    }
}

void TextEditor::moveUp()
{
    const int row = m_cursor.getRow();
    if (row <= 0) { return; }

    const auto& previous = m_doc.getLine(row - 1);
    const int col = std::min(m_cursor.getCol(), m_doc.getLineLength(row - 1));
    m_cursor.setPosition(row - 1, Utf8::clampBoundary(previous, col));
}

void TextEditor::moveDown()
{
    const int row = m_cursor.getRow();
    if (row + 1 >= m_doc.getLines()) { return; }

    const auto& next = m_doc.getLine(row + 1);
    const int col = std::min(m_cursor.getCol(), m_doc.getLineLength(row + 1));
    m_cursor.setPosition(row + 1, Utf8::clampBoundary(next, col));
}

void TextEditor::moveHome()
{
    m_cursor.setPosition(m_cursor.getRow(), 0);
}

void TextEditor::moveEnd()
{
    const int row = m_cursor.getRow();
    m_cursor.setPosition(row, m_doc.getLineLength(row));
}

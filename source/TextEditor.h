#pragma once
#include "TextDocument.h"
#include "TextCursor.h"

class TextEditor
{
private:
    TextDocument m_doc;
    TextCursor m_cursor;

public:
    const TextDocument& getDocument() const;
    const TextCursor& getCursor() const;
    TextCursor& getCursor();

    void insertChar(char character);
    void backspace();
    void deleteChar();
    void enter();
    void clear();

    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void moveHome();
    void moveEnd();
};

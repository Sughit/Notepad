#pragma once

#include "TextDocument.h"
#include "TextCursor.h"

class TextEditor
{
private:
	TextDocument doc;
	TextCursor cursor;

public:
	const TextDocument& getDocument() const;
	const TextCursor& getCursor() const;

	void insertChar(char c);
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
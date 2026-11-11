#pragma once

#include "TextEditor.h" 

class InputManager
{
private:
	int ch = 0;

public:
	void update(TextEditor& editor);
};
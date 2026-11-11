#include "InputManager.h"
#include "graphics.h"

void InputManager::update(TextEditor& editor)
{
	if (!kbhit()) { return; }

	ch = getch();

	if (ch == 0 || ch == 224) // TASTE SPECIALE
	{
		int special = getch();

		if (special == KEY_UP) editor.moveUp();
		if (special == KEY_DOWN) editor.moveDown();
		if (special == KEY_LEFT) editor.moveLeft();
		if (special == KEY_RIGHT) editor.moveRight();
		if (special == KEY_HOME) editor.moveHome();
		if (special == KEY_END) editor.moveEnd();
	}
	else if (ch >= 32 && ch <= 126)
	{
		editor.insertChar((char)ch);
	}
	else if (ch == VK_BACK) // BACKSPACE
	{
		editor.backspace();
	}
	else if (ch == VK_TAB) // TAB
	{
		editor.insertChar(' ');
		editor.insertChar(' ');
		editor.insertChar(' ');
		editor.insertChar(' ');
	}
	else if (ch == VK_RETURN) // ENTER
	{
		editor.enter();
	}
}
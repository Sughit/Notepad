#pragma once

#include <graphics.h>
#include <windows.h>
#include "TextEditor.h"

const int MENU_HEIGHT = 30;

class RenderWindow
{
private:
	int lastWidth = -1;
	int lastHeight = -1;

	void init(int w, int h);

	void drawMenu();
	void drawEditor(const TextEditor& editor);

public:
	RenderWindow(int w, int h) { init(w, h); }

	void render(const TextEditor& editor);
	void update(const TextEditor& editor);
};
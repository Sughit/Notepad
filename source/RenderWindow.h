#pragma once

#include <graphics.h>
#include <windows.h>
#include <vector>
#include <string>
#include "TextEditor.h"

const int MENU_HEIGHT = 30;

class RenderWindow
{
private:
	int lastWidth = -1;
	int lastHeight = -1;

	int lastRow = -1;
	int lastCol = -1;

	std::vector<std::string> lastLines;

	void init(int w, int h);

	void drawMenu();
	void drawEditor(const TextEditor& editor);
	void drawCursor(const TextEditor& editor);

public:
	RenderWindow(int w, int h) { init(w, h); }

	void render(const TextEditor& editor);
	void update(const TextEditor& editor);
};
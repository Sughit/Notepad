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
	int m_lastWidth = -1;
	int m_lastHeight = -1;

	int m_lastRow = -1;
	int m_lastCol = -1;

	std::vector<std::string> m_lastLines;

	void init(int w, int h);

	void drawMenu();
	void drawEditor(const TextEditor& editor);
	void drawCursor(const TextEditor& editor);

public:
	RenderWindow(int w, int h) { init(w, h); }

	void render(const TextEditor& editor);
	void update(const TextEditor& editor);
};
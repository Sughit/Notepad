#pragma once

#include <graphics.h>
#include <windows.h>

const int MENU_HEIGHT = 30;

class RenderWindow
{
private:
	int lastWidth = -1;
	int lastHeight = -1;

	void init(int w, int h);

	void drawMenu();
	void drawEditor();
	void render();

public:
	RenderWindow(int w, int h) { init(w, h); }

	void update();
};
#include "RenderWindow.h"

void RenderWindow::init(int w, int h)
{
    initwindow(w, h, "Notepad", 0, 0, false);

    HWND hwnd = FindWindowA(NULL, "Notepad");

    if (hwnd == NULL)
    {
        MessageBoxA(NULL, "Window not found!", "Error", MB_OK);
        return;
    }

    LONG_PTR style = GetWindowLongPtr(hwnd, GWL_STYLE);

    style |= WS_THICKFRAME | WS_MAXIMIZEBOX;

    SetWindowLongPtr(hwnd, GWL_STYLE, style);

    SetWindowPos(
        hwnd, NULL,
        0, 0, 0, 0,
        SWP_NOMOVE |
        SWP_NOSIZE |
        SWP_NOZORDER |
        SWP_FRAMECHANGED
    );

    lastWidth = getmaxx();
    lastHeight = getmaxy();

    render();
}

void RenderWindow::drawMenu()
{
	setfillstyle(SOLID_FILL, LIGHTGRAY);
	bar(0, 0, getmaxx(), MENU_HEIGHT);

	setbkcolor(LIGHTGRAY);
	setcolor(BLACK);
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);

	outtextxy(15, 10, (char*)"File");
	outtextxy(70, 10, (char*)"Edit");
	outtextxy(125, 10, (char*)"View");

	setcolor(DARKGRAY);
	line(0, MENU_HEIGHT, getmaxx(), MENU_HEIGHT);
}

void RenderWindow::drawEditor()
{
	setfillstyle(SOLID_FILL, WHITE);
	bar(0, MENU_HEIGHT + 1, getmaxx(), getmaxy());
}

void RenderWindow::render()
{
	setbkcolor(WHITE);
	cleardevice();

	drawEditor();
	drawMenu();
}

void RenderWindow::update()
{
	int w = getmaxx();
	int h = getmaxy();

	if (lastWidth != w || lastHeight != h)
	{
		render();

		lastWidth = w;
		lastHeight = h;
	}
}
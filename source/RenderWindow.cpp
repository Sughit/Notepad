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

void RenderWindow::drawEditor(const TextEditor& editor)
{
    const TextDocument& doc = editor.getDocument();

    const int PADDING_X = 10;
    const int PADDING_Y = 10;
    const int LINE_HEIGHT = 20;

    setfillstyle(SOLID_FILL, WHITE);
    bar(0, MENU_HEIGHT + 1, getmaxx(), getmaxy());

    setbkcolor(WHITE);
    setcolor(BLACK);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);

    for (int i = 0; i < doc.getLines(); i++)
    {
        int x = PADDING_X;
        int y = MENU_HEIGHT + PADDING_Y + i * LINE_HEIGHT;

        if (y + LINE_HEIGHT > getmaxy())
            break;

        std::string line = doc.getLine(i);

        outtextxy(x, y, const_cast<char*>(line.c_str()));
    }
}

void RenderWindow::render(const TextEditor& editor)
{
	setbkcolor(WHITE);
	cleardevice();

	drawEditor(editor);
	drawMenu();
}

void RenderWindow::update(const TextEditor& editor)
{
	int w = getmaxx();
	int h = getmaxy();

	if (lastWidth != w || lastHeight != h)
	{
		render(editor);

		lastWidth = w;
		lastHeight = h;
	}
}
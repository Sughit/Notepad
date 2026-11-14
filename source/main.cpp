#include "RenderWindow.h"
#include "TextEditor.h"
#include "InputManager.h"
#include "LanguageManager.h"

#include <iostream>

int main()
{
    RenderWindow window(1920, 1080);
    TextEditor editor;
    InputManager input;
    LanguageManager language("config.txt");

    window.render(editor);

    while (true)
    {
        input.update(editor);
        window.update(editor);

        if (GetAsyncKeyState(VK_ESCAPE) & 1) break;

        delay(16);
    }

    closegraph();

    return 0;
}

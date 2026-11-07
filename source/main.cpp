#include "RenderWindow.h"
#include "TextEditor.h"

#include <iostream>

int main()
{
    RenderWindow window(1920, 1080);
    TextEditor editor;

    std::string text = "Hello world";

    for (char c : text) editor.insertChar(c);
    editor.enter();

    text = "This is my notepad!";

    for (char c : text) editor.insertChar(c);
    editor.enter();

    window.render(editor);

    while (true)
    {
        window.update(editor);

        if (GetAsyncKeyState(VK_ESCAPE) & 1) break;

        delay(16);
    }

    closegraph();

    return 0;
}

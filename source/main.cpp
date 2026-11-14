#include "AppStyle.h"
#include "InputManager.h"
#include "LanguageManager.h"
#include "RenderWindow.h"
#include "TextEditor.h"
#include <graphics.h>
#include <windows.h>

int main()
{
    LanguageManager language("config.txt");
    TextEditor editor;
    InputManager input;
    RenderWindow window(AppStyle::InitialWidth, AppStyle::InitialHeight);

    while (!(GetAsyncKeyState(VK_ESCAPE) & 1))
    {
        input.update(editor, window, language);
        window.update(editor, language);
        delay(AppStyle::FrameDelayMs);
    }
}

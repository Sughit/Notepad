#include "InputManager.h"
#include "AppStyle.h"
#include "LanguageManager.h"
#include "RenderWindow.h"
#include "TextEditor.h"
#include <graphics.h>
#include <windows.h>

namespace
{
    constexpr int DeleteKeyScanCode = 83; // Codul de la Windows pentru delete
}

void InputManager::update(TextEditor& editor, RenderWindow& window, LanguageManager& language)
{
    handleMouse(editor, window, language);
    handleKeyboard(editor);
}

void InputManager::handleMouse(TextEditor& editor, RenderWindow& window, LanguageManager& language)
{
    while (ismouseclick(WM_LBUTTONDOWN))
    {
        int x = 0;
        int y = 0;
        getmouseclick(WM_LBUTTONDOWN, x, y);
        const Point click = {x, y};

        if (window.menuClick(click, language)) { continue; }
        if (y < AppStyle::MenuHeight || x < 0) { continue; }

        const auto position = window.documentPosition(click, editor.getDocument());
        editor.getCursor().setPosition(position.row, position.col);
    }
}

void InputManager::handleKeyboard(TextEditor& editor)
{
    if (!kbhit()) { return; }

    const int key = getch();
    if (key == 0 || key == 224) // Cod special
    {
        const int special = getch();
        switch (special)
        {
        case KEY_UP:    editor.moveUp();    break;
        case KEY_DOWN:  editor.moveDown();  break;
        case KEY_LEFT:  editor.moveLeft();  break;
        case KEY_RIGHT: editor.moveRight(); break;
        case KEY_HOME:  editor.moveHome();  break;
        case KEY_END:   editor.moveEnd();   break;
        case DeleteKeyScanCode:    editor.deleteChar();break;
        }
        return;
    }

    switch (key)
    {
    case VK_BACK:   editor.backspace(); break;
    case VK_RETURN: editor.enter();     break;
    case VK_TAB:
        for (int count = 0; count < AppStyle::TabSpaces; count++)
            editor.insertChar(' ');
        break;
    default:
        if (key >= ' ' && key <= '~')
            editor.insertChar(static_cast<char>(key));
        break;
    }
}

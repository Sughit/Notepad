#include "AppStyle.h"
#include "InputManager.h"
#include "LanguageManager.h"
#include "RenderWindow.h"
#include "TextEditor.h"
#include "PieceTable.h"
#include <graphics.h>
#include <windows.h>

#include <iostream>

int main()
{
    LanguageManager language("config.txt");
    TextEditor editor;
    InputManager input;
    RenderWindow window(AppStyle::InitialWidth, AppStyle::InitialHeight);

    int x = 0;
    std::cout << "Give command\n 0. Default\n 1. Piece Table\n";
    std::cin >> x;

    if (x == 0)
    {
        while (!(GetAsyncKeyState(VK_ESCAPE) & 1))
        {
            input.update(editor, window, language);
            window.update(editor, language);
            delay(AppStyle::FrameDelayMs);
        }
    }
    else if (x == 1)
    {
        std::string word = "Hello\nWorld!\n";

        PieceTable pieceTable(word);

        pieceTable.printTree(pieceTable.root); std::cout << "\n";
        pieceTable.insertCharacter('C', 1, 0);
        pieceTable.printTree(pieceTable.root); std::cout << "\n";
        pieceTable.insertCharacter('r', 1, 1);
        pieceTable.printTree(pieceTable.root); std::cout << "\n";
        pieceTable.insertCharacter('u', 1, 2);
        pieceTable.printTree(pieceTable.root); std::cout << "\n";
        pieceTable.insertCharacter('e', 1, 3);
        pieceTable.printTree(pieceTable.root); std::cout << "\n";
        pieceTable.insertCharacter('l', 1, 4);
        pieceTable.printTree(pieceTable.root); std::cout << "\n";
        pieceTable.insertCharacter('\n', 1, 5);
        pieceTable.printTree(pieceTable.root); std::cout << "\n";

        pieceTable.getTree(pieceTable.root);
        std::cout << "\n";
        pieceTable.printTree(pieceTable.root);
    }

    return 0;
}

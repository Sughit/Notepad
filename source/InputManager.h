#pragma once

class TextEditor;
class RenderWindow;
class LanguageManager;

class InputManager
{
private:
    void handleKeyboard(TextEditor& editor);
    void handleMouse(TextEditor& editor, RenderWindow& window, LanguageManager& language);

public:
    void update(TextEditor& editor, RenderWindow& window, LanguageManager& language);
};
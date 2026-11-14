#pragma once
#include "EditorLayout.h"
#include "MenuBar.h"
#include "TextRenderer.h"
#include <memory>
#include <string>
#include <vector>

class LanguageManager;
class TextEditor;

class RenderWindow
{
private:
    void drawEditor(const TextEditor& editor);

    HWND m_window = nullptr;
    std::unique_ptr<TextRenderer> m_text;
    MenuBar m_menu;
    EditorLayout m_layout;

    bool m_needsRedraw = true;
    int m_previousWidth = -1;
    int m_previousHeight = -1;
    int m_previousLanguage = -1;
    int m_previousRow = -1;
    int m_previousCol = -1;
    std::vector<std::string> m_previousLines;

public:
    RenderWindow(int width, int height);
    ~RenderWindow();

    RenderWindow(const RenderWindow&) = delete;
    RenderWindow& operator=(const RenderWindow&) = delete;

    void render(const TextEditor& editor, const LanguageManager& language);
    void update(const TextEditor& editor, const LanguageManager& language);
    bool menuClick(Point point, LanguageManager& language);
    DocumentPosition documentPosition(Point point, const TextDocument& document);
};
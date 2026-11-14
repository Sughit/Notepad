#include "RenderWindow.h"
#include "AppStyle.h"
#include "LanguageManager.h"
#include "TextEditor.h"
#include <graphics.h>
#include <stdexcept>
#include <utility>

RenderWindow::RenderWindow(int width, int height)
{
    initwindow(width, height, "Notepad", 0, 0, false);
    m_window = FindWindowA(nullptr, "Notepad");
    if (!m_window) { throw std::runtime_error("Could not find Notepad window"); }

    LONG_PTR style = GetWindowLongPtr(m_window, GWL_STYLE);
    SetWindowLongPtr(m_window, GWL_STYLE, style | WS_THICKFRAME | WS_MAXIMIZEBOX);
    SetWindowPos(m_window, nullptr, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);

    m_text = std::make_unique<TextRenderer>(m_window);
}

RenderWindow::~RenderWindow()
{
    m_text.reset();
    closegraph();
}

void RenderWindow::drawEditor(const TextEditor& editor)
{
    const auto& doc = editor.getDocument();
    RECT client = {};
    GetClientRect(m_window, &client);

    for (int row = 0; row < doc.getLines(); row++)
    {
        const int y = AppStyle::MenuHeight + AppStyle::EditorPaddingY + row * AppStyle::EditorLineHeight;
        if (y >= client.bottom) { break; }

        m_text->draw(AppStyle::EditorPaddingX, y, doc.getLine(row));
    }

    const auto& cursor = editor.getCursor();
    const auto cursorPoint = m_layout.toScreen(doc, { cursor.getRow(), cursor.getCol() }, *m_text);
    if (cursorPoint.y < client.bottom)
    {
        m_text->drawCursor(cursorPoint.x, cursorPoint.y);
    }
}

void RenderWindow::render(const TextEditor& editor, const LanguageManager& language)
{
    m_text->begin();
    RECT client = {};
    GetClientRect(m_window, &client);
    m_text->fillRect(0, 0, client.right, client.bottom, AppStyle::EditorBackground);

    m_menu.refresh(language, *m_text);
    drawEditor(editor);
    m_menu.drawBackground(client.right, *m_text);
    m_menu.drawText(*m_text);
    m_text->end();  
}

void RenderWindow::update(const TextEditor& editor, const LanguageManager& language)
{
    RECT client = {};
    GetClientRect(m_window, &client);
    const int width = client.right - client.left;
    const int height = client.bottom - client.top;
    const auto& cursor = editor.getCursor();
    const auto& doc = editor.getDocument();

    std::vector<std::string> lines;
    lines.reserve(doc.getLines());
    for (int row = 0; row < doc.getLines(); row++)
    {
        lines.push_back(doc.getLine(row));
    }

    if (m_needsRedraw || width != m_previousWidth || height != m_previousHeight || language.activeIndex() != m_previousLanguage ||
        cursor.getRow() != m_previousRow || cursor.getCol() != m_previousCol || lines != m_previousLines)
    {
        render(editor, language);
        m_needsRedraw = false;
        m_previousWidth = width;
        m_previousHeight = height;
        m_previousLanguage = language.activeIndex();
        m_previousRow = cursor.getRow();
        m_previousCol = cursor.getCol();
        m_previousLines = std::move(lines);
    }
}

bool RenderWindow::menuClick(Point point, LanguageManager& language)
{
    m_text->begin(false);
    const auto result = m_menu.click(point, language, *m_text);
    m_text->end();
    
    m_needsRedraw = true;
    return result == MenuBar::ClickResult::Consumed;
}

DocumentPosition RenderWindow::documentPosition(Point point, const TextDocument& document)
{
    m_text->begin(false);
    const auto position = m_layout.fromScreen(document, point, *m_text);
    m_text->end();
    return position;
}

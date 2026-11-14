#pragma once
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <string>

class TextRenderer
{
private:
    static std::wstring toWide(const std::string& utf8);

    HWND m_window = nullptr;
    HDC m_windowDc = nullptr;
    HDC m_dc = nullptr;
    HBITMAP m_buffer = nullptr;
    HGDIOBJ m_previousBitmap = nullptr;
    HGDIOBJ m_previousFont = nullptr;
    HFONT m_font = nullptr;
    int m_frameWidth = 0;
    int m_frameHeight = 0;
    bool m_isFrame = false;

public:
    explicit TextRenderer(HWND window);
    ~TextRenderer();

    TextRenderer(const TextRenderer&) = delete;
    TextRenderer& operator=(const TextRenderer&) = delete;

    void begin(bool frame = true);
    void end();
    void draw(int x, int y, const std::string& utf8);
    void drawCursor(int x, int y);
    void fillRect(int x, int y, int width, int height, COLORREF color);
    void frameRect(int x, int y, int width, int height, COLORREF color);
    void drawLine(int x1, int y1, int x2, int y2, COLORREF color);
    int width(const std::string& utf8);
    int height();
};
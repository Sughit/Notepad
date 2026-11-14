#include "TextRenderer.h"
#include "AppStyle.h"

TextRenderer::TextRenderer(HWND window) : m_window(window)
{
    m_font = CreateFontW(
        -AppStyle::FontSize, 0, 0, 0, FW_NORMAL,
        FALSE, FALSE, FALSE, DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        CLEARTYPE_QUALITY, FIXED_PITCH | FF_MODERN, L"Consolas");
}

TextRenderer::~TextRenderer()
{
    end();
    if (m_font)
    {
        DeleteObject(m_font);
    }
}

void TextRenderer::begin(bool frame)
{
    if (m_dc) { return; }

    m_windowDc = GetDC(m_window);
    if (!m_windowDc) { return; }

    m_isFrame = frame;
    if (frame)
    {
        RECT client = {};
        GetClientRect(m_window, &client);
        m_frameWidth = client.right - client.left;
        m_frameHeight = client.bottom - client.top;

        if (m_frameWidth <= 0 || m_frameHeight <= 0)
        {
            ReleaseDC(m_window, m_windowDc);
            m_windowDc = nullptr;
            return;
        }

        m_dc = CreateCompatibleDC(m_windowDc);
        if (!m_dc)
        {
            ReleaseDC(m_window, m_windowDc);
            m_windowDc = nullptr;
            return;
        }
        m_buffer = CreateCompatibleBitmap(m_windowDc, m_frameWidth, m_frameHeight);
        if (!m_buffer)
        {
            DeleteDC(m_dc);
            m_dc = nullptr;
            ReleaseDC(m_window, m_windowDc);
            m_windowDc = nullptr;
            return;
        }
        m_previousBitmap = SelectObject(m_dc, m_buffer);
    }
    else
    {
        m_dc = m_windowDc;
    }

    if (m_font)
    {
        m_previousFont = SelectObject(m_dc, m_font);
    }

    SetBkMode(m_dc, TRANSPARENT);
    SetTextColor(m_dc, AppStyle::TextColor);
}

void TextRenderer::end()
{
    if (!m_dc) { return; }

    if (m_previousFont)
    {
        SelectObject(m_dc, m_previousFont);
    }
    m_previousFont = nullptr;

    if (m_isFrame)
    {
        BitBlt(m_windowDc, 0, 0, m_frameWidth, m_frameHeight, m_dc, 0, 0, SRCCOPY);
        SelectObject(m_dc, m_previousBitmap);
        DeleteObject(m_buffer);
        DeleteDC(m_dc);
    }

    ReleaseDC(m_window, m_windowDc);
    m_windowDc = nullptr;
    m_dc = nullptr;
    m_buffer = nullptr;
    m_previousBitmap = nullptr;
    m_isFrame = false;
}

std::wstring TextRenderer::toWide(const std::string& utf8)
{
    if (utf8.empty()) { return {}; }

    const int count = MultiByteToWideChar(CP_UTF8, 0, utf8.data(), static_cast<int>(utf8.size()), nullptr, 0);
    if (count <= 0) { return {}; }

    std::wstring result(count, L'\0');
    MultiByteToWideChar(CP_UTF8, 0, utf8.data(), static_cast<int>(utf8.size()), &result[0], count);
    return result;
}

void TextRenderer::draw(int x, int y, const std::string& utf8)
{
    if (!m_dc) { return; }
    const auto value = toWide(utf8);
    TextOutW(m_dc, x, y, value.c_str(), static_cast<int>(value.size()));
}

void TextRenderer::fillRect(int x, int y, int width, int height, COLORREF color)
{
    if (!m_dc || width <= 0 || height <= 0) { return; }
    RECT rect = {x, y, x + width, y + height};
    HBRUSH brush = CreateSolidBrush(color);
    FillRect(m_dc, &rect, brush);
    DeleteObject(brush);
}

void TextRenderer::frameRect(int x, int y, int width, int height, COLORREF color)
{
    if (!m_dc || width <= 0 || height <= 0) { return; }
    RECT rect = {x, y, x + width, y + height};
    HBRUSH brush = CreateSolidBrush(color);
    FrameRect(m_dc, &rect, brush);
    DeleteObject(brush);
}

void TextRenderer::drawLine(int x1, int y1, int x2, int y2, COLORREF color)
{
    if (!m_dc) { return; }
    HPEN pen = CreatePen(PS_SOLID, 1, color);
    HGDIOBJ oldPen = SelectObject(m_dc, pen);
    MoveToEx(m_dc, x1, y1, nullptr);
    LineTo(m_dc, x2, y2);
    SelectObject(m_dc, oldPen);
    DeleteObject(pen);
}

int TextRenderer::width(const std::string& utf8)
{
    if (!m_dc) { return 0; } 
    const auto value = toWide(utf8);
    SIZE extent = {};
    GetTextExtentPoint32W(m_dc, value.c_str(), static_cast<int>(value.size()), &extent);
    return extent.cx;
}

int TextRenderer::height()
{
    if (!m_dc) { return AppStyle::FontSize; }
    TEXTMETRICW metrics = {};
    GetTextMetricsW(m_dc, &metrics);
    return metrics.tmHeight;
}

void TextRenderer::drawCursor(int x, int y)
{
    drawLine(x, y, x, y + height(), AppStyle::TextColor);
}

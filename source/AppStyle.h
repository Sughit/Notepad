#pragma once
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>

namespace AppStyle
{
    constexpr int InitialWidth = 1200;
    constexpr int InitialHeight = 750;
    constexpr int FrameDelayMs = 16;

    constexpr int MenuHeight = 34;
    constexpr int MenuLeftPadding = 10;
    constexpr int MenuButtonPadding = 13;
    constexpr int MenuButtonGap = 3;

    constexpr int SubMenuMinWidth = 160;
    constexpr int SubMenuRowHeight = 30;
    constexpr int SubMenuPadding = 12;
    constexpr int SubMenuCheckWidth = 18;

    constexpr int EditorPaddingX = 12;
    constexpr int EditorPaddingY = 9;
    constexpr int EditorLineHeight = 23;
    constexpr int FontSize = 18;
    constexpr int TabSpaces = 4;

    constexpr COLORREF MenuBackground = RGB(225, 225, 225);
    constexpr COLORREF EditorBackground = RGB(255, 255, 255);
    constexpr COLORREF SubMenuSelectedBackground = RGB(245, 245, 245);
    constexpr COLORREF BorderColor = RGB(145, 145, 145);
    constexpr COLORREF TextColor = RGB(0, 0, 0);
}

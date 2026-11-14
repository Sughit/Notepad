#include "EditorLayout.h"
#include "AppStyle.h"
#include "TextDocument.h"
#include "TextRenderer.h"
#include "Utf8.h"
#include <algorithm>

Point EditorLayout::toScreen(const TextDocument& document, DocumentPosition position, TextRenderer& text) const
{
    const std::string line = document.getLine(position.row);
    const int col = Utf8::clampBoundary(line, position.col);

    return 
    {
        AppStyle::EditorPaddingX + text.width(line.substr(0, col)),
        AppStyle::MenuHeight + AppStyle::EditorPaddingY + position.row * AppStyle::EditorLineHeight
    };
}

DocumentPosition EditorLayout::fromScreen(const TextDocument& document, Point point, TextRenderer& text) const
{
    const int relativeY = point.y - AppStyle::MenuHeight - AppStyle::EditorPaddingY;
    const int row = std::clamp(relativeY < 0 ? 0 : relativeY / AppStyle::EditorLineHeight, 0, document.getLines() - 1);

    const auto line = document.getLine(row);
    const auto offsets = Utf8::boundaries(line);
    const int relativeX = point.x - AppStyle::EditorPaddingX;
    int column = 0;

    for (std::size_t index = 1; index < offsets.size(); index++)
    {
        const int left = text.width(line.substr(0, offsets[index - 1]));
        const int right = text.width(line.substr(0, offsets[index]));
        if (relativeX < (left + right) / 2) { break; }
        column = offsets[index];
    }

    return {row, column};
}

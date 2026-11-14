#pragma once
#include "Geometry.h"

class TextDocument;
class TextRenderer;

class EditorLayout
{
public:
    Point toScreen(const TextDocument& document, DocumentPosition position, TextRenderer& text) const;
    DocumentPosition fromScreen(const TextDocument& document, Point point, TextRenderer& text) const;
};

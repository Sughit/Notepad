#include "Utf8.h"
#include <algorithm>

namespace
{
    bool isContinuation(unsigned char c)
    {
        return (c & 0xC0) == 0x80;
    }
}

std::vector<int> Utf8::boundaries(const std::string& text)
{
    std::vector<int> offsets = {0};
    for (int i = 1; i < static_cast<int>(text.size()); i++)
    {
        if (!isContinuation(static_cast<unsigned char>(text[i])))
        {
            offsets.push_back(i);
        }
    }
    offsets.push_back(static_cast<int>(text.size()));
    return offsets;
}

int Utf8::previous(const std::string& text, int offset)
{
    const auto positions = boundaries(text);
    const auto it = std::lower_bound(positions.begin(), positions.end(), offset);
    return it == positions.begin() ? 0 : *(it - 1);
}

int Utf8::next(const std::string& text, int offset)
{
    const auto positions = boundaries(text);
    const auto it = std::upper_bound(positions.begin(), positions.end(), offset);
    return it == positions.end() ? static_cast<int>(text.size()) : *it;
}

int Utf8::clampBoundary(const std::string& text, int offset)
{
    const auto positions = boundaries(text);
    const auto it = std::upper_bound(positions.begin(), positions.end(), offset);
    return it == positions.begin() ? 0 : *(it - 1);
}

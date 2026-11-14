#pragma once
#include <string>
#include <vector>

namespace Utf8
{
    std::vector<int> boundaries(const std::string& text);
    int previous(const std::string& text, int offset);
    int next(const std::string& text, int offset);
    int clampBoundary(const std::string& text, int offset);
}

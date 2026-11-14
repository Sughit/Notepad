#pragma once

struct Point
{
    int x = 0;
    int y = 0;
};

struct Rect
{
    int x = 0;
    int y = 0;
    int width = 0;
    int height = 0;

    bool contains(Point point) const
    {
        return point.x >= x && point.x < x + width && point.y >= y && point.y < y + height;
    }
};

struct DocumentPosition
{
    int row = 0;
    int col = 0; 
};


#include "graphics.h"

int main()
{
    initwindow(800, 600, "Test Graphics");

    setcolor(WHITE);
    circle(400, 300, 100);

    setcolor(RED);
    rectangle(100, 100, 300, 200);

    getch();
    closegraph();

    return 0;
}

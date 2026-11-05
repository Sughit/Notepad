#include "RenderWindow.h"

int main()
{
    RenderWindow window = RenderWindow(1920, 1080);

    while (true)
    {
        window.update();

        if (GetAsyncKeyState(VK_ESCAPE) & 1) break;

        delay(16);
    }

    closegraph();
    return 0;
}

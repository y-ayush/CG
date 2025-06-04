#include <graphics.h>
#include <stdio.h>

void SlopeMethod(int x1, int y1, int x2, int y2) {
    float m = (float)(y2 - y1) / (x2 - x1);
    float y;
    int x;

    for (x = x1; x <= x2; x++) {
        y = y1 + m * (x - x1);
        putpixel((int)x, (int) y, WHITE);
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");

    SlopeMethod(100, 100, 300, 250); 

    getch();
    closegraph();
    return 0;
}

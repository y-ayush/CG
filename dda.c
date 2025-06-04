#include <graphics.h>
#include <stdio.h>
#include <math.h>

void DDA(int x1, int y1, int x2, int y2) {
    int dx, dy, steps, i;
    float xIncrement, yIncrement, x, y;

    dx = x2 - x1;
    dy = y2 - y1;

    steps = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);
    xIncrement = (float)dx / steps;
    yIncrement = (float)dy / steps;

    x = x1;
    y = y1;

    for (i = 0; i <= steps; i++) {
	    putpixel((int)(x), (int)(y), RED);
	    x += xIncrement;
	    y += yIncrement;
    }
}

int main() {
    int gd = DETECT, gm;
    int x1,y1,x2,y2;
    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");

    printf("Enter P1( x1, y1) P2( x2, y2): ");
    scanf("%d %d %d %d",&x1,&y1,&x2,&y2);

    DDA(x1,y1,x2,y2);

    getch();
    closegraph();
    return 0;
}

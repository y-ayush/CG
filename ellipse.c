#include <graphics.h>
#include <stdio.h>
#include <math.h>


void putEllispePixel(int xc, int yc, int x, int y){
    putpixel(xc + x, yc + y, WHITE);
    putpixel(xc - x, yc + y, WHITE);
    putpixel(xc + x, yc - y, WHITE);
    putpixel(xc - x, yc - y, WHITE);
}

void drawEllipse(int xc, int yc, int rx, int ry) {
    int x = 0, y = ry;
    long rx2 = rx * rx;
    long ry2 = ry * ry;
    long twoRx2 = 2 * rx2;
    long twoRy2 = 2 * ry2;
    double p;  // decision parameter
    long dx = 0, dy = twoRx2 * y;

    // ----- Region 1 -----
    // Initial decision parameter for region 1
    p = ry2 - (rx2 * ry) + (0.25 * rx2);
    while (dx < dy) {
        // Draw the four symmetric points
        putEllispePixel(xc,yc,x,y);
        x++;
        dx += twoRy2;
        p += ry2 + dx;
        if (p > 0) {
            y--;
            dy -= twoRx2;
            p -=  dy;
        }
    }

    // ----- Region 2 -----
    // Initial decision parameter for region 2
    p = ry2 * (x + 0.5) * (x + 0.5) + rx2 * (y - 1) * (y - 1) - rx2 * ry2;
    while (y >= 0) {
        // Draw the four symmetric points
        putEllispePixel(xc,yc,x,y);

        y--;
        dy -= twoRx2;
        p += rx2 - dy;
        if (p < 0) {
             x++;
            dx += twoRy2;
            p += dx;
        } 
    }
}

int main() {
    int gd = DETECT, gm;
    int x,y,r1,r2;

    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");
    printf("Enter Center(x,y), r1 and r2: ");
    scanf("%d %d %d %d",&x,&y,&r1,&r2);
    drawEllipse(x,y,r1,r2);

    getch();
    closegraph();

    return 0;
}

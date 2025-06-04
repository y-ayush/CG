#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>

void Bresenham(int x1, int y1, int x2, int y2) {
    int dx, dy, D, x, y, sx, sy;

    dx = abs(x2 - x1);
    dy = abs(y2 - y1);
    sx = (x2 > x1) ? 1 : -1;
    sy = (y2 > y1) ? 1 : -1;

    x = x1;
    y = y1;

    D = (dy > dx) ? (2 * dx - dy) : (2 * dy - dx);

   
    if (dx > dy) {
        while (x != x2) {
            putpixel(x, y, RED);
            if (D >= 0) {
                y += sy;
                D -= 2 * dx;
            }
            x += sx;
            D += 2 * dy;
        }
    } 
   
    else {
        while (y != y2) {
            putpixel(x, y, RED);
            if (D >= 0) {
                x += sx;
                D -= 2 * dy;
            }
            y += sy;
            D += 2 * dx;
        }
    }

    putpixel(x, y, RED);
}

int main() {
    int gd = DETECT, gm;
    int x1, y1, x2, y2;
    
    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");

    printf("Enter P1 (x1, y1) P2 (x2, y2): ");
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
    
    Bresenham(x1, y1, x2, y2);

    getch(); 
    closegraph(); 
    return 0;
}

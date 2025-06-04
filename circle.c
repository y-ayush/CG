#include <graphics.h>
#include <stdio.h>

void BresenhamCircle(int xc, int yc, int r) {
    int x = 0, y = r;
    int D = 3 - (2 * r);

    while (x <= y) {
        // Plot all 8 symmetric points 
	putpixel(xc + x, yc + y, RED);
	putpixel(xc - x, yc + y, RED);
	putpixel(xc + x, yc - y, RED);
	putpixel(xc - x, yc - y, RED);
	putpixel(xc + y, yc + x, RED);
	putpixel(xc - y, yc + x, RED);
	putpixel(xc + y, yc - x, RED);
	putpixel(xc - y, yc - x, RED);

        x++;
        if (D > 0) {
            y--;
            D = D + 4 * (x - y) + 10;
        } else {
            D = D + 4 * x + 6;
        }
    }
}

int main() {
    int gd = DETECT, gm;
    int x,y,r;
    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");

    printf("Enter circle Center(x,y) : ");
    scanf("%d %d",&x,&y);

    printf("Enter Radius of circle: ");
    scanf("%d",&r);

    BresenhamCircle(x,y,r);

    getch();
    closegraph();
    return 0;
}

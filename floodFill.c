#include <graphics.h>
#include <stdio.h>


void floodFill(int x, int y, int fill_color, int boundary_color)
{
    int current = getpixel(x, y);
    if (current == boundary_color || current == fill_color)
        return;
    putpixel(x, y, fill_color);
    floodFill(x + 1, y, fill_color, boundary_color);
    floodFill(x - 1, y, fill_color, boundary_color);
    floodFill(x, y + 1, fill_color, boundary_color);
    floodFill(x, y - 1, fill_color, boundary_color);

    return;
    // floodFill(x + 1, y - 1, fill_color, boundary_color);
    // floodFill(x + 1, y + 1, fill_color, boundary_color);
    // floodFill(x - 1, y + 1, fill_color, boundary_color);
    // floodFill(x - 1, y - 1, fill_color, boundary_color);
}

int main(void)
{
    int gd = DETECT, gm;
    int n, i;
    int seed_x, seed_y,r;

 
    int boundary_color = GREEN, fill_color = RED;

    printf("Enter Center Of Circle(x,y) and Radius (r): ");
    scanf("%d%d%d",&seed_x,&seed_y,&r);

    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");

    clrscr();

    setcolor(boundary_color);
    circle(seed_x, seed_y,r);

    floodFill(seed_x, seed_y, fill_color, boundary_color);

    getch();
    closegraph();
    return 0;
}

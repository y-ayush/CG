#include <graphics.h>
#include <stdio.h>

#define MAX 10


void drawPolygon(int points[][2], int n, int color, int xMax, int yMax) {
    int i;
    setcolor(color);
    for (i = 0; i < n - 1; i++) {
        line(points[i][0]+xMax, points[i][1]+yMax, points[i + 1][0]+xMax, points[i + 1][1]+yMax);
    }
    line(points[n - 1][0]+xMax, points[n - 1][1]+yMax, points[0][0]+xMax, points[0][1]+yMax);
}

void mirrorX(int points[][2], int n) {
    int i;
    for (i = 0; i < n; i++) {
        points[i][1] = -points[i][1];
    }
}

void mirrorY(int points[][2], int n) {
    int i;
    for (i = 0; i < n; i++) {
        points[i][0] = -points[i][0];
    }
}

int main() {
    int gd = DETECT, gm;
    int points[MAX][2];
    int n, i, choice, xMax, yMax;

    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");
    xMax = getmaxx() / 2;
    yMax = getmaxy() / 2;

    printf("Enter number of vertices (max %d): ", MAX);
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Vertex %d (x y): ", i + 1);
        scanf("%d %d", &points[i][0], &points[i][1]);
    }

    printf("Mirror across:\n1. X-axis\n2. Y-axis\nEnter choice: ");
    scanf("%d", &choice);

    clrscr();

    line(0, yMax, xMax*2, yMax);
    line(xMax, 0, xMax, yMax*2);

    drawPolygon(points, n, RED, xMax, yMax);

    if (choice == 1) mirrorX(points, n);
    else if (choice == 2) mirrorY(points, n);
    else printf("Invalid choice\n");
      

    drawPolygon(points, n, GREEN, xMax, yMax);
    outtextxy(10, 10, "Mirrored Polygon(green)");
    getch();

    closegraph();
    return 0;
}

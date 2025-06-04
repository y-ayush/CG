#include <graphics.h>
#include <stdio.h>

#define MAX 10

void drawPolygon(int points[][2], int n, int color) {
    int i;
    setcolor(color);
    for (i = 0; i < n - 1; i++) {
        line(points[i][0], points[i][1], points[i + 1][0], points[i + 1][1]);
    }
    line(points[n - 1][0], points[n - 1][1], points[0][0], points[0][1]);
}

void translate(int points[][2], int n, int tx, int ty) {
    int i;
    for (i = 0; i < n; i++) {
        points[i][0] += tx;
        points[i][1] += ty;
    }
}

int main() {
    int gd = DETECT, gm;
    int points[MAX][2];
    int n, i, tx, ty;

    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");

    printf("Enter number of vertices (max %d): ", MAX);
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Vertex %d (x y): ", i + 1);
        scanf("%d %d", &points[i][0], &points[i][1]);
    }

    printf("Enter translation tx ty: ");
    scanf("%d %d", &tx, &ty);

    clrscr();

    drawPolygon(points, n, RED);            // original in RED

    translate(points, n, tx, ty);

    drawPolygon(points, n, WHITE);          // transformed in WHITE

    outtextxy(10, 10, "Original (RED) & Translated (white) Polygon");
    getch();

    closegraph();
    return 0;
}

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

void scale(int points[][2], int n, float sx, float sy) {
    int i;
    for (i = 0; i < n; i++) {
        points[i][0] = (int)(points[i][0] * sx);
        points[i][1] = (int)(points[i][1] * sy);
    }
}

int main() {
    int gd = DETECT, gm;
    int points[MAX][2];
    int n, i;
    float sx, sy;

    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");

    printf("Enter number of vertices (max %d): ", MAX);
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Vertex %d (x y): ", i + 1);
        scanf("%d %d", &points[i][0], &points[i][1]);
    }

    printf("Enter scaling factors sx sy: ");
    scanf("%f %f", &sx, &sy);

    clrscr();

    drawPolygon(points, n, RED);

    scale(points, n, sx, sy);

    drawPolygon(points, n, WHITE);
    outtextxy(10, 10, "Scaled Polygon");
    getch();

    closegraph();
    return 0;
}

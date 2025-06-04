#include <graphics.h>
#include <stdio.h>
#include <math.h>

#define MAX 10
#define PI 3.14159

void drawPolygon(int points[][2], int n, int color) {
    int i;
    setcolor(color);
    for (i = 0; i < n - 1; i++) {
        line(points[i][0], points[i][1], points[i + 1][0], points[i + 1][1]);
    }
    line(points[n - 1][0], points[n - 1][1], points[0][0], points[0][1]);
}

void rotate(int points[][2], int n, float angle_deg) {
    int i;
    float angle = angle_deg * PI / 180.0;
    float cos_a = cos(angle);
    float sin_a = sin(angle);
    int x, y;
    for (i = 0; i < n; i++) {
        x = points[i][0];
        y = points[i][1];
        points[i][0] = (int)(x * cos_a - y * sin_a);
        points[i][1] = (int)(x * sin_a + y * cos_a);
    }
}

int main() {
    int gd = DETECT, gm;
    int points[MAX][2];
    int n, i;
    float angle;

    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");

    printf("Enter number of vertices (max %d): ", MAX);
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Vertex %d (x y): ", i + 1);
        scanf("%d %d", &points[i][0], &points[i][1]);
    }

    printf("Enter rotation angle (degrees): ");
    scanf("%f", &angle);

    drawPolygon(points, n, RED);

    rotate(points, n, angle);

    drawPolygon(points, n, WHITE);
    outtextxy(10, 10, "Rotated Polygon");
    getch();

    closegraph();
    return 0;
}

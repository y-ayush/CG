#include <graphics.h>
#include <stdio.h>

#define MAX 10

void drawPolygon(int points[][2], int n, int color) {
    int i;
    setcolor(color);
    for (i = 0; i < n - 1; i++) line(points[i][0], points[i][1], points[i + 1][0], points[i + 1][1]);
    line(points[n - 1][0], points[n - 1][1], points[0][0], points[0][1]);
}

void shearX(int points[][2], int n, float shx) {
    int i;
    for (i = 0; i < n; i++) points[i][0] = (int)(points[i][0] + shx * points[i][1]);
    
}

void shearY(int points[][2], int n, float shy) {
    int i;
    for (i = 0; i < n; i++) points[i][1] = (int)(points[i][1] + shy * points[i][0]);
    
}

int main() {
    int gd = DETECT, gm;
    int points[MAX][2];
    int n, i, choice;
    float sh;

    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");

    printf("Enter number of vertices (max %d): ", MAX);
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Vertex %d (x y): ", i + 1);
        scanf("%d %d", &points[i][0], &points[i][1]);
    }

    printf("Shear in:\n1. X-direction\n2. Y-direction\nEnter choice: ");
    scanf("%d", &choice);
    printf("Enter shearing factor: ");
    scanf("%f", &sh);

    clrscr();
    drawPolygon(points, n, RED);

    if (choice == 1) shearX(points, n, sh);
    else if (choice == 2) shearY(points, n, sh);
    else printf("Invalid choice");

    drawPolygon(points, n, WHITE);
    outtextxy(10, 10, "Sheared Polygon(white)");
    getch();

    closegraph();
    return 0;
}

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

void translate(int points[][2], int n, int tx, int ty) {
    int i;
    for (i = 0; i < n; i++) {
        points[i][0] += tx;
        points[i][1] += ty;
    }
}

void scale(int points[][2], int n, float sx, float sy) {
    int i;
    for (i = 0; i < n; i++) {
        points[i][0] = (int)(points[i][0] * sx);
        points[i][1] = (int)(points[i][1] * sy);
    }
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

void shearX(int points[][2], int n, float shx) {
    int i;
    for (i = 0; i < n; i++) {
        points[i][0] = (int)(points[i][0] + shx * points[i][1]);
    }
}

void shearY(int points[][2], int n, float shy) {
    int i;
    for (i = 0; i < n; i++) {
        points[i][1] = (int)(points[i][1] + shy * points[i][0]);
    }
}

void copyPolygon(int src[][2], int dest[][2], int n) {
    int i;
    for (i = 0; i < n; i++) {
        dest[i][0] = src[i][0];
        dest[i][1] = src[i][1];
    }
}

int main() {
    int gd = DETECT, gm;
    int original[MAX][2], temp[MAX][2];
    int n, i, tx, ty;
    float sx, sy, angle, shx, shy;

    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");

    printf("Enter number of vertices (max %d): ", MAX);
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Vertex %d (x y): ", i + 1);
        scanf("%d %d", &original[i][0], &original[i][1]);
    }

    // Original Polygon
    copyPolygon(original, temp, n);
    drawPolygon(temp, n, WHITE);
    outtextxy(10, 10, "Original Polygon");
    getch();
    cleardevice();

    // Translation
    copyPolygon(original, temp, n);
    printf("\nEnter translation tx ty: ");
    scanf("%d %d", &tx, &ty);
    translate(temp, n, tx, ty);
    drawPolygon(temp, n, GREEN);
    outtextxy(10, 10, "Translated Polygon");
    getch();
    cleardevice();

    // Scaling
    copyPolygon(original, temp, n);
    printf("\nEnter scaling sx sy: ");
    scanf("%f %f", &sx, &sy);
    scale(temp, n, sx, sy);
    drawPolygon(temp, n, BLUE);
    outtextxy(10, 10, "Scaled Polygon");
    getch();
    cleardevice();

    // Rotation
    copyPolygon(original, temp, n);
    printf("\nEnter angle for rotation (degrees): ");
    scanf("%f", &angle);
    rotate(temp, n, angle);
    drawPolygon(temp, n, CYAN);
    outtextxy(10, 10, "Rotated Polygon");
    getch();
    cleardevice();

    // Mirror X
    copyPolygon(original, temp, n);
    mirrorX(temp, n);
    drawPolygon(temp, n, RED);
    outtextxy(10, 10, "Mirrored across X-axis");
    getch();
    cleardevice();

    // Mirror Y
    copyPolygon(original, temp, n);
    mirrorY(temp, n);
    drawPolygon(temp, n, MAGENTA);
    outtextxy(10, 10, "Mirrored across Y-axis");
    getch();
    cleardevice();

    // Shear X
    copyPolygon(original, temp, n);
    printf("\nEnter shear factor in X (shx): ");
    scanf("%f", &shx);
    shearX(temp, n, shx);
    drawPolygon(temp, n, YELLOW);
    outtextxy(10, 10, "Sheared in X-direction");
    getch();
    cleardevice();

    // Shear Y
    copyPolygon(original, temp, n);
    printf("\nEnter shear factor in Y (shy): ");
    scanf("%f", &shy);
    shearY(temp, n, shy);
    drawPolygon(temp, n, LIGHTBLUE);
    outtextxy(10, 10, "Sheared in Y-direction");
    getch();
    cleardevice();

    closegraph();
    return 0;
}

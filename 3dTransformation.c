#include <graphics.h>
#include <stdio.h>
#include <math.h>

#define PI 3.14159
#define MAX 8

#define SCREEN_CENTER_X (getmaxx() / 2)
#define SCREEN_CENTER_Y (getmaxy() / 2)

typedef struct {
    float x, y, z;
} Point3D;

// Original cube vertices
Point3D originalCube[MAX] = {
    {100, 100, 100},
    {200, 100, 100},
    {200, 200, 100},
    {100, 200, 100},
    {100, 100, 200},
    {200, 100, 200},
    {200, 200, 200},
    {100, 200, 200}
};

void copyCube(Point3D src[], Point3D dest[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        dest[i].x = src[i].x;
        dest[i].y = src[i].y;
        dest[i].z = src[i].z;
    }
}

// Projects a 3D point into 2D isometric view
void project(Point3D p, int *px, int *py) {
    float angleX = 30 * PI / 180;
    float angleY = 30 * PI / 180;
    int x2d = (int)(p.x - p.z * cos(angleY));
    int y2d = (int)(p.y - p.z * sin(angleX));

    *px = SCREEN_CENTER_X + x2d;
    *py = SCREEN_CENTER_Y - y2d;
}


void drawCube(Point3D cube[]) {
    int i, x1, y1, x2, y2;
    
    // Front face
    for (i = 0; i < 4; i++) {
        project(cube[i], &x1, &y1);
        project(cube[(i + 1) % 4], &x2, &y2);
        line(x1, y1, x2, y2);
    }

    // Back face 
    for (i = 4; i < 8; i++) {
        project(cube[i], &x1, &y1);
        project(cube[4 + (i + 1) % 4], &x2, &y2);
        line(x1, y1, x2, y2);
    }

    // Connect front and back 
    for (i = 0; i < 4; i++) {
        project(cube[i], &x1, &y1);
        project(cube[i + 4], &x2, &y2);
        line(x1, y1, x2, y2);
    }
}


void translate(Point3D cube[], float tx, float ty, float tz) {
    int i;
    for (i = 0; i < MAX; i++) {
        cube[i].x += tx;
        cube[i].y += ty;
        cube[i].z += tz;
    }
}

void scale(Point3D cube[], float sx, float sy, float sz) {
    int i;
    for (i = 0; i < MAX; i++) {
        cube[i].x *= sx;
        cube[i].y *= sy;
        cube[i].z *= sz;
    }
}

void rotateX(Point3D cube[], float angle) {
    int i;
    float rad = angle * PI / 180;
    float y, z;
    for (i = 0; i < MAX; i++) {
        y = cube[i].y;
        z = cube[i].z;
        cube[i].y = y * cos(rad) - z * sin(rad);
        cube[i].z = y * sin(rad) + z * cos(rad);
    }
}

void rotateY(Point3D cube[], float angle) {
    int i;
    float rad = angle * PI / 180;
    float x, z;
    for (i = 0; i < MAX; i++) {
        x = cube[i].x;
        z = cube[i].z;
        cube[i].x = x * cos(rad) + z * sin(rad);
        cube[i].z = -x * sin(rad) + z * cos(rad);
    }
}

void rotateZ(Point3D cube[], float angle) {
    int i;
    float rad = angle * PI / 180;
    float x, y;
    for (i = 0; i < MAX; i++) {
        x = cube[i].x;
        y = cube[i].y;
        cube[i].x = x * cos(rad) - y * sin(rad);
        cube[i].y = x * sin(rad) + y * cos(rad);
    }
}

int main() {
    int gd = DETECT, gm;
    float tx, ty, tz;
    float sx, sy, sz;
    float angleX, angleY, angleZ;
    Point3D tempCube[MAX];

    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");

    // Original 
    copyCube(originalCube, tempCube, MAX);
    drawCube(tempCube);
    outtextxy(10, 10, "Original Cube");
    getch();
    cleardevice();

    // Translation 
    copyCube(originalCube, tempCube, MAX);
    printf("Enter translation tx ty tz: "); scanf("%f %f %f", &tx, &ty, &tz);
    translate(tempCube, tx, ty, tz);
    drawCube(tempCube);
    outtextxy(10, 10, "Translated Cube");
    getch();
    cleardevice();

    // Scaling 
    copyCube(originalCube, tempCube, MAX);
    printf("Enter scaling sx sy sz: "); scanf("%f %f %f", &sx, &sy, &sz);
    scale(tempCube, sx, sy, sz);
    drawCube(tempCube);
    outtextxy(10, 10, "Scaled Cube");
    getch();
    cleardevice();

    // Rotation 
    copyCube(originalCube, tempCube, MAX);
    printf("Enter rotation angles X Y Z: "); scanf("%f %f %f", &angleX, &angleY, &angleZ);
    rotateX(tempCube, angleX);
    rotateY(tempCube, angleY);
    rotateZ(tempCube, angleZ);
    drawCube(tempCube);
    outtextxy(10, 10, "Rotated Cube");
    getch();

    closegraph();
    return 0;
}

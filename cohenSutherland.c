#include <graphics.h>
#include <stdio.h>

#define INSIDE 0 // 0000
#define LEFT   1 // 0001
#define RIGHT  2 // 0010
#define BOTTOM 4 // 0100
#define TOP    8 // 1000

// Clipping rectangle
int x_min = 100, y_min = 100, x_max = 300, y_max = 300;

// Compute region code for a point
int computeCode(int x, int y) {
    int code = INSIDE;

    if (x < x_min) code |= LEFT;
    else if (x > x_max) code |= RIGHT;

    if (y < y_min) code |= BOTTOM;
    else if (y > y_max) code |= TOP;

    return code;
}

// Cohen–Sutherland algorithm
void cohenSutherlandClip(int x1, int y1, int x2, int y2) {
    int code1 = computeCode(x1, y1);
    int code2 = computeCode(x2, y2);
    int accept = 0;

    while (1) {
        if ((code1 == 0) && (code2 == 0)) {
            accept = 1;
            break;
        } else if (code1 & code2) {
            break;
        } else {
            int code_out;
            int x, y;

            code_out = code1 ? code1 : code2;

            if (code_out & TOP) {
                x = x1 + (float)(x2 - x1) * (y_max - y1) / (y2 - y1);
                y = y_max;
            } else if (code_out & BOTTOM) {
                x = x1 + (float)(x2 - x1) * (y_min - y1) / (y2 - y1);
                y = y_min;
            } else if (code_out & RIGHT) {
                y = y1 + (float)(y2 - y1) * (x_max - x1) / (x2 - x1);
                x = x_max;
            } else if (code_out & LEFT) {
                y = y1 + (float)(y2 - y1) * (x_min - x1) / (x2 - x1);
                x = x_min;
            }

            if (code_out == code1) {
                x1 = x;
                y1 = y;
                code1 = computeCode(x1, y1);
            } else {
                x2 = x;
                y2 = y;
                code2 = computeCode(x2, y2);
            }
        }
    }

    if (accept) {
        setcolor(GREEN);
        line(x1, y1, x2, y2);
    } else {
        setcolor(RED);
        line(x1, y1, x2, y2);       // rejected line
    }
}

int main() {
    int gd = DETECT, gm;
    int x1, y1, x2, y2;

    // Initialize graphics (use correct path to BGI directory)
    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");

    // Draw clipping window
    setcolor(WHITE);
    rectangle(x_min, y_min, x_max, y_max);

    printf("Clipping boundaries:\n x_min = %d\n y_min = %d\n x_max = %d\n y_max = %d\n", x_min, y_min, x_max, y_max);
    printf("Enter line endpoints (x1 y1 x2 y2): ");
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);

    // Draw original line
    setcolor(RED);
    line(x1, y1, x2, y2);

    getch();
    cleardevice();

    // Draw clipping window again
    setcolor(WHITE);
    rectangle(x_min, y_min, x_max, y_max);

    // Perform clipping
    cohenSutherlandClip(x1, y1, x2, y2);

    getch();
    closegraph();
    return 0;
}

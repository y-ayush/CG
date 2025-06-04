  #include <graphics.h>
#include <stdio.h>
#include <conio.h>

#define MAX 20

typedef struct {
    int x, y;
} Point;

int n;
Point input[MAX], output[MAX];

// Check if point is inside the clipping boundary
int inside(Point p, int edge, char boundary) {
    switch (boundary) {
        case 'l': return p.x >= edge;
        case 'r': return p.x <= edge;
        case 'b': return p.y >= edge;
        case 't': return p.y <= edge;
    }
    return 0;
}

// Get intersection point of edge and polygon edge
Point intersection(Point p1, Point p2, int edge, char boundary) {
    Point i;
    float m;

    if (p2.x - p1.x != 0)
        m = (float)(p2.y - p1.y) / (p2.x - p1.x);
    else
        m = 1e5; // Large number to avoid divide by 0

    switch (boundary) {
        case 'l':
            i.x = edge;
            i.y = p1.y + (edge - p1.x) * m;
            break;
        case 'r':
            i.x = edge;
            i.y = p1.y + (edge - p1.x) * m;
            break;
        case 'b':
            i.y = edge;
            if (m != 0)
                i.x = p1.x + (edge - p1.y) / m;
            else
                i.x = p1.x;
            break;
        case 't':
            i.y = edge;
            if (m != 0)
                i.x = p1.x + (edge - p1.y) / m;
            else
                i.x = p1.x;
            break;
    }
    return i;
}

// Clip polygon with one boundary
void clip(Point* in, int inCount, Point* out, int* outCount, int edge, char boundary) {
    Point s, p;
    int i;
    *outCount = 0;

    for (i = 0; i < inCount; i++) {

        int s_in, p_in;
        s = in[i];
        p = in[(i + 1) % inCount];

        s_in = inside(s, edge, boundary);
        p_in = inside(p, edge, boundary);

        if (s_in && p_in) {
            out[(*outCount)++] = p;
        } else if (s_in && !p_in) {
            out[(*outCount)++] = intersection(s, p, edge, boundary);
        } else if (!s_in && p_in) {
            out[(*outCount)++] = intersection(s, p, edge, boundary);
            out[(*outCount)++] = p;
        }
    }
}

// Sutherland-Hodgman Clipping Logic
void sutherlandHodgman(Point poly[], int n, int xmin, int ymin, int xmax, int ymax) {
    Point temp1[MAX], temp2[MAX];
    int count1 = n, count2, i;

    for (i = 0; i < n; i++)
        temp1[i] = poly[i];

    clip(temp1, count1, temp2, &count2, xmin, 'l');
    clip(temp2, count2, temp1, &count1, xmax, 'r');
    clip(temp1, count1, temp2, &count2, ymin, 'b');
    clip(temp2, count2, temp1, &count1, ymax, 't');

    // Draw final polygon
    setcolor(WHITE);
    for (i = 0; i < count1; i++) {
        line(temp1[i].x, temp1[i].y, temp1[(i + 1) % count1].x, temp1[(i + 1) % count1].y);
    }
    outtextxy(xmin + 5, ymin - 15, "Clipped Polygon (white)");
}

int main() {
    int gd = DETECT, gm;
    int i;
    int xmin = 100, ymin = 200, xmax = 300, ymax =400 ;

    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");

    printf("Cliping Boundarys\n x_min = %d\n y_min = %d\n x_max = %d\n y_max = %d\n", xmin, ymin, xmax, ymax);
    printf("Enter number of polygon vertices: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter vertex %d (x y): ", i + 1);
        scanf("%d %d", &input[i].x, &input[i].y);
    }

    // Draw clipping window
    setcolor(YELLOW);
    rectangle(xmin, ymin, xmax, ymax);
    outtextxy(xmin, ymin - 15, "Clipping Window");

    // Draw original polygon
    setcolor(RED);
    for (i = 0; i < n; i++) {
        line(input[i].x, input[i].y, input[(i + 1) % n].x, input[(i + 1) % n].y);
    }

    getch();
    cleardevice();

    // Redraw window
    setcolor(YELLOW);
    rectangle(xmin, ymin, xmax, ymax);

    // Perform clipping
    sutherlandHodgman(input, n, xmin, ymin, xmax, ymax);

    getch();
    closegraph();
    return 0;
}

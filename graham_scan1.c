#include <stdio.h>
#include <time.h>
#include <math.h>

void swapPoints(Point pts[], int i, int j) {
    Point temp = pts[i];
    pts[i] = pts[j];
    pts[j] = temp;
}

int findAnchor(Point pts[], int n) {
    int index = 0;
    for (int i = 1; i < n; i++) {
        if (pts[i].y < pts[index].y ||
           (fabs(pts[i].y - pts[index].y) < EPSILON && pts[i].x < pts[index].x)) {
            index = i;
        }
    }
    return index;
}

int graham_scan1(Point pts[], int n, Point hull[]) {
    int anchorIndex = findAnchor(pts, n);
    if (anchorIndex != 0) {
        swapPoints(pts, 0, anchorIndex);
    }

    Polar polarArr[MAX_POINT_COUNT];
    Point *subPts = pts + 1;
    polarAngle(subPts, polarArr, pts[0], n - 1);
    bubbleSortWithPoints(subPts, polarArr, n - 1);

    Stack S;
    CREATE(&S);
    PUSH(&S, pts[0]);
    PUSH(&S, pts[1]);
    PUSH(&S, pts[2]);

    for (int i = 3; i < n; i++) {
        Point top = POP(&S);
        while (!ISEMPTY(&S) &&
               orientation(TOP(&S), top, pts[i]) <= 0) {
            top = POP(&S);
        }
        PUSH(&S, top);
        PUSH(&S, pts[i]);
    }

    return GET_STACK(&S, hull);
}

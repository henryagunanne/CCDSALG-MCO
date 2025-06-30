

#include "sort.h"


void polarAngle(Point pts[], Polar polarArr[], Point anchor, int n) {
    for (int i = 0; i < n; i++) {
        double dx = pts[i].x - anchor.x;
        double dy = pts[i].y - anchor.y;
        polarArr[i].r = sqrt(dx * dx + dy * dy);
        polarArr[i].theta = atan2(dy, dx) * (180.0 / M_PI);
    }
}

double orientation(Point p, Point q, Point r) {
    return (q.x - p.x) * (r.y - q.y) - (q.y - p.y) * (r.x - q.x);
}

void bubbleSortWithPoints(Point pts[], Polar polarArr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (polarArr[j].theta > polarArr[j + 1].theta) {
                Polar tempP = polarArr[j];
                polarArr[j] = polarArr[j + 1];
                polarArr[j + 1] = tempP;

                Point tempPt = pts[j];
                pts[j] = pts[j + 1];
                pts[j + 1] = tempPt;
            }
        }
    }
}

void heapify(Polar polarArr[], Point pts[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && polarArr[left].theta > polarArr[largest].theta) {
        largest = left;
    }
    if (right < n && polarArr[right].theta > polarArr[largest].theta) {
        largest = right;
    }

    if (largest != i) {
        Polar tempP = polarArr[i];
        polarArr[i] = polarArr[largest];
        polarArr[largest] = tempP;

        Point tempPt = pts[i];
        pts[i] = pts[largest];
        pts[largest] = tempPt;

        heapify(polarArr, pts, n, largest);
    }
}

void heapSortWithPoints(Point pts[], Polar polarArr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(polarArr, pts, n, i);
    }
    for (int i = n - 1; i > 0; i--) {
        Polar tempP = polarArr[0];
        polarArr[0] = polarArr[i];
        polarArr[i] = tempP;

        Point tempPt = pts[0];
        pts[0] = pts[i];
        pts[i] = tempPt;

        heapify(polarArr, pts, i, 0);
    }
}

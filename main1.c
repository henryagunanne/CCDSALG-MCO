/**
 * Programmer: [Your Name]
 * Code Tester: [Tester's Name]
 * 
 * Description: Driver program for testing graham_scan2 (uses heap sort).
 */

#include <stdio.h>
#include "point.h"
#include "stack.h"
#include "sort.h"

#include "graham_scan1.c"

int graham_scan1(Point pts[], int n, Point hull[]);

int main() {
    FILE *fin = fopen("input-circle.txt", "r");
    if (!fin) return 1;

    int n;
    if (fscanf(fin, "%d", &n) != 1) {
        fclose(fin);
        return 1;
    }

    if (n < 1 || n > MAX_POINT_COUNT) {
        fclose(fin);
        return 1;
    }

    Point pts[MAX_POINT_COUNT];
    for (int i = 0; i < n; i++) {
        if (fscanf(fin, "%lf %lf", &pts[i].x, &pts[i].y) != 2) {
            fclose(fin);
            return 1;
        }
    }
    fclose(fin);

    Point hull[MAX_POINT_COUNT];
    int m;

    if (n < 3) {
        for (int i = 0; i < n; i++) {
            hull[i] = pts[i];
        }
        m = n;
    } else {
        m = graham_scan1(pts, n, hull);
    }

    printf("%d\n", m);
    for (int i = 0; i < m; i++) {
        printf("%.6f %.6f\n", hull[i].x, hull[i].y);
    }

    return 0;
}

/**
 * Programmer: [Your Name]
 * Code Tester: [Tester's Name]
 * 
 * Description: Graham Scan implementation using Bubble Sort for convex hull.
 */

#include "graham_scan1.h"


/**
 * @brief Swaps two points in an array.
 *
 * @param pts Array of points.
 * @param i Index of the first point.
 * @param j Index of the second point.
 */
void swapPoints(Point pts[], int i, int j) {
    Point temp = pts[i];
    pts[i] = pts[j];
    pts[j] = temp;
}


/**
 * @brief Finds the anchor point: the point with the lowest y-coordinate (and lowest x if tied).
 *
 * This point will serve as the reference for polar angle sorting.
 *
 * @param pts Array of input points.
 * @param n Number of points.
 * @return Index of the anchor point.
 */
int findAnchor(Point pts[], int n) {
    int index = 0;
    for (int i = 1; i < n; i++) {
        // If current point is lower in y or same y but lower in x, update anchor
        if (pts[i].y < pts[index].y ||
           (fabs(pts[i].y - pts[index].y) < EPSILON && pts[i].x < pts[index].x)) {
            index = i;
        }
    }
    return index;
}


/**
 * @brief Computes the convex hull of a set of 2D points using the Graham Scan algorithm.
 *
 *  Assumes the input array has at least 3 points.
 *
 * @param pts Array of input points (may be reordered during execution).
 * @param n Number of input points.
 * @param hull Output array containing the points on the convex hull in counter-clockwise order.
 * @return Number of points in the convex hull.
 */
void graham_scan1(Point pts[], int n, Point hull[]) {

    clock_t start = clock();

    // Step 1: Find anchor point and move it to index 0
    int anchorIndex = findAnchor(pts, n);
    if (anchorIndex != 0) {
        swapPoints(pts, 0, anchorIndex);
    }

    // Step 2: Convert remaining points to polar coordinates with respect to anchor
    Polar polarArr[MAX_POINT_COUNT];
    Point *subPts = pts + 1;    // exclude the anchor point
    polarAngle(subPts, polarArr, pts[0], n - 1);

    // Step 3: Sort the remaining points based on their angle
    bubbleSortWithPoints(subPts, polarArr, n - 1);

    // Step 4: Initialize stack with first three points
    Stack S;
    CREATE(&S);
    PUSH(&S, pts[0]);    // anchor
    PUSH(&S, pts[1]);
    PUSH(&S, pts[2]);

    // Step 5: Process remaining points
    for (int i = 3; i < n; i++) {
        Point top = POP(&S);

        // Remove top while the turn formed by (next_to_top, top, pts[i]) is not counter-clockwise
        while (!ISEMPTY(&S) &&
               orientation(TOP(&S), top, pts[i]) <= 0) {
            top = POP(&S);
        }
        PUSH(&S, top);
        PUSH(&S, pts[i]);
    }

    // Step 6: Time measurement complete
    clock_t end = clock();  // End timing
    double elapsed = ((double)(end - start)) * 1000.0 / CLOCKS_PER_SEC;
    printf("Elapsed time (Bubble Sort): %.3f ms\n", elapsed);

    
    // return GET_STACK(&S, hull);
}

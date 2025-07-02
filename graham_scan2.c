/**
 * Programmer: [Your Name]
 * Code Tester: [Tester's Name]
 * 
 * Description: Graham Scan implementation using Heap Sort for convex hull. Outputs to file.
 */

#include <stdio.h>
#include <time.h>
#include "sort.h"
#include "stack.h"


/**
 * @brief Finds the index of the anchor point (lowest y, then lowest x if tied).
 * 
 * @param pts Array of input points.
 * @param n Number of points in the array.
 * @return Index of the anchor point.
 */
int findAnchorPoint(Point pts[], int n){
    
    int index = 0;
    int i;
    
    for (i = 1; i < n; i++){
        if (pts[i].y < pts[index].y)
            index = i;
        else if (pts[i].y == pts[index].y){
            if(pts[i].x < pts[index].x)
                index = i;
        }
    }
    return index;
}


/**
 * @brief Swaps two points in the array.
 * 
 * @param pts Array of points.
 * @param i Index of the first point.
 * @param j Index of the second point.
 */
void swapPoints(Point pts[], int i, int j){
    Point temp = pts[i];
    pts[i] = pts[j];
    pts[j] = temp;
}


/**
 * @brief Computes the convex hull using the Graham Scan algorithm with Heap Sort.
 * 
 * Outputs the result to a given file and prints execution time to stdout.
 * 
 * @param pts Array of input points (may be modified).
 * @param n Number of input points.
 * @param fout File pointer for output (convex hull points will be written here).
 */
void graham_scan2 (Point pts[], int n, FILE *fout){
    
    clock_t start = clock();
    
    // Step 1: Find anchor point (lowest y, then x) and swap to front
    int anchorIndex = findAnchorPoint(pts, n);
    swapPoints(pts, 0, anchorIndex);
    Point anchor = pts[0];
    
    // Step 2: Compute polar angle and distance from anchor
    Polar polarArr[MAX_POINT_COUNT];
    polarAngle(pts, polarArr, anchor, n);
    
    // Step 3: Sort points by polar angle using heap sort
    heapSortWithPoints(pts, polarArr, n);
    
    // Step 4: Initialize stack with first three sorted points
    Stack hull;
    CREATE(&hull);
    PUSH(&hull, pts[0]);
    PUSH(&hull, pts[1]);
    PUSH(&hull, pts[2]);
    
    // Step 5: Process remaining points
    for (int i = 3; i < n; i++) {
        // Remove top of stack while we don't make a left turn
        while (hull.topIndex >= 1 &&
               orientation(NEXT_TO_TOP(&hull), TOP(&hull), pts[i]) <= 0) {
            POP(&hull);
        }
        PUSH(&hull, pts[i]);
    }
    
    // Step 6: Time measurement complete
    clock_t end = clock();  // End timing
    double elapsed = ((double)(end - start)) * 1000.0 / CLOCKS_PER_SEC;
    printf("Elapsed time (Heap Sort): %.3f ms\n", elapsed);
    
    // Step 7: Write results to output file
    fprintf(fout, "%d\n",n);
        Point result[MAX_POINT_COUNT];
        int count = GET_STACK(&hull, result);
        for (int i = 0; i < count; i++) {
            fprintf(fout, "%.6f  %.6f\n", result[i].x, result[i].y);
        }


}

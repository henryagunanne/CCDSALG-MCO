/**
 * Programmer: [Your Name]
 * Code Tester: [Tester's Name]
 * 
 * Description: Polar angle calculation and sorting algorithms (bubble and heap sort).
 */


#include "sort.h"

/**
 * @brief Converts each point to its polar coordinates relative to an anchor point.
 * 
 * The angle is computed in degrees using atan2, and distance (r) is calculated via Euclidean norm.
 * 
 * @param pts Array of input points.
 * @param polarArr Output array of polar coordinates.
 * @param anchor The reference point from which angles/distances are measured.
 * @param n Number of points.
 */
void polarAngle(Point pts[], Polar polarArr[], Point anchor, int n) {
    for (int i = 0; i < n; i++) {
        double dx = pts[i].x - anchor.x;
        double dy = pts[i].y - anchor.y;

        // Distance from anchor
        polarArr[i].r = sqrt(dx * dx + dy * dy);

        // Angle (in degrees) from anchor to point
        polarArr[i].theta = atan2(dy, dx) * (180.0 / M_PI);
    }
}


/**
 * @brief Returns the orientation of the ordered triplet (p, q, r).
 * 
 * Uses a determinant-based cross product to find orientation.
 * 
 * @param p First point.
 * @param q Second point.
 * @param r Third point.
 * @return A positive value for counter-clockwise, negative for clockwise, and 0 for colinear.
 */
double orientation(Point p, Point q, Point r) {
    double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (fabs(val) < EPSILON) return 0;     // colinear
    return (val > 0) ? 1 : -1;              // clockwise or counter-clockwise
}


/**
 * @brief Sorts points and their corresponding polar coordinates by angle using bubble sort.
 * 
 * @param pts Array of points to sort.
 * @param polarArr Corresponding polar coordinates.
 * @param n Number of points.
 */
void bubbleSortWithPoints(Point pts[], Polar polarArr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (polarArr[j].theta > polarArr[j + 1].theta) {
                 // Swap polar coordinates
                Polar tempP = polarArr[j];
                polarArr[j] = polarArr[j + 1];
                polarArr[j + 1] = tempP;

                // Swap corresponding points
                Point tempPt = pts[j];
                pts[j] = pts[j + 1];
                pts[j + 1] = tempPt;
            }
        }
    }
}



/**
 * @brief Maintains the max heap property for heap sort based on polar angle.
 * 
 * @param polarArr Array of polar coordinates.
 * @param pts Array of points corresponding to polarArr.
 * @param n Size of the heap.
 * @param i Index of the current root to heapify.
 */
void heapify(Polar polarArr[], Point pts[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // Compare left child
    if (left < n && polarArr[left].theta > polarArr[largest].theta) {
        largest = left;
    }
    // Compare right child
    if (right < n && polarArr[right].theta > polarArr[largest].theta) {
        largest = right;
    }

    // If root is not largest, swap and heapify
    if (largest != i) {
        // Swap polar angles
        Polar tempP = polarArr[i];
        polarArr[i] = polarArr[largest];
        polarArr[largest] = tempP;

        // Swap points
        Point tempPt = pts[i];
        pts[i] = pts[largest];
        pts[largest] = tempPt;

        // Recursive heapify
        heapify(polarArr, pts, n, largest);
    }
}


/**
 * @brief Sorts points and their polar angles using heap sort based on angle.
 * 
 * @param pts Array of points to sort.
 * @param polarArr Array of polar coordinates.
 * @param n Number of elements.
 */
void heapSortWithPoints(Point pts[], Polar polarArr[], int n) {
    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(polarArr, pts, n, i);
    }

    // Extract elements from heap one by one
    for (int i = n - 1; i > 0; i--) {
        // Move current root (largest) to end
        Polar tempP = polarArr[0];
        polarArr[0] = polarArr[i];
        polarArr[i] = tempP;

        Point tempPt = pts[0];
        pts[0] = pts[i];
        pts[i] = tempPt;

        // Heapify reduced heap
        heapify(polarArr, pts, i, 0);
    }
}

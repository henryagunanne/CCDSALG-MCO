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

#include "graham_scan1.h"

int graham_scan1(Point pts[], int n, Point hull[]);

int main() {
    char inputFile[100];
    char outputFile[200];
    FILE *fIn, *fOut;
    int n, m;

    // Ask for input filename
    printf("Enter the input filename (e.g., MYDATA.TXT): ");
    scanf("%s", inputFile);

    // Ask for output filename
    printf("Enter the output filename (e.g., MYHULL.TXT): ");
    scanf("%s", outputFile);

    // Open input file
    fIn = fopen(inputFile, "r");
    while (fIn == NULL) {
        fprintf(stderr, "Error: Cannot open input file.\n");
        printf("Try Entering Another File Name!(eg.Filename.txt): ");
        scanf("%s", inputFile);
        fIn = fopen(inputFile, "r");
    }

    // Read points from input file
    Point pts[MAX_POINT_COUNT];
    if (fscanf(fIn, "%d", &n) != 1) {
        fclose(fIn);
        return 1;
    }

    if (n < 1 || n > MAX_POINT_COUNT) {
        fclose(fIn);
        return 1;
    }

    // Read the rest of the file 
    for (int i = 0; i < n; i++) {
        if (fscanf(fIn, "%lf %lf", &pts[i].x, &pts[i].y) != 2) {
            fclose(fIn);
            return 1;
        }
    }
    fclose(fIn);

    // Call graham_scan1
    Point hull[MAX_POINT_COUNT];

    if (n < 3) {
        for (int i = 0; i < n; i++) {
            hull[i] = pts[i];
        }
        m = n;
    } else {
        m = graham_scan1(pts, n, hull);
    }

    // Write result to output file
    fOut = fopen(outputFile, "w");

    fprintf(fOut, "%d\n", m);
    for (int i = 0; i < m; i++) {
        fprintf(fOut, "%.6f %.6f\n", hull[i].x, hull[i].y);
    }

    fclose(fOut);
    printf("Convex hull written to %s\n", outputFile);
    
    return 0;
}

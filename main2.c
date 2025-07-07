/**
 * Programmer: Agunanne Henry, Lu Qinpei
 * Code Tester: Agunanne Henry, Lu Qinpei
 * 
 * Description: Driver program for testing graham_scan2 (uses Heap sort).
 */

#include <stdio.h>
#include "graham_scan2.h"

int main() {
    FILE *fIn, *fOut;
    int n;
    Point pts[MAX_POINT_COUNT];
    char inputFile[100];
    char outputFile[100];
    int i;
    
    // Ask for input filename
    printf("Enter the input filename (e.g., MYDATA.TXT): ");
    scanf("%s", inputFile);

    // Ask for output filename
    printf("Enter the output filename (e.g., MYHULL.TXT): ");
    scanf("%s", outputFile);

    fIn = fopen(inputFile, "r");
    while (fIn == NULL) {
        fprintf(stderr, "Error: Cannot open input file.\n");
        printf("Try Entering Another File Name!(eg.Filename.txt): ");
        scanf("%s", inputFile);
        fIn = fopen(inputFile, "r");
    }
    
    // Read points from the input file
    fscanf(fIn, "%d", &n);
    for (i = 0; i < n; i++) {
        fscanf(fIn, "%lf %lf", &pts[i].x, &pts[i].y);
    }
    fclose(fIn);
    
    fOut = fopen(outputFile, "w");
    graham_scan2(pts, n, fOut);

    fclose(fOut);
    
    printf("Convex hull written to %s\n", outputFile);

    return 0;
}

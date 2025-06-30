
#include <stdio.h>
#include "stack.h"
#include "sort.h"
#include "graham_scan2.h"

int main() {
    FILE *fin, *fout;
    int n;
    Point pts[MAX_POINT_COUNT];
    char inputFile[21] = "input-circle.txt";
    int i;
    
    fin = fopen(inputFile, "r");
    while (fin == NULL) {
        printf("Error: Cannot open input file.\n");
        printf("Try Entering Another File Name!(eg.Filename.txt)\n");
        scanf("%s", inputFile);
        fin = fopen(inputFile, "r");
    }
    
    fscanf(fin, "%d", &n);
    for (i = 0; i < n; i++) {
        fscanf(fin, "%lf %lf", &pts[i].x, &pts[i].y);
    }
    fclose(fin);
    
    fout = fopen("output-circle.txt","w");
    graham_scan2(pts, n, fout);
    fclose(fout);
    
    printf("Convex hull written to output.txt\n");

    return 0;
    
}

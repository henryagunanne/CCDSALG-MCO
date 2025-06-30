#include "graham_scan2.h"

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


void swapPoints(Point pts[], int i, int j){
    Point temp = pts[i];
    pts[i] = pts[j];
    pts[j] = temp;
}

void graham_scan2 (Point pts[], int n, FILE *fout){
    
    clock_t start = clock();
    
    int anchorIndex = findAnchorPoint(pts, n);
    
    swapPoints(pts, 0, anchorIndex);
    
    Point anchor = pts[0];
    
    Polar polarArr[MAX_POINT_COUNT];
    
    polarAngle(pts, polarArr, anchor, n);
    
    heapSortWithPoints(pts, polarArr, n);
    
    Stack hull;
    CREATE(&hull);
    PUSH(&hull, pts[0]);
    PUSH(&hull, pts[1]);
    PUSH(&hull, pts[2]);
    
    
    for (int i = 3; i < n; i++) {
        while (hull.topIndex >= 1 &&
               orientation(NEXT_TO_TOP(&hull), TOP(&hull), pts[i]) <= 0) {
            POP(&hull);
        }
        PUSH(&hull, pts[i]);
    }
    
    clock_t end = clock();  // End timing
    double elapsed = ((double)(end - start)) * 1000.0 / CLOCKS_PER_SEC;
    printf("Elapsed time (Heap Sort): %.3f ms\n", elapsed);
    
    fprintf(fout, "%d\n",n);
        Point result[MAX_POINT_COUNT];
        int count = GET_STACK(&hull, result);
        for (int i = 0; i < count; i++) {
            fprintf(fout, "%.6f  %.6f\n", result[i].x, result[i].y);
        }


}

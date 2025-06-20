#include <math.h>
#include "sort.h"


void polarAngle(Point points[], Polar polarArr[], Point anchor, int n) {
    for (int i = 0; i < n; i++) {
        double dx = points[i].x - anchor.x;
        double dy = points[i].y - anchor.y;
        polarArr[i].r = sqrt(dx*dx + dy*dy);
        polarArr[i].theta = atan2(dy, dx) * (180.0 / M_PI);
    }
} 


void bubbleSortWithPoints(Point points[], Polar polarArr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (polarArr[j].theta > polarArr[j+1].theta) {
              
                Polar tmpP = polarArr[j];
                polarArr[j] = polarArr[j+1];
                polarArr[j+1] = tmpP;
                
                Point tmpPt = points[j];
                points[j] = points[j+1];
                points[j+1] = tmpPt;
            }
        }
    }
}

static void heapifyPoints(Polar polarArr[], Point points[], int n, int i) {
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if (left < n && polarArr[left].theta > polarArr[largest].theta) {
        largest = left;
    }
    if (right < n && polarArr[right].theta > polarArr[largest].theta) {
        largest = right;
    }
    if (largest != i) {
       
        Polar tmpP = polarArr[i];
        polarArr[i] = polarArr[largest];
        polarArr[largest] = tmpP;
        
        Point tmpPt = points[i];
        points[i] = points[largest];
        points[largest] = tmpPt;

        heapifyPoints(polarArr, points, n, largest);
    }
}

void heapSortWithPoints(Point points[], Polar polarArr[], int n) {
    if (n <= 1) return;

    
    for (int i = n/2 - 1; i >= 0; i--) {
        heapifyPoints(polarArr, points, n, i);
    }
   
    for (int i = n - 1; i > 0; i--) {
    	
        Polar tmpP = polarArr[0];
        polarArr[0] = polarArr[i];
        polarArr[i] = tmpP;
        Point tmpPt = points[0];
        points[0] = points[i];
        points[i] = tmpPt;
        
        heapifyPoints(polarArr, points, i, 0);
    }
}
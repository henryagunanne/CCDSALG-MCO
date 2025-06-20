
#include "point.h"

typedef struct {
    double r;
    double theta;
} Polar;

void polarAngle(Point points[], Polar polarArr[], Point anchor, int n);

void bubbleSortWithPoints(Point points[], Polar polarArr[], int n);

void heapSortWithPoints(Point points[], Polar polarArr[], int n); 
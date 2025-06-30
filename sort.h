#ifndef POLAR_H
#define POLAR_H

#include <math.h>
#include "point.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef struct {
    double r;
    double theta;
} Polar;


void polarAngle(Point pts[], Polar polarArr[], Point anchor, int n);


void bubbleSortWithPoints(Point pts[], Polar polarArr[], int n);


void heapSortWithPoints(Point pts[], Polar polarArr[], int n);


double orientation(Point p, Point q, Point r);

#endif

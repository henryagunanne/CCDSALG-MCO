#include <stdio.h>
#include <time.h>
#include <math.h>
#include "sort.h"
#include "stack.h"


void swapPoints(Point pts[], int i, int j);

int findAnchor(Point pts[], int n);

int graham_scan1(Point pts[], int n, Point hull[]);

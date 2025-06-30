#include <stdio.h>
#include <time.h>
#include "sort.h"
#include "stack.h"

int findAnchorPoint(Point pts[], int n);

void swapPoints(Point pts[], int i, int j);

void graham_scan2 (Point pts[], int n, FILE *fout);

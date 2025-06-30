
typedef struct {
    double r;
    double theta;
} Polar;


void polarAngle(Point pts[], Polar polarArr[], Point anchor, int n);


void bubbleSortWithPoints(Point pts[], Polar polarArr[], int n);


void heapSortWithPoints(Point pts[], Polar polarArr[], int n);


double orientation(Point p, Point q, Point r);

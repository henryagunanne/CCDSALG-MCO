/**
 * Programmer: Inocencio Chazwick, Lu Qinpei
 * Code Tester: Agunanne Henry
 * 
 * Description: Header for polar angle calculations and sorting utilities.
 */


#ifndef POLAR_H
#define POLAR_H

/// @file polar.h
/// @brief Provides structures and functions for converting points to polar coordinates and sorting them based on angles.

#include <math.h>
#include "point.h"

/// @def M_PI
/// @brief Defines π (pi) if not already defined by the math library.
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


/**
 * @struct Polar
 * @brief Represents a point in polar coordinates.
 * 
 * Consists of a radius (r) and an angle (theta) in radians.
 */
typedef struct {
    double r;      ///< Distance from the origin (radius).
    double theta;  ///< Angle in radians relative to the x-axis. 
} Polar;


// ----------------- Function Prototypes -----------------
void polarAngle(Point pts[], Polar polarArr[], Point anchor, int n);


void bubbleSortWithPoints(Point pts[], Polar polarArr[], int n);


void heapSortWithPoints(Point pts[], Polar polarArr[], int n);


double orientation(Point p, Point q, Point r);

#endif

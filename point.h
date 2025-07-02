/**
 * Programmer: [Your Name]
 * Code Tester: [Tester's Name]
 * 
 * Description: Header file defining the Point struct and constants.
 */

#ifndef POINT_H
#define POINT_H

/// @file point.h
/// @brief Defines a 2D point structure and related constants for geometric operations.

/// @def MAX_POINT_COUNT
/// @brief Maximum number of points allowed. Set to 2^15 (32768).
#define MAX_POINT_COUNT (1 << 15)

/// @def EPSILON
/// @brief A small threshold value used for floating-point comparisons.
#define EPSILON 1e-9


/**
 * @struct Point
 * @brief Represents a point in 2D Cartesian space.
 *
 * This structure stores the coordinates of a point using double precision.
 */
typedef struct {
    double x; ///< The x-coordinate of the point.
    double y; ///< The y-coordinate of the point.
} Point;

#endif

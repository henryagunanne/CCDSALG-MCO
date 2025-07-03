/**
 * Programmer: [Your Name]
 * Code Tester: [Tester's Name]
 * 
 * Description: Stack implementation header for storing Point data.
 */

#ifndef STACK_H
#define STACK_H

/// @file stack.h
/// @brief Defines a stack structure and operations for storing 2D points.

#include <stdio.h>
#include "point.h"  // Include definition for Point and MAX_POINT_COUNT


/**
 * @struct Stack
 * @brief A stack data structure for storing Points.
 *
 * This stack supports typical LIFO operations such as push, pop, and top.
 */
typedef struct {
    Point items[MAX_POINT_COUNT]; ///< Array to hold stack elements.
    int topIndex;                 ///< Index of the top element in the stack.
} Stack;

// Function Prototypes
void CREATE(Stack *S);
int ISEMPTY(Stack *S);
int ISFULL(Stack *S);
void PUSH(Stack *S, Point elem);
Point POP(Stack *S);
Point TOP(Stack *S);
Point NEXT_TO_TOP(Stack *S);
int GET_STACK(Stack *S, Point outArray[]);

#endif

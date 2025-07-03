/**
 * Programmer: [Your Name]
 * Code Tester: [Tester's Name]
 * 
 * Description: Stack implementation source file for managing Point data.
 */

#include "stack.h"

/**
 * @brief Initializes the stack to an empty state.
 * 
 * Sets the top index to -1, indicating the stack is empty.
 */
void CREATE(Stack *S) {
    S->topIndex = -1;
}


/**
 * @brief Checks if the stack is empty.
 * 
 * @param S Pointer to the stack.
 * @return 1 if empty, 0 otherwise.
 */
int ISEMPTY(Stack *S) {
    if (S->topIndex < 0) {
        fprintf(stderr, "Stack underflow\n");
        return 1;
    } else {
        return 0;
    }
}


/**
 * @brief Checks if the stack is full.
 * 
 * @param S Pointer to the stack.
 * @return 1 if full, 0 otherwise.
 */
int ISFULL(Stack *S) {
    if (S->topIndex >= MAX_POINT_COUNT - 1) {
        fprintf(stderr, "Stack Overflow\n");
        return 1;
    } else {
        return 0;
    }
}


/**
 * @brief Pushes a Point element onto the stack.
 * 
 * If the stack is not full, the element is added at the top.
 * 
 * @param S Pointer to the stack.
 * @param elem The Point to push onto the stack.
 */
void PUSH(Stack *S, Point elem) {
    if (!ISFULL(S)) {
        S->items[++S->topIndex] = elem;
    }
}


/**
 * @brief Pops and returns the top element of the stack.
 * 
 * Returns a default (0.0, 0.0) Point if the stack is empty.
 * 
 * @param S Pointer to the stack.
 * @return The Point at the top or a default if empty.
 */
Point POP(Stack *S) {
    Point temp = {0.0, 0.0};
    if (!ISEMPTY(S)) {
        temp = S->items[S->topIndex--];
    }
    return temp;
}


/**
 * @brief Returns the top element without removing it.
 * 
 * Returns a default (0.0, 0.0) Point if the stack is empty.
 * 
 * @param S Pointer to the stack.
 * @return The Point at the top or a default if empty.
 */
Point TOP(Stack *S) {
    if (!ISEMPTY(S)) {
        return S->items[S->topIndex];
    } else {
        Point empty = {0.0, 0.0};
        return empty;
    }
}


/**
 * @brief Returns the element just below the top of the stack.
 * 
 * Useful for algorithms like Graham's scan in convex hulls.
 * 
 * Returns a default (0.0, 0.0) Point if the stack has fewer than 2 elements.
 * 
 * @param S Pointer to the stack.
 * @return The second-from-top Point or a default if not available.
 */
Point NEXT_TO_TOP(Stack *S) {
    if (S->topIndex >= 1) {
        return S->items[S->topIndex - 1];
    } else {
        Point empty = {0.0, 0.0};
        return empty;
    }
}


/**
 * @brief Copies the contents of the stack into an external array.
 * 
 * @param S Pointer to the stack.
 * @param outArray Array to store the stack elements in order.
 * @return The number of elements copied.
 */
int GET_STACK(Stack *S, Point outArray[]) {
    int count = S->topIndex + 1;
    for (int i = 0; i < count; i++) {
        outArray[i] = S->items[i];
    }
    return count;
}

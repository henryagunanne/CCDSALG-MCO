#include "stack.h"

// CREATE
void CREATE(Stack *S) {
    S->topIndex = -1;
}

// ISEMPTY
int ISEMPTY(Stack *S) {
    int result;
    if (S->topIndex < 0) {
        result = 1;
    } else {
        result = 0;
    } 
    return result;
}

// ISFULL
int ISFULL(Stack *S) {
    int result;
    if (S->topIndex >= MAX_POINT_COUNT - 1) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}

// PUSH
void PUSH(Stack *S, Point elem) {
    if (ISFULL(S) == 0) {
        S->topIndex++;
        S->items[S->topIndex] = elem;
    }
}

// POP
Point POP(Stack *S) {
    Point result;
    if (ISEMPTY(S) == 1) {
        result.x = 0.0;
        result.y = 0.0;
    } else {
        result = S->items[S->topIndex];
        S->topIndex--;
    }
    return result;
}

// TOP
Point TOP(Stack *S) {
    Point result;
    if (ISEMPTY(S) == 1) {
        result.x = 0.0;
        result.y = 0.0;
    } else {
        result = S->items[S->topIndex];
    }
    return result;
}

// NEXT_TO_TOP
Point NEXT_TO_TOP(Stack *S) {
    Point result;
    if (S->topIndex < 1) {
        result.x = 0.0;
        result.y = 0.0;
    } else {
        result = S->items[S->topIndex - 1];
    }
    return result;
}

// GET_STACK
int GET_STACK(Stack *S, Point outArray[]) {
    int count = S->topIndex + 1;
    for (int i = 0; i < count; i++) {
        outArray[i] = S->items[i];
    }
    return count;
}
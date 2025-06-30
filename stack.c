#include "stack.h"

void CREATE(Stack *S) {
    S->topIndex = -1;
}

int ISEMPTY(Stack *S) {
    if (S->topIndex < 0) {
        return 1;
    } else {
        return 0;
    }
}

int ISFULL(Stack *S) {
    if (S->topIndex >= MAX_POINT_COUNT - 1) {
        return 1;
    } else {
        return 0;
    }
}

void PUSH(Stack *S, Point elem) {
    if (!ISFULL(S)) {
        S->items[++S->topIndex] = elem;
    }
}

Point POP(Stack *S) {
    Point temp = {0.0, 0.0};
    if (!ISEMPTY(S)) {
        temp = S->items[S->topIndex--];
    }
    return temp;
}

Point TOP(Stack *S) {
    if (!ISEMPTY(S)) {
        return S->items[S->topIndex];
    } else {
        Point empty = {0.0, 0.0};
        return empty;
    }
}

Point NEXT_TO_TOP(Stack *S) {
    if (S->topIndex >= 1) {
        return S->items[S->topIndex - 1];
    } else {
        Point empty = {0.0, 0.0};
        return empty;
    }
}

int GET_STACK(Stack *S, Point outArray[]) {
    int count = S->topIndex + 1;
    for (int i = 0; i < count; i++) {
        outArray[i] = S->items[i];
    }
    return count;
}


#define STACK_H
typedef struct {
    Point items[MAX_POINT_COUNT];
    int topIndex;
} Stack;

void CREATE(Stack *S);
int ISEMPTY(Stack *S);
int ISFULL(Stack *S);
void PUSH(Stack *S, Point elem);
Point POP(Stack *S);
Point TOP(Stack *S);
Point NEXT_TO_TOP(Stack *S);
int GET_STACK(Stack *S, Point outArray[]);

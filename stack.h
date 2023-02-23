typedef struct stack
{
    char *A;
    // List **numbers;
    int n;
    int top;
} stack;

void initStack(stack *s,int n);
int isFull(stack s);
int isEmpty(stack s);
void push(stack *s,char c);
char pop(stack *s);
char peek(stack s);
void convertInfixToPostfix(stack *s, char *infix, char *postfix, int size);
int evaluatePostfix(stack *s, char *postfix, int size);
void printExpression(char *expr, int size);
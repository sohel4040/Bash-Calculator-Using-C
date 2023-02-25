typedef struct item 
{
    char data;
    struct item * next;    
} item;


typedef struct stack
{
    struct item* top;
} stack;

void initStack(stack *s);
int isFull(stack s);
int isEmpty(stack s);
void push(stack *s,char c);
char pop(stack *s);
char peek(stack s);
void convertInfixToPostfix(stack *s, char *infix, char *postfix, int size);
int evaluatePostfix(stack *s, char *postfix, int size);
void printExpression(char *expr, int size);
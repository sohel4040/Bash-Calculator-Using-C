#include<stdio.h>
#include"stack.h"

int len(char str[])
{
    char ch = str[0];
    int count = 0;
    int i = 0;
    while(ch != '\0')
    {
        count++;
        i++;
        ch = str[i];
    }

    return count;
}

int precedence(char ch)
{
    if(ch == '+' || ch == '-')
        return 1;

    if(ch == '*' || ch == '/')
        return 2;

    return -1;
}

int isOperand(char ch)
{
    return ch >= '0' && ch <= '9';
}

int isOperator(char ch)
{
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

int eval(char opr, int a , int b)
{
    int res = 0;
    
    switch(opr)
    {
        case '+': 
                res = a+b;
                break;
        case '-':
                res = a-b;
                break;
        case '*':
                res = a*b;
                break;
        case '/':
                res = a/b;
                break;
    }
    return res;
}

int evaluate(char infix[], int size)
{   
    stack operand, operator;
    initStack(&operand, size);
    initStack(&operator, size);


    for(int i=0; i < size; i++)
    {
        char ch = infix[i];

        if(isOperand(ch))
        {
            push(&operand, ch);
        }
        else if(isOperator(ch))
        {

            while(!isEmpty(operator) && precedence(peek(operator)) >= precedence(ch))
            {
                int b = pop(&operand) - '0';
                int a = pop(&operand) - '0';
                char op = pop(&operator);
                int res = eval(op, a, b);

                push(&operand, res + '0');

            }
            
            push(&operator, ch);
        }
        else if(ch == ')')
        {

            while(!isEmpty(operator) && !(peek(operator) == '('))
            {
                int b = pop(&operand) - '0';
                int a = pop(&operand) - '0';
                char op = pop(&operator);
                int res = eval(op, a, b);
                push(&operand,res + '0');

            }
            pop(&operator);
        }
        else
            push(&operator, ch);
    }

    while(!isEmpty(operator))
    {
        int b = pop(&operand) - '0';
        int a = pop(&operand) - '0';
        char op = pop(&operator);
        int res = eval(op, a, b);
        push(&operand, res + '0');
    }

    return peek(operand) - '0';

}

int main()
{
    char str[4000];
    scanf("%s",str);
    int size = len(str);

    int res = evaluate(str, size);

    // printExpression(str, size);
    printf("%d\n", res);
    return 0;
}

// 1 . if operand encounters then push it into operand stack

// 2 . if operator encounters then push it into operator stack
//     and check until stack has operators with same and higher priority and pop

// 3 . check stack empty condition also for poping
// 4 . pop until opern bracket encounters  

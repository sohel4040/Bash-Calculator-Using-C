#include"stack.h"
#include<stdio.h>
#include<stdlib.h>

void initStack(stack *s,int n)
{
        s-> A = (char*)malloc(sizeof(char)*n);
        s-> n = n;
        s-> top = -1;
}

int isFull(stack s)
{
    return (s.top == s.n-1);
}

int isEmpty(stack s)
{
    return (s.top == -1);
}

void push(stack *s,char c)
{
    if(isFull(*s))
        return;
    s->A[++(s->top)] = c;

}

char pop(stack *s)
{
    if(isEmpty(*s))
        return -1;
    return s->A[(s->top)--];
}

char peek(stack s)
{
    return s.A[s.top];
}

void convertInfixToPostfix(stack *s, char *infix, char *postfix, int size)
{
    int index = 0;
    for(int i=0;i<size;i++)
    {
        char c = infix[i];
        
        char p = peek(*s);
        if(((c == '+' || c == '-') && (p == '*' || p == '/' || p == '-' || p == '+') ) || ((c == '*' || c == '/') && (p == '*' || p == '/' ) ))
        {
            char n = pop(s);
            p = peek(*s);
            postfix[index++] = n;

            if(((c == '+' || c == '-') && (p == '*' || p == '/' || p == '-' || p == '+') ) || ((c == '*' || c == '/') && (p == '*' || p == '/' ) ))
            {
                char n = pop(s);
                postfix[index++] = n;
            }
            push(s,c);
        }
        else if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(')
        {
            push(s, c);
        }
        else if(c >= '0' && c <= '9' )
        {
            postfix[index++] = c;
        }
        if( c == ')')
        {
            char p = pop(s);
            while( p != '(' && !isEmpty(*s))
            {
                postfix[index++]=p;
                p = pop(s);
            }
        }
    }
    
    while(!isEmpty(*s))
    {
        postfix[index++] = pop(s);
    }
}

int evaluatePostfix(stack *s, char *postfix, int size)
{
    int eval=0;
    for(int i=0;i<size;i++)
    {
        char c = postfix[i];
       
        if(!(c == '+' || c == '-' || c == '*' || c == '/'))
        {
            push(s,c);
        }
        else 
        {
            int b = pop(s) - '0';
            int a = pop(s) - '0';
            switch(c)
            {
                case '+': 
                        eval = a+b;
                        break;
                case '-':
                        eval = a-b;
                        break;
                case '*':
                        eval = a*b;
                        break;
                case '/':
                        eval = a/b;
                        break;
            }
            push(s,eval + '0');
        }
    }

    return eval;
}

void printExpression(char *expr, int size)
{
    for(int i=0;i<size;i++)
    {
        printf("%c",expr[i]);
    }
}
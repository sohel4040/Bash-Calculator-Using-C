#include"stack.h"
#include<stdio.h>
#include<stdlib.h>

// Linkedlist implementation of stack should be added
// void initStack(stack *s,int n)
// {
//         s-> A = (char*)malloc(sizeof(char)*n);
//         s-> n = n;
//         s-> top = -1;
// }

// int isFull(stack s)
// {
//     return (s.top == s.n-1);
// }

// int isEmpty(stack s)
// {
//     return (s.top == -1);
// }

// void push(stack *s,char c)
// {
//     if(isFull(*s))
//         return;
//     s->A[++(s->top)] = c;

// }

// char pop(stack *s)
// {
//     if(isEmpty(*s))
//         return -1;
//     return s->A[(s->top)--];
// }

// char peek(stack s)
// {
//     return s.A[s.top];
// }

// void printExpression(char *expr, int size)
// {
//     for(int i=0;i<size;i++)
//     {
//         printf("%c",expr[i]);
//     }
// }


void initStack(stack *s)
{
    s -> top = NULL;
}

int isEmpty(stack s)
{
    return (s.top == NULL);
}

void push(stack *s,char data)
{
    item* newnode = (item*) malloc(sizeof(item));

    if(!newnode)
    return;

    newnode->data=data;
    newnode->next = NULL;

    if(isEmpty(*s))
    {
        s->top = newnode;
        return;
    }

    newnode -> next = s -> top;
    s -> top = newnode;

}

char pop(stack *s)
{
    if(isEmpty(*s))
    return -1;

    char element = s->top->data;
    item * temp = s-> top;
    s->top = s->top->next;
    free(temp);

    return element;

}

char peek(stack s)
{
    return s.top -> data;
}

#include<stdio.h>
#include<stdlib.h>
#include"number.h"

typedef struct element
{
    Number *number;
    struct element * next;    
} element;

typedef struct NumberStack
{
    element* top;
} NumberStack;

void initNumber(NumberStack *s)
{
    s->top = NULL;
}

int isNumberStackEmpty(NumberStack s)
{
    return (s.top == NULL);
}

void pushNumber(NumberStack *s,Number *num)
{
    element* newnode = (element*) malloc(sizeof(element));

    if(!newnode)
    return;

    newnode->number=num;
    newnode->next = NULL;

    if(isNumberStackEmpty(*s))
    {
        s->top = newnode;
        return;
    }

    newnode -> next = s -> top;
    s -> top = newnode;

}

Number* popNumber(NumberStack *s)
{
    if(isNumberStackEmpty(*s))
    return NULL;

    Number *num = s->top->number;
    element * temp = s-> top;
    s->top = s->top->next;
    free(temp);

    return num;

}

Number* topNumber(NumberStack s)
{   
    return s.top->number;
}

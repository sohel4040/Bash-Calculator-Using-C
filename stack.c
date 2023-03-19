#include"stack.h"
#include<stdio.h>
#include<stdlib.h>

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

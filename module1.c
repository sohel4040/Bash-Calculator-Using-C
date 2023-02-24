#include<stdio.h>
#include<stdlib.h>
#include"linkedlist.c"

typedef struct element
{
    List *number;
    struct element * next;    
} element;

typedef struct NumberStack
{
    element* top;
} NumberStack;

void initstack(NumberStack *s)
{
    s->top = NULL;
}

int isEmpty(NumberStack s)
{
    return (s.top == NULL);
}

void push(NumberStack *s,List *num)
{
    element* newnode = (element*) malloc(sizeof(element));

    if(!newnode)
    return;

    newnode->number=num;
    newnode->next = NULL;

    if(isEmpty(*s))
    {
        s->top = newnode;
        return;
    }

    newnode -> next = s -> top;
    s -> top = newnode;

}

List* pop(NumberStack *s)
{
    if(isEmpty(*s))
    return NULL;

    List *num = s->top->number;
    element * temp = s-> top;
    s->top = s->top->next;
    free(temp);

    return num;

}

List* top(NumberStack s)
{   
    return s.top->number;
}

// void display(stack *s)
// {
//     element *temp = s->top;

//     while(temp)
//     {
//         printf("%d\t",temp->data);
//         temp = temp -> next;
//     }
//     printf("\n");
// }

// int main()
// {
//     NumberStack s;

//     initstack(&s);
//     List l1, l2;
//     initList(&l1);
//     initList(&l2);
    
//     insertToFront(&l1, 9);
//     insertToFront(&l1, 5);

//     insertToFront(&l2, 2);
//     insertToFront(&l2, 1);

//     displayReverse(l1);
//     printf("\n");
//     displayReverse(l2);
//     printf("\n");

    
//     push(&s, &l1);
//     push(&s, &l2);

//     pop(&s);
//     List *l = top(s);


//     displayReverse(*l);



//     return 0;
    
// }
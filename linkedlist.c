#include<stdio.h>
#include<stdlib.h>
#include"linkedlist.h"

void initList(List *l)
{
    *l = NULL;
    return;
}

void insertToFront(List *l, int digit)
{
    node *nn = (node*) malloc(sizeof(node));
    nn -> data = digit;
    nn -> next = NULL;

    if(!nn)
        return;

    nn -> next = *l;
    *l = nn;

    return;
}

void append(List *l, int digit)
{
    node *nn = (node*) malloc(sizeof(node));
    nn -> data = digit;
    nn -> next = NULL;

    if(!nn)
        return;

    if(!(*l))
    {
        *l = nn;
        return;
    }

    node *temp = *l;
    while(temp->next)
    {
        temp = temp -> next;
    }

    temp -> next = nn;
    return;
}

List addTwoLinkedLists(List *l1, List *l2)
{
    if (!(*l1))
        return *l2;

    if(!(*l2))
        return *l1;

    List l3;
    initList(&l3);

    int sum = 0, carry = 0;
    node *p = *l1;
    node *q = *l2;

    while(p && q)
    {
        sum = (p -> data + q -> data + carry) % 10;
        append(&l3,sum); 
        carry = (p -> data + q -> data + carry) / 10;

        p = p -> next;
        q = q -> next;
        
    }

    while(p)
    {
        sum = (p -> data + carry) % 10;
        append(&l3,sum); 
        carry = (p -> data + carry) / 10;
        
        p = p -> next; 

    }

    while(q)
    {
        sum = (q -> data + carry) % 10;
        append(&l3,sum);
        carry = (q -> data + carry) / 10;

        q = q -> next; 

    }

    if(carry)
        append(&l3,carry);
    
        
    return l3;
}

void displayList(List l)
{
    node *temp = l;

    while(temp)
    {
        printf("%d\t",temp->data);
        temp = temp -> next;
    }

    printf("\n");

    return;
}


void displayReverse(node *l)
{
    if(!l)
        return;

    displayReverse(l->next);
    printf("%d\t",l->data);
}
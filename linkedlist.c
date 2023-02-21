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

int isZero(List l)
{
    if(!l)
        return -1;

    node *temp = l;
    int zero = 0;

    while(temp)
    {
        if(temp -> data == 0)
            zero++;

        temp = temp -> next;
    }

    return length(l) == zero;

}

// All test cases passed
List addTwoLinkedLists(List *l1, List *l2)
{
    if (!(*l1))
        return *l2;

    if(!(*l2))
        return *l1;

    List result;
    initList(&result);

    int sum = 0, carry = 0;
    node *p = *l1;
    node *q = *l2;

    while(p && q)
    {
        sum = (p -> data + q -> data + carry) % 10;
        append(&result,sum); 
        carry = (p -> data + q -> data + carry) / 10;

        p = p -> next;
        q = q -> next;
        
    }

    while(p)
    {
        sum = (p -> data + carry) % 10;
        append(&result,sum); 
        carry = (p -> data + carry) / 10;
        
        p = p -> next; 

    }

    while(q)
    {
        sum = (q -> data + carry) % 10;
        append(&result,sum);
        carry = (q -> data + carry) / 10;

        q = q -> next; 

    }

    if(carry)
        append(&result,carry);
    
        
    return result;
}

// Test cases are remaining 
// Yet to be tested more ...
List substractTwoLinkedLists(List *l1, List *l2)
{
    if (!(*l1))
        return *l2;

    if(!(*l2))
        return *l1;

    List result;
    initList(&result);

    int diff = 0, borrow = 0;
    node *p = *l1;
    node *q = *l2;

    while(p && q)
    {
        diff = p -> data - q -> data - borrow;

        if(diff < 0)
        {
            diff += 10;
            borrow = 1;
        } 
        else 
        {
            borrow = 0;
        }

        append(&result, diff);

        p = p -> next;
        q = q -> next;

    }

    while(p)
    {
        diff = p -> data - borrow;
        append(&result, diff);
        if(diff < 0)
        {
            diff += 10;
            borrow = 1;
        } 
        else 
        {
            borrow = 0;
        }

        p = p -> next;
    }

    while(q)
    {
        diff = q -> data - borrow;
        append(&result, diff);
        if(diff < 0)
        {
            diff += 10;
            borrow = 1;
        } 
        else 
        {
            borrow = 0;
        }

        q = q -> next;
    }

    return result;
}

// Multiplication done
// Yet to be tested more ...
List multiplyTwoLinkedLists(List *l1 , List *l2)
{
    if (!(*l1))
        return *l2;

    if(!(*l2))
        return *l1;

    List result, temp;
    initList(&result);

    node *p = *l1;
    int  decimalPlaces = 0;
    while(p)
    {
       initList(&temp);
       node *q = *l2;
       int product = 1, carry = 0; 
       while(q)
       {
         product = (p -> data * q -> data + carry) % 10;
         append(&temp, product);
         carry = (p -> data * q -> data + carry) / 10;
         q = q -> next;
       }

       for(int i = 0; i < decimalPlaces; i++)
       {
            insertToFront(&temp, 0);
       }

       if(carry)
         append(&temp, carry);
       
       result = addTwoLinkedLists(&result, &temp);
       decimalPlaces++;

       p = p -> next;

    }

    return result;
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
    printf("%d",l->data);
}

int length(List l)
{
    node *temp = l;

    int count = 0;
    while(temp)
    {
        count++;
        temp = temp -> next;
    }

    return count;
}
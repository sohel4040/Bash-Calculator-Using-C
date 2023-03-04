#include<stdio.h>
#include<stdlib.h>
#include"linkedlist.h"

void initList(List *l)
{
    *l = NULL;
    return;
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

int deleteFirst(List *l)
{
    if(!(*l))
        return -1;

    node* temp = (*l);
    int element = temp -> data;
    *l = (*l) -> next;

    free(temp);

    return element;
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

void reverse(List *l)
{
    if(!(*l) || !((*l) -> next))
        return;

    node *previous = NULL;
    node *current = *l;

    while(current)
    {
        node *temp = current -> next;
        current -> next = previous;
        previous = current;
        current = temp;
    }
    *l = previous;
}

int checkIfEqual(List l1, List l2)
{
    node *p = l1;
    node *q = l2;

    int len1 = length(l1);
    int len2 = length(l2);

    if(len1 == len2)
    {
        while(p && q)
        {
            if(p -> data != q -> data)
                return 0;
            
            p = p -> next;
            q = q -> next;
        }

        return 1;
    }
    else 
        return 0;

}

int compare(List l1, List l2)
{
    List temp1, temp2;
    initList(&temp1);
    initList(&temp2);

    node *traverse1, *traverse2;

    traverse1 = l1;
    traverse2 = l2;

    while(traverse1)
    {
        insertToFront(&temp1, traverse1 -> data);
        traverse1 = traverse1 -> next; 
    }

    while(traverse2)
    {
        insertToFront(&temp2, traverse2 -> data);
        traverse2 = traverse2 -> next; 
    }

    int p = length(temp1);
    int q = length(temp2);

     if(q > p)
         return 0;

    node *first = temp1;
    node *second = temp2;

    if(p == q)
    {
        while(first && second)
        {
            if(second -> data > first -> data)
                return 0;
            else if(first -> data > second -> data)
                return 1;

            first = first -> next;
            second = second -> next;

        }
    }
    return 1;
}

void removeRedundentZeros(List *l)
{
    if(!(*l))
        return;

    reverse(l);

    node *temp = *l;

    while(temp)
    {
        if(temp -> data == 0)
        {
            deleteFirst(l);
        }
        else
        {
            reverse(l);
            return;
        }

        temp = *l;

    }

    reverse(l);


    return;
}

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

    if(!compare(*l1,*l2))
    {
        p = *l2;
        q = *l1;
    }

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
    }

    while(q)
    {
        diff = q -> data - borrow;
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

        q = q -> next;
    }

    return result;
}

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


int compareTwoNumbers(List l1, List l2)
{

    if(!l1)
        return 0;

    if(!l2)
        return 1;

    if(checkIfEqual(l1, l2))
        return 0;
    int p = length(l1);
    int q = length(l2);

     if(q > p)
         return 0;

    node *first = l1;
    node *second = l2;

    if(p == q)
    {
        while(first && second)
        {
            if(second -> data > first -> data)
                return 0;
            else if(first -> data > second -> data)
                return 1;

            first = first -> next;
            second = second -> next;

        }
    }
    return 1;
}

// It performs small numbers division
List divideDigits(List *l1, List *l2)
{
    if (!(*l1))
        return *l2;

    if(!(*l2))
        return *l1;

    if(isZero(*l2))
        return NULL;
    

    List result, one;
    initList(&result);
    initList(&one);
    append(&result, 0);
    append(&one, 1);

    if(isZero(*l1))
    {
        return result;
    }
    removeRedundentZeros(l1);
    removeRedundentZeros(l2);


    node *temp = *l2;

    while(compare(*l1,temp))
    {
        result = addTwoLinkedLists(&result, &one);
        temp = addTwoLinkedLists(&temp, l2);
    }


    return result;
}

// Return the quotient linkedlist of two numbers after division
List divideTwoLinkedLists(List *l1, List *l2)
{
    if (!(*l1))
        return *l2;

    if(!(*l2))
        return *l1;

    if(isZero(*l1))
        return *l1;

    if(isZero(*l2))
    {
        printf("Runtime Error : Cannot divide by zero\n");
        return NULL;
    }

    removeRedundentZeros(l1);
    removeRedundentZeros(l2);

    List temp,quotient,first,second, traverse ;
    initList(&quotient);
    initList(&temp);
    first = *l1;
    second = *l2;
    traverse = first;

    reverse(&first);
    reverse(&second);

    append(&temp, first -> data);

    while(first)
    {
        if(compareTwoNumbers(second, temp))
        {
            insertToFront(&quotient, 0);
        }
        else
        {
            reverse(&temp);
            reverse(&second);
            
            List division = divideDigits(&temp, &second);
            insertToFront(&quotient, division -> data);


            List mul = multiplyTwoLinkedLists(&second, &division);

            temp = substractTwoLinkedLists(&temp, &mul);
            removeRedundentZeros(&temp);

            reverse(&temp);
            reverse(&second);

        }
        first = first -> next;

        if(first)
        {
            int data = first -> data;
            append(&temp, data);
        }
    }

    return quotient;
   
}

// It will perform division of two numbers and returns the remainder linkedlist.
List modTwoLinkedLists(List *l1, List *l2)
{
    if (!(*l1))
        return *l2;

    if(!(*l2))
        return *l1;

    if(isZero(*l2))
        return NULL;

    List temp, first, second, traverse;
    initList(&temp);
    first = *l1;
    second = *l2;
    traverse = first;

    reverse(&first);
    reverse(&second);

    append(&temp, first -> data);

    while(first)
    {
        if(!compareTwoNumbers(second, temp))
        {
            reverse(&temp);
            reverse(&second);
            
            List division = divideDigits(&temp, &second);
            List mul = multiplyTwoLinkedLists(&second, &division);

            temp = substractTwoLinkedLists(&temp, &mul);
            removeRedundentZeros(&temp);

            reverse(&temp);
            reverse(&second);

        }
        first = first -> next;

        if(first)
        {
            int data = first -> data;
            append(&temp, data);
        }
    }

    if(!temp)
        append(&temp , 0);

    reverse(&temp);

    return temp;

}

List power(List *l1, List *l2)
{

    List result, one = NULL;
    initList(&result);
    append(&result, 1);
    append(&one, 1);

    while(!isZero(*l2))
    {
        result = multiplyTwoLinkedLists(&result, l1);
        *l2 = substractTwoLinkedLists(l2, &one);
    }

    return result;
}

void displayList(List l)
{
    node *temp = l;

    while(temp)
    {
        printf("%d",temp->data);
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


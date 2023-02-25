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

// Addition done
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

// Substraction done
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

    // if second number is greater than first number
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

int compareTwoNumbers(List l1, List l2)
{

    if(!l1)
        return 0;

    if(!l2)
        return 1;

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
List divideTwoLinkedLists(List *l1, List *l2)
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
        append(&result, 0);
        return result;
    }

    node *temp = *l2;

    while(compare(*l1,temp))
    {
        result = addTwoLinkedLists(&result, &one);
        temp = addTwoLinkedLists(&temp, l2);
    }


    return result;
}

// Division done
// Yet to be tested more ...
// List divideTwoLinkedLists(List *l1, List *l2)
// {
//     if (!(*l1))
//         return *l2;

//     if(!(*l2))
//         return *l1;

//     if(isZero(*l2))
//         return NULL;

//     List temp,quotient,first,second, traverse ;
//     initList(&quotient);
//     initList(&temp);
//     first = *l1;
//     second = *l2;
//     traverse = first;

//     reverse(&first);
//     reverse(&second);

//     // isplayList(first);
//     // displayList(second);d

//     append(&temp, first -> data);
//     // first = first -> next;

//     while(first)
//     {
//         if(compareTwoNumbers(second, temp))
//         {
//             insertToFront(&quotient, 0);
//         }
//         else
//         {
//             reverse(&temp);
//             reverse(&second);
            
//             List division = divideDigits(&temp, &second);
//             insertToFront(&quotient, division -> data);

//             List mul = multiplyTwoLinkedLists(&second, &division);

//             temp = substractTwoLinkedLists(&temp, &mul);
//             reverse(&temp);
//             reverse(&second);

//         }
//         int data = first -> data;
//         append(&temp, data);
//         // displayList(temp);
//         // printf("\n");
//         first = first -> next;
//     }

//     return quotient;
   
// }

// Remainder function works 
// some extra work need to be done
List modTwoLinkedLists(List *l1, List *l2)
{
    if (!(*l1))
        return *l2;

    if(!(*l2))
        return *l1;

    if(isZero(*l2))
        return NULL;

    List result;
    initList(&result);

    if(isZero(*l1))
    {
        append(&result, 0);
        return result;
    }

    if(compare(*l2, *l1))
    {
        return *l1;
    }


    List division = divideTwoLinkedLists(l1, l2);
    List temp = multiplyTwoLinkedLists(l2, &division);

    result = substractTwoLinkedLists(l1, &temp);
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



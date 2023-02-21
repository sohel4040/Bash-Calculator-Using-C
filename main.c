#include<stdio.h>
#include<stdlib.h>
#include"linkedlist.h"
#include"stack.h"

// Addition Done 
// Substraction Done
// Multiplication Done
// Division is pending

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

int main()
{
    List l,l1;
    initList(&l);
    initList(&l1);

    // stack s;
    // char str[4000];
    // scanf("%s",str);
    // int size = len(str);
    // initStack(&s, size);
    // char *postfix = (char *) malloc(sizeof(char)*size);

    // convertInfixToPostfix(&s, str, postfix, size);

    // printExpression(postfix, size);

    insertToFront(&l,6);
    insertToFront(&l,4);
    // insertToFront(&l,3);
    // insertToFront(&l,6);
    // insertToFront(&l,4);

    insertToFront(&l1,2); 
    // insertToFront(&l1,3);
    // insertToFront(&l1,4);
    // insertToFront(&l1,4);
    // insertToFront(&l1,4);
    // insertToFront(&l1,3);
    // insertToFront(&l1,5);

    displayReverse(l);
    printf("\n");
    displayReverse(l1);
    printf("\n");


    // List l2 = addTwoLinkedLists(&l, &l1);
    // List l3 = substractTwoLinkedLists(&l, &l1);
    // List l4 = multiplyTwoLinkedLists(&l, &l1);
    List l5 = divideTwoLinkedLists(&l, &l1);

    // displayReverse(l5);
    printf("\n");

    return 0;
}

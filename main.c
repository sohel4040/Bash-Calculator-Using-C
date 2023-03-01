#include<stdio.h>
#include<stdlib.h>
#include"linkedlist.h"

int main()
{
    List l1,l2;

    initList(&l1);
    initList(&l2);

    insertToFront(&l1, 3);
    insertToFront(&l1, 9);
    insertToFront(&l1, 4);
    insertToFront(&l1, 4);
    insertToFront(&l1, 4);
    insertToFront(&l1, 4);
    insertToFront(&l1, 1);
    insertToFront(&l1, 1);
    insertToFront(&l1, 1);
    insertToFront(&l1, 1);
    insertToFront(&l1, 1);
    insertToFront(&l1, 1);
    insertToFront(&l1, 1);
    insertToFront(&l1, 1);
    insertToFront(&l1, 1);
    insertToFront(&l1, 1);
    insertToFront(&l1, 1);
    insertToFront(&l1, 1);
    insertToFront(&l1, 1);
    insertToFront(&l1, 1);
    insertToFront(&l1, 1);
    insertToFront(&l1, 1);
    insertToFront(&l1, 1);
    insertToFront(&l1, 1);
    insertToFront(&l1, 1);
    insertToFront(&l1, 1);
    insertToFront(&l1, 1);



    insertToFront(&l2, 3);
    // insertToFront(&l2, 3);

    displayReverse(l1);
    printf("\n");

    displayReverse(l2);
    printf("\n");

    List result = divide(&l1, &l2);

    displayReverse(result);
    printf("\n");


    return 0;
}



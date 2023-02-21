#include<stdio.h>
#include"linkedlist.h"

int main()
{
    List l,l1;
    initList(&l);
    initList(&l1);


    insertToFront(&l,6);
    insertToFront(&l,4);
    insertToFront(&l,3);
    insertToFront(&l,6);
    insertToFront(&l,4);

    

    insertToFront(&l1,3);
    insertToFront(&l1,3);
    insertToFront(&l1,4);
    insertToFront(&l1,4);
    insertToFront(&l1,4);
    insertToFront(&l1,3);
    insertToFront(&l1,5);





    // printf("%d",isZero(l1));

    displayReverse(l);
    printf("\n");
    displayReverse(l1);
    printf("\n");


    // List l2 = addTwoLinkedLists(&l, &l1);
    // List l3 = substractTwoLinkedLists(&l, &l1);
    List l4 = multiplyTwoLinkedLists(&l, &l1);

    displayReverse(l4);
    printf("\n");

    return 0;
}

// 1 2 2 p
// 2 0 4 q  
// 2 4 4
// 

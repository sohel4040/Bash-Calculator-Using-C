#include<stdio.h>
#include"linkedlist.h"

int main()
{
    List l,l1;
    initList(&l);
    initList(&l1);


    insertToFront(&l,9);
    insertToFront(&l,9);
    insertToFront(&l,9);

    // insertToFront(&l1,4);
    insertToFront(&l1,3);
    insertToFront(&l1,8);


    displayReverse(l);
    printf("\n");
    displayReverse(l1);
    printf("\n");


    List l2 = addTwoLinkedLists(&l, &l1);
    displayReverse(l2);
    printf("\n");

    return 0;
}

// 9 9 9 
//   3 8
// 0 3 7

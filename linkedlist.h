typedef struct node
{
    int data;
    struct node* next;
} node;

typedef node* List;

void initList(List *l);
void insertToFront(List *l, int d);
void append(List *l, int d);
int length(List l);
int isZero(List l);
List addTwoLinkedLists(List *l1, List *l2);
List substractTwoLinkedLists(List *l1, List *l2);
List multiplyTwoLinkedLists(List *l1, List *l2);
void displayList(List l);   
void displayReverse(node *l);


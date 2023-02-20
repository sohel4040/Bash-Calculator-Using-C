typedef struct node
{
    int data;
    struct node* next;
} node;

typedef node* List;

void initList(List *l);
void insertToFront(List *l, int d);
List addTwoLinkedLists(List *l1, List *l2);
void displayList(List l);   
void displayReverse(node *l);


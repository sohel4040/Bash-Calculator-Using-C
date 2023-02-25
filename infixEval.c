#include<stdio.h>
#include<stdlib.h>
#include"stack.h"
#include"linkedlist.h"
#include"module1.c"

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

int precedence(char ch)
{
    if(ch == '+' || ch == '-')
        return 1;

    if(ch == '*' || ch == '/')
        return 2;

    return -1;
}

int isOperand(char ch)
{
    return ch >= '0' && ch <= '9';
}

int isOperator(char ch)
{
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

Number* eval(char opr, Number* a , Number* b)
{

    Number *res = (Number*) malloc(sizeof(Number));

    if(!res)
        return NULL;

    List temp;
    initList(&temp);

    if(opr == '*' || opr == '/')
    {
        if((a -> sign == '+' && b -> sign == '-') || (a -> sign == '-' && b -> sign == '+'))
            res -> sign = '-';
        else
            res -> sign = '+';

        if(opr == '*')
        {
            temp =  multiplyTwoLinkedLists(a -> head, b -> head);
        }
        else
        {
            temp =  divideTwoLinkedLists(a -> head, b -> head);
        }
    }
    else
    {
        if((a -> sign == '-' && b -> sign == '-') || (a -> sign == '+' && b -> sign == '+'))
        {
            res -> sign = a -> sign;
            temp = addTwoLinkedLists(a -> head, b -> head);
        }
        else
        {
            if(compare(*(a -> head), *(b -> head)))
                res -> sign = a -> sign;
            else
                res -> sign = b -> sign;

            temp = substractTwoLinkedLists(a -> head, b -> head);
        }
     
    }

    res -> head = &temp;

    return res;
}

Number* createNumber(char sign, List num)
{
    Number* no = (Number*) malloc(sizeof(Number));

    if(!no)
        return NULL;

    no -> sign = sign;
    no -> head = &num;

    return no;
}

Number* evaluate(char infix[], int size)
{   
    NumberStack operand;
    stack operator;
    initNumber(&operand);
    initStack(&operator, size);

    int j = 0;
    for(int i=0; i < size; i++)
    {
        char ch = infix[j];

        if(isOperand(ch))
        {
            List num;
            char sign;
            initList(&num); 

            if(j==0 || infix[j-1] == '+')
                sign = '+';
            else if(infix[j-1] == '-')
                sign = '-';
            else
                sign = '+';

            while(isOperand(ch))
            {
                insertToFront(&num, ch - '0');
                j++;
                ch = infix[j];
            }
            // Number *no = createNumber(sign, num);
            // printf("%c",no -> sign);
            displayReverse(num);
            printf("\n");
            // pushNumber(&operand, no);
        }
        else if(isOperator(ch))
        {
            printf("\n%c\n",ch);
            while(!isEmpty(operator) && precedence(peek(operator)) >= precedence(ch))
            {
                // Number* b = popNumber(&operand);
                // Number* a = popNumber(&operand);
                // char op = pop(&operator);
                // Number* res = eval(op, a, b);

                // pushNumber(&operand, res);

            }
            push(&operator, ch);
            j++;
        }
        else if(ch == ')')
        {

            while(!isEmpty(operator) && !(peek(operator) == '('))
            {
                // Number* b = popNumber(&operand);
                // Number* a = popNumber(&operand);
                // char op = pop(&operator);
                // Number* res = eval(op, a, b);
                // pushNumber(&operand, res);

            }
            pop(&operator);
            j++;
        }
        else
        {
            push(&operator, ch);
            j++;
        }
    }

    while(!isEmpty(operator))
    {
        // Number* b = popNumber(&operand);
        // Number* a = popNumber(&operand);
        // char op = pop(&operator);
        // Number* res = eval(op, a, b);

        // pushNumber(&operand, res);
    }

    return topNumber(operand);

}

int main()
{
    char str[4000];
    scanf("%s",str);
    int size = len(str);

    Number *res = evaluate(str, size);
    // printf("\n%c",res -> sign);
    // List temp = *(res -> head);
    // displayReverse(temp);
    printf("\n");

    // printExpression(str, size);
    // printf("%d\n", res);
    return 0;
}

// 1 . if operand encounters then push it into operand stack

// 2 . if operator encounters then push it into operator stack
//     and check until stack has operators with same and higher priority and pop

// 3 . check stack empty condition also for poping
// 4 . pop until opern bracket encounters  

#include<stdio.h>
#include<stdlib.h>
#include"stack.h"
#include"linkedlist.h"
#include"numberstack.c"

#define MAX_SIZE 5000

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

    if(ch == '%')
        return 3;

    return -1;
}

int isOperand(char ch)
{
    return ch >= '0' && ch <= '9';
}

int isOperator(char ch)
{
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%';
}

int isAlien(char ch)
{
    return !(ch >= '0' && ch <= '9' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '(' || ch == ')');
}

Number* eval(char opr, Number* a , Number* b)
{

    Number *res = (Number*) malloc(sizeof(Number));

    if(!res)
        return NULL;

    List temp;
    initList(&temp);
    List first = a -> head;
    List second = b -> head; 

    // printf("%c", a -> sign);
    // displayReverse(a -> head);
    // printf("\n");

    // printf("%c", b -> sign);
    // displayReverse(b -> head);
    // printf("\n");

    if(opr == '*' || opr == '/')
    {
        if((a -> sign == '+' && b -> sign == '-') || (a -> sign == '-' && b -> sign == '+'))
            res -> sign = '-';
        else
            res -> sign = '+';

        if(opr == '*')
            temp =  multiplyTwoLinkedLists(&first, &second);
        else
            temp =  divideTwoLinkedLists(&first, &second);
    }
    else if(opr == '%')
    {
        if((a -> sign == '-' && b -> sign == '-') || (a -> sign == '+' && b -> sign == '+'))
        {
            res -> sign = a -> sign;
        }
        else
        {
                res -> sign = a -> sign;
        }
        temp = modTwoLinkedLists(&first, &second);
    }
    else
    {
        if((a -> sign == '-' && b -> sign == '-') || (a -> sign == '+' && b -> sign == '+'))
        {
            res -> sign = a -> sign;
            temp = addTwoLinkedLists(&first, &second);
        }
        else
        {
            if(compare(first, second))
                res -> sign = a -> sign;
            else
                res -> sign = b -> sign;

            temp = substractTwoLinkedLists(&first, &second);

        }
     
    }

    if(!isZero(temp))
        removeRedundentZeros(&temp);
    res -> head = temp;

    return res;
}

Number* createNumber(char sign, List num)
{
    Number* no = (Number*) malloc(sizeof(Number));

    if(!no)
        return NULL;

    no -> sign = sign;
    no -> head = num;

    return no;
}

Number* evaluate(char infix[], int size)
{   
    NumberStack operand;
    stack operator;
    initNumber(&operand);
    initStack(&operator);

    int j = 0;
    while(j < size)
    {
        char ch = infix[j];
        

        if(ch == '.')
        {
            printf("Numbers should be decimals");
            return NULL;
        }

        if(isAlien(ch))
        {
            printf("Syntax Error\n");
            return NULL;
        }

        if(isOperand(ch))
        {
            List num;
            char sign;
            initList(&num); 

            if(j==0)
                sign = '+';
            else if(infix[j-1] == '-' || (infix[j-1] == '+' && infix[j-2] == '-' && j>2))
                sign = '-';
            else
                sign = '+';

            while(isOperand(ch))
            {
                insertToFront(&num, ch - '0');
                j++;
                ch = infix[j];
            }
            Number *no = createNumber(sign, num);
            pushNumber(&operand, no);
        }
        else if(isOperator(ch))
        {
            if(ch == '-' && isOperator(infix[j+1]))
            {
                printf("Syntax Error - Invalid expression\n");
                return NULL;
            }
       
            if((ch == '-' && isOperator(infix[j-1])) || j == 0 || (ch == '+' && isOperator(infix[j-1])) || (isOperator(ch) && infix[j-1] == '('))
            {
                j++;
                continue;
            }
            while(!isEmpty(operator) && precedence(peek(operator)) >= precedence(ch))
            {
                Number* b = popNumber(&operand);
                Number* a = popNumber(&operand);

                char op = pop(&operator);
                Number* res = eval(op, a, b);
                pushNumber(&operand, res);

            }
          
            push(&operator, ch);
            j++;
        }
        else if(ch == ')')
        {

            while(!isEmpty(operator) && !(peek(operator) == '('))
            {
                Number* b = popNumber(&operand);
                Number* a = popNumber(&operand);
                char op = pop(&operator);
                Number* res = eval(op, a, b);
                pushNumber(&operand, res);
            }
            pop(&operator);
            Number *temp = topNumber(operand);
            char tempOpr = peek(operator);

            if(temp -> sign == '-' && tempOpr == '-')
            {
                temp = popNumber(&operand);
                temp -> sign = '+';
                tempOpr = pop(&operator);
                tempOpr = '+';
                pushNumber(&operand, temp);
                push(&operator, tempOpr);
            }
            else if(temp -> sign == '+' && tempOpr == '-')
            {
                temp = popNumber(&operand);
                temp -> sign = '-';
                pushNumber(&operand, temp);
            }
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
        Number* b = popNumber(&operand);
        Number* a = popNumber(&operand);
        char op = pop(&operator);

        Number* res = eval(op, a, b);
        pushNumber(&operand, res);

    }

    return popNumber(&operand);
}

void removeAllSpacesFromExpression(char str[], int size)
{
    int i = 0, j = 0;

    while (i < size) {
        if (str[i] != ' ') {
            str[j++] = str[i];
        }
        i++;
    }
    str[j] = '\0';

    // printf("%d", len(str));

    int k = 0;

    // while(k < size)
    // {
    //     printf("%c",str[k++]);
    // }
    // printf("\n");
}

int main()
{
    char str[MAX_SIZE];
    printf("Type q or ctrl+c to exit from calculator...\n");

    while(1)
    {
        printf("> ");
        scanf("%s",str);
        if(str[0] == 'q')
            break;
        int size = len(str);

        // removeAllSpacesFromExpression(str, size);        
        // 5 + 6 - 3 * 8 / 4 * 2 + 9 *2

        Number* res = evaluate(str, size);

        if(res)
        {
            if(res -> sign == '-' && !isZero(res -> head))
                printf("%c",res -> sign);
            
            // if(!isZero(res -> head))
            //     removeRedundentZeros(&(res -> head));
            
            displayReverse(res -> head);
            printf("\n");
        }
       
    
    }

    return 0;
}


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
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

    if(ch == '*' || ch == '/' || ch == '%')
        return 2;

    if(ch == '^')
        return 3;

    return -1;
}

int isOperand(char ch)
{
    return ch >= '0' && ch <= '9';
}

int isOperator(char ch)
{
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '^';
}

int isAlien(char ch)
{
    return !(isOperand(ch) || isOperator(ch) || ch == '(' || ch == ')' || ch == '.');
}

void appendZeros(List *num, int count)
{
    int i = 0;
    while(i < count)
    {
        append(num, 0);
    }
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

    int count1 = length(first);
    int count2 = length(second);

    int afterDecimal1 = count1 - a -> count;
    int afterDecimal2 = count2 - b -> count;

    while(afterDecimal1 > afterDecimal2)
    {   
            insertToFront(&second, 0);
            afterDecimal2++;
    }

    while(afterDecimal2 > afterDecimal1)
    {
            insertToFront(&first, 0);
            afterDecimal1++;
    }

    if(opr == '*' || opr == '/')
    {
        if((a -> sign == '+' && b -> sign == '-') || (a -> sign == '-' && b -> sign == '+'))
            res -> sign = '-';
        else
            res -> sign = '+';

        if(opr == '*')
        {
            temp =  multiplyTwoLinkedLists(&first, &second);
            int afterDecimal3 = length(temp) - (length(temp) - (afterDecimal1 + afterDecimal2));

            int needToTruncate = afterDecimal1 >= afterDecimal2 ? afterDecimal1 : afterDecimal2; 
            truncateDecimalPointDigits(&temp,afterDecimal3, needToTruncate);

            res -> count = length(temp) - needToTruncate;

        }
        else
        {
            if(a -> count < b -> count)
            {
                List num;
                initList(&num);
                append(&num, 0);
                temp = num;

                
            }
            else 
            {
                if(afterDecimal1 < afterDecimal2)
                    appendZeros(&first, afterDecimal2 - afterDecimal1);
                else
                    appendZeros(&second, afterDecimal1 - afterDecimal2);
                
                temp = divideTwoLinkedLists(&first, &second);

                res -> count = length(temp);

            }



        }

    }
    else if(opr == '%')
    {
        if((a -> sign == '-' && b -> sign == '-') || (a -> sign == '+' && b -> sign == '+'))
            res -> sign = a -> sign;
        else
            res -> sign = a -> sign;
            
        temp = modTwoLinkedLists(&first, &second);
    }
    else if(opr == '^')
    {
        if(b -> sign == '-'&& b -> count == length(b -> head))
        {
            List num;
            initList(&num);
            append(&num, 0);
            temp = num;
            res -> sign = '+';
        }
        else if(b -> count < count2)
        {
            printf("Runtime warning\n");
            temp = NULL;
        }
        else if(isZero(second))
        {
            List num;
            initList(&num);
            append(&num, 1);
            temp = num;
            res -> sign = '+';
        }
        else
        {

            res -> sign = '+';
            temp = power(&first, &second);
            res -> count = length(temp);
        }
            
    }
    else
    {
        if((a -> sign == '-' && b -> sign == '-') || (a -> sign == '+' && b -> sign == '+'))
        {
            res -> sign = a -> sign;
            temp = addTwoLinkedLists(&first, &second);
            res -> count = length(temp) - afterDecimal1;

        }
        else
        {
            if(compare(first, second))
                res -> sign = a -> sign;
            else
                res -> sign = b -> sign;

            temp = substractTwoLinkedLists(&first, &second);
            
            if(!isZero(temp))
                removeRedundentZeros(&temp);
            
            res -> count = b -> count;
        
        }
     
    }

    if(!temp)
        return NULL;

    if(checkIfNumberIsTendsToZero(temp, res -> count))
    {
            res -> head = temp;
            return res;
    }


    if(!isZero(temp))
    {
        removeRedundentZeros(&temp);
    }
    else
    {
        temp = NULL;
        append(&temp, 0);
    }
    res -> head = temp;

    return res;
}

Number* createNumber(char sign, int count, List num)
{
    Number* no = (Number*) malloc(sizeof(Number));

    if(!no)
        return NULL;

    no -> sign = sign;
    no -> count = count;
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

        if(isAlien(ch))
        {
            printf("Syntax Error\n");
            return NULL;
        }

        if(isOperand(ch))
        {
            int i = 0,count = 0, flag = 0;
            List num;
            char sign;
            initList(&num); 
            if(j==0)
                sign = '+';
            else if(infix[j-1] == '-' || (infix[j-1] == '+' && infix[j-2] == '-' && j>2))
                sign = '-';
            else
                sign = '+';

            if(infix[j-1] == '.')
                flag = 1;

            while(isOperand(ch) || ch == '.')
            {
                if(ch == '.')
                {
                    count = i;
                }
                else 
                {
                    i++;
                    insertToFront(&num, ch - '0');
                }
                j++;
                ch = infix[j];
            }
            if(count == 0)
            {
                count = i;
            }
            if(flag == 1)
                count = 0;

            Number *no = createNumber(sign, count, num);
         
            pushNumber(&operand, no);
        }
        else if(isOperator(ch))
        {
            if((ch == '-' && isOperator(infix[j+1])) || (ch == '+' && (infix[j+1] == '*' || infix[j+1] == '/')))
            {
                printf("Syntax Error - Invalid expression\n");
                return NULL;
            }
           
            if(!(j == 0 && (ch == '-' || ch == '+') && infix[j+1] == '(') && ((ch == '-' && isOperator(infix[j-1])) || j == 0 || (ch == '+' && isOperator(infix[j-1])) || (isOperator(ch) && infix[j-1] == '(')))
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
            if(isEmpty(operator))
            {
                printf("Syntax Error");
                return NULL;
            }
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

            if((temp -> sign == '-' && tempOpr == '-'))
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
            if(j == 0)
            {
                List num;
                initList(&num); 
                insertToFront(&num, 0);
                Number *no = createNumber('+',1, num);
                pushNumber(&operand, no);

                push(&operator, '+');
            }
            else if(j == 1 && (infix[0] == '-' || infix[0] == '+'))
            {
                List num;
                initList(&num); 
                insertToFront(&num, 0);
                Number *no = createNumber('+',1, num);
                pushNumber(&operand, no);

            }

            push(&operator, ch);
            j++;
        }
    }

    while(!isEmpty(operator))
    {
        Number* b = popNumber(&operand);
        Number* a = popNumber(&operand);

        char op = pop(&operator);

        if(!a)
        {
            if(op != -1)
            {
                if((b -> sign == '-' && op == '-') || (b -> sign == '-' && op == '+') || (b -> sign == '+' && op == '-'))
                    b -> sign = '-';
                else
                    b -> sign = '+';

            }
            return b;
        }

        Number* res = eval(op, a, b);
        pushNumber(&operand, res);

    }

    return popNumber(&operand);
}

int main()
{
    char str[MAX_SIZE];
    printf("DSA-I Project : Binary Calculator\n");
    printf("Name : Sohel Shamshuddin Bargir\nMIS : 142203002\n");
    printf("-------------------------------------------\n");
    printf("Type q or ctrl+c to exit from calculator...\n");

    while(1)
    {
        printf("> ");
        fgets(str, MAX_SIZE, stdin);
        if(str[0] == 'q')
            break;
        int size = len(str);

        int i = 0, j = 0;

        while (i < size) {
            int ch = str[i];
            if (ch != 32) {
                str[j++] = str[i];
            }
            i++;
        }
        str[j] = '\0';

        size = len(str);

        Number* res = evaluate(str, size - 1);

        if(res)
        {
            if(res -> sign == '-' && !isZero(res -> head))
                printf("%c",res -> sign);
            
            // displayReverse(res -> head);
            displayNumber(res -> head, res -> count);
            printf("\n");
        }
       
    
    }

    return 0;
}

// 4504125/3

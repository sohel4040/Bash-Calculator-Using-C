#include<stdio.h>
#include<string.h>

#define MAX_SIZE 5000

int main()
{
    char str[MAX_SIZE];
    fgets(str, MAX_SIZE, stdin);
    // scanf("%s",str);

    int size = strlen(str);

    printf("The size is : %d\n",size);

}
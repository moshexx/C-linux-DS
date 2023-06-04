#include<stdio.h>

void main()
{
    int a,b;

    a=(-1,0,1);
    b=a++;

    printf("%d %d", a, b);
}
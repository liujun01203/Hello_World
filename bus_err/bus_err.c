#include <string.h>
#include <stdio.h>
void main()
{
    char buf[256];
    int *x;
    x = (int *) & buf[1];
    *x = 68000;
    printf("*x = %d\n",*x);
}

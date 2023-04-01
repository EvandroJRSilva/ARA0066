#include <stdio.h>

void main()
{
    int a, *p;

    a = 5;
    p = &a;

    printf("Valor de a antes de ser modificado: %d;\n", a);
    
    *p = 10;

    printf("Valor de a depois de ser modificado: %d;\n", a);
}
#include <stdio.h>

void main()
{
    int a, *p;

    a = 5;
    p = &a;

    printf("Valor de a: %d;\n", a);
    printf("Valor de p: %p;\n", p);
    printf("Valor da variável apontada por p: %d\n", *p);
}
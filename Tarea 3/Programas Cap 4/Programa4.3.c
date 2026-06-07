#include <stdio.h>

/* Conflicto de variables con el mismo nombre. */

void f1(void);      /* Protatipo de funcion. */
int K = 5;          /* Variable global. */

void main(void)
{
    int I;
    for (I=1; I<=3; I++)
    {
        f1();
    }
}
void f1(void)
/* Lafuncion utliza tanto la variable local K como la variable
global K. */
{
    int K = 2;          /* VAriable local. */
    K += K;
    printf("\n\nEl valor de la variable local es: %d", K);
    ::K = ::K + K;      /* Uso de ambas variables. */
    printf("\nEl valor de la variable global es: %d", ::K);
}

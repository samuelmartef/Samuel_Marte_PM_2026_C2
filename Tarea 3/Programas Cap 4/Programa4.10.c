#include <stdio.h>

/* Multiplo
El programa al recibir como datos dos numeros enteros determina
si el segundo es multiplo del primero */

int multiplo(int, int);     /* Prototipo de funcion*/

void main(void)
{
    int NU1, NU2, RES;
    printf("\nIngrese los dos numeros:");
    scanf("%d %d", &NU1, &NU2);
    RES = multiplo(NU1, NU2);
    if (RES)
    {
        printf("\nEL segundo numero es el multiplo del primero");
    }
    else
    {
        printf("\nEL segundo numero no es el multiplo del primero");
    }
}

int multiplo(int N1, int N2)
/* esta funcion determina se N2 es multiplo de N1 */
{
    int RES;
    if ((N2 % N1) == 0)
    {
        RES = 1;
    }
    else
    {
        RES = 0;
    }
    return(RES);
}

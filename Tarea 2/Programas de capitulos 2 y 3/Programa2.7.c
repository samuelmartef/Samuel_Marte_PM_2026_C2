#include <stdio.h>

/* Ventas descendentes.
El programa, al recibir como datos tres valores que representan las ventas de los vendedores de una tienda de discos, escribe las ventas en
orden descendente.

P, S y R: Variables de tipo real. */

void main(void)
{
float P, S, R, i;
printf("Ventas vendedor 1: ");
scanf("%f", &P);
printf("Ventas vendedor 2: ");
scanf("%f", &S);
printf("Ventas vendedor 3: ");
scanf("%f", &R);


if (P > S)
    if (P > R)
        if (S > R)
            printf("\n\n El orden es P, S y R: %8.2f %8.2f %8.2f", P, S, R);
        else
            printf("\n\n El orden es P, R y S: %8.2f %8.2f %8.2f", P, R, S);
    else
        printf("\n\n El orden es R, P y S: %8.2f %8.2f %8.2f", R, P, S);
else
    if (S > R)
        if (R > P)
            printf("\n\n El orden es S, R y P: %8.2f %8.2f %8.2f", S, R, P);
        else
            printf("\n\n El orden es S, P y R: %8.2f %8.2f %8.2f", S, P, R);
    else
        printf("\n\n El orden es R, S y P: %8.2f %8.2f %8.2f", R, S, P);

}

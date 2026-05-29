#include <stdio.h>

#include <math.h>

/* Funcion matematica.
El programa obtiene el resultado de una funcion.

OP y T: Variables de tipo entero.
RES: Variaeble de tipo rela. */

void main(void)
{
int OP, T;
float RES;
printf("Ingrese la opcion del calculo y el valor entero\n(Opcion del 1 al 4): ");
scanf("%d %d", &OP, &T);
switch(OP)
{
    case 1: RES = T / 5;
        break;
    case 2: RES = pow(T,T);
        break;
    case 3:
    case 4: RES = 6 * T/2;
        break;
    default: RES = 1;
        break;
}
printf("\nResultado: %7.2f", RES);
}

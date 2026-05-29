#include <stdio.h>

/* Billete de ferrocarril.
El programa calcula el costo de un billete de ferrocarril teniendo en
cuenta la distancia entre las dos ciudades y el tiempo de permanencia
del pasajero.

DIS y TIE: Variables de tipo entero.
BIL: Variable de tipo rela. */

void main(void)
{
int DIS, TIE;
float BIL;
printf("Ingrese la distancia entre ciudades y el tiempo de estacia: ");
scanf("%d %d", &DIS, &TIE);
if (DIS*2 > 500 && TIE > 10)
    BIL = ((DIS*2) * 0.19) - (((DIS*2) * 0.19)*0.20);
else
    BIL = (DIS*2) * 0.19;
printf("\nEl precio es: %0.2f\tDistancia: %d\tTiempo: %d", BIL, DIS, TIE);
}

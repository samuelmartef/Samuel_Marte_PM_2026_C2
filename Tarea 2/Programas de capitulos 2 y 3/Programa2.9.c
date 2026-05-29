#include <stdio.h>
#include <math.h>

/* Expresion.
El rpograma, al recibir como datos tres valores enteros, establecer si los
mismos satisfacen una expresion determinada.

R, T y Q: VAriable de tipo entero.
RES: Variable de tipo real. */

void main(void)
{
int R, T, Q;
float RES;
printf("Ingrese los valores de R, T y Q: ");
scanf("%d %d %d", &R, &T, &Q);
RES = pow(R, 4) - pow(T, 3) + 4 * pow(Q, 2);
if (RES < 820)
    printf("%d\nR = %d\t T = %d\t Q = %d", R, T, Q);
}

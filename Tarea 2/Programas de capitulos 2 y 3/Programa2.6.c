#include <stdio.h>

/* Incremento de salario.
El programa, al recibir como dato el nivel de un profesor, incrementa su
salario en funcion de la tabla 2.3.

NIV: Variable de tipo entero.
SAL: Variable de tipo real. */

void main(void)

{
int NIV;
float SAL;
printf("Ingrese el nivel academico del profesor: ");
scanf("%d", &NIV);
printf("Ingrese el Salario: ");
scanf("%f", &SAL);

switch(NIV)
{
    case 1: SAL = SAL * 1.035;  break;
    case 2: SAL = SAL * 1.041;  break;
    case 3: SAL = SAL * 1.048;  break;
    case 4: SAL = SAL * 1.053;  break;
}
printf("\n\nNivel: %d \tNuevo salario es de: %8.2f",NIV, SAL);
}

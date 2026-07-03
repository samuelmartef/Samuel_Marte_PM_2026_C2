#include <stdio.h>

/*Archivo y caracteres
El programa escribe caracteres en un archivo*/

void main(void)
{
char p1;
FILE *ar;
ar = fopen("C:\\Users\\samue\\Desktop\\PROGRAMACION PARA MECA\\Calculadora\\archi.txt", "w");     /*Se abre el archivo arc.txt paraescritura.*/
if (ar != NULL)
{
    while ((p1 = getchar()) != '\n')
    /*Se escribe caracteres en el archivo mientras no se detecte el caracter
    que indica el fin de la linea*/
        fputc(p1, ar);
    fclose(ar);     /*Se cierra el archivo*/
}
else
    printf("No se puede abrir el archivo");
}
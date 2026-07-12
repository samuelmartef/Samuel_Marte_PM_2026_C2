#include <stdio.h>

/*Incrementa salarios
El prorama incrementa el salario de los empleados de una emoresa
-actualiza el archivo correspondiente- si sus ventas son superiores al millon de pesos anuales*/

typedef struct      /*Declaracion de la estructura empleado*/
{
    int calve;
    int departamento;
    float salario;
    float ventas[12];
}empleado;

void incrementa(FILE *);        /*Prototipo de funcion*/

void main(void)
{
FILE *ar;
if ((ar = fopen("ad5.dat", "r+")) != NULL)
/*El archivo se abre en la modalidad para leer y escribir*/
    incrementa(ar);
else
    printf("\nEl archivo no se puede abrir");

rewind(ar);
/*La funcion rewind se utiliza para posicionarnos en el inicio del
archivo cada vez que sea necesatiro. En este programa no tien ninguna
utilidad, solo se exscribio para explicar su uso*/
fclose(ar);
}

void incrementa(FILE *ap)
/*Esta funcion se utiliza para incrementar el salario de todos aquellos
empleados que hayan tenido ventas por mas de 1000000
Actualiza ademas el archivo correxpondiente*/
{
int i, j, t;
float sum;
empleado emple;

t = sizeof(empleado);
/*La funcion sizeof se utiliza para conocer el tamano de la estructura
empleado*/

fread(&emple, sizeof(empleado), 1, ap);     /*Se lee el primer registro del archivo*/

while (!feof(ap))
{
    i = ftell(ap) / t;
    /*La funcion ftell se utiliza para conocer la posicion de nuestro apuntador
    en el archivo. La variable i nos porporciona en este caso
    el tamano de todos los bloques que existen debajo de nuestra
    posicion. Si conocemos el tamno de cada bloque , entonces podemos
    obtener el numero de bloques que hay exactamente debajo de nuestra
    posicion*/

    sum = 0;
    for (j=0; j<12; j++)
        sum += emple.ventas[j];     /*Se calculan las ventas de cada vendedor*/
    if (sum > 1000000)
    {
        emple.salario = emple.salario *1.10;    /*Se encrementa el salario*/
        fseek(ap, (i-1)*sizeof(empleado), 0);
        /*Nos posicionamos nuevamente para leer el siguiente registro
        Esta instruccion no deberia ser necesaria, pero la funcion
        fwrite se comporta a veces de manera inestable en algunos
        compiladores de C. Para asegurarnos que siemore funcione correctamente
        realizamos este nuevo reposicionamiento*/
    }
    fread(&emple, sizeof(empleado), 1, ap);
}
}

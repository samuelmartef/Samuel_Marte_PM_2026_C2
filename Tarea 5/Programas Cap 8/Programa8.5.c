#include <stdio.h>
#include <string.h>

/*Union 
El programa muestra la manera como se declara una union, asi como la forma de
acceso a los campos de las variables de tipo union tanto casignacion de valores 
como para lestura y escritura*/

union datos     /*Declaracion de una unnion*/
{
    char celular[15];
    char correo[20];
};

typedef struct      /*Declaracion de una estructura utilizando typedef*/
{
    int matricula;
    char nombre[20];
    char carrera[20];
    float promedio;
    union datos personales;
    /*Observa que uno de los campos de la estructura alumno es una union*/

}alumno;

void Lectura(alumno *a);     /*Prototipo de funcion*/

void main(void)
{
alumno a1 = {120, "Maria", "Contabilidada", 8.9, "5-158-40-50"}, a2, a3;
/*Observa que solo el primer componente de una union puede recibir valores por
medio de este tipo de asignaciones*/

/*Para que puedas observar las diferentes formas e que los ampos de las varaibles
de tipo estructura alumno reciben valores, ingresamos los valores
de los campos de tres formas diferentes. Los campos de a1 reciben valores
directamente, los campos de a2 se leen en el programa principal, y los campos
de a3 reciben valores a traves de una funcion. */
printf("Alumno 2\n");
printf("Ingrese la matricula: ");
scanf("%d", &a2.matricula);
fflush(stdin);
printf("Ingrese el nombre: ");
gets(a2.nombre);
fflush(stdin);
printf("Ingrese la carrera: ");
gets(a2.carrera);
printf("Ingrese el promedio: ");
scanf("%f", &a2.promedio);
fflush(stdin);
printf("Ingrese el correo electronico: ");
gets(a2.personales.correo);
/*Observa que la variable a2 de tipo estructura alumno el segundo campo de la
union recibe un valor. */

printf("Alumno 3\n");
Lectura(&a3);   /*Se llama a una funcion para leer los campos de la cariable a3*/

/*impresion de resultados*/
printf("\nDatos del alumno\n");
printf("%d\n", a1.matricula);
puts(a1.nombre);
puts(a1.carrera);
printf("%.2f\n", a1.promedio);
puts(a1.personales.celular);
/*Obserca que escribe el valor de telefono celular asignado. */
puts(a1.personales.correo);
/*Observa que se tratamos de imprimir el campo correo, escribe basura.*/
}
#include <stdio.h>

void main(void)
{
char *cad0 = "Buenos dias";     /*En este caso se asigana 11 caracteres mas el
caracter de terminacion '\0' a la posicion de memoria a la que apunta la variable
cad0 -apuutador del tipo cadena de caracteres. */

char cad1[20] = "Hola";     /*Se asigna cuatro caracteres mas el caracter
de terminancion a la variable tipo char cad1. Observa que cad1 tiene espacio
para 20 caracteres.*/

char cad2[] = "Mexico";     /*En este caso se asigna seis caracteres (mas
el caracter de terminacion) a la variable cad2. Observa que cad2 no tiene espacio
reservado como cad1; por lo tanto. acepta cualquier numero de caracteres. */

char cad3[] = {'B', 'i', 'e', 'n', 'v', 'e', 'n', 'i', 'd', 'o', '\0'};
/*Observa otra forma de asignacion de valores a la variable cad3.*/

char cad4[20], cad5[20], cad6[20];

printf("\nLa cadena cad0 es: ");
puts(cad0);
/*La funcion puts es la mas apropiada para escribir cadenas de caracteres.
Observa que esta funcon baja automaticamente una linea despues de imprimir
la cadena. */
printf("\nLa cadena cad1 es: ");
printf("%s", cad1);
/*La funcion printf, con el formato de variable %s, tambien se puede utilizar
para escribir cadenas de caracteres. Baja automaticamente una linea despues de 
escribir la cadena.*/

printf("\nLa cadena cad2 es: ");
puts(cad2);
printf("\nLa cadena cad3 es: ");
puts(cad3);

printf("\nIngrese una linea de texto - se lee con gets-: \n");
/*Lafuncon gets es la mas apropiada para leer cadenas de caracteres. */
gets(cad4);
printf("\nLa cadena cad3 es:");
puts(cad3);

printf("\nIngrese una linea de texto -se lee con scanf-: \n");
/*La funcion scanf, con el formato de variable %s, tambien se puede utilizar
para leer una cadena de caracteres, aunque con algunas restricciones . Si la
cadenas esta foramda par varias palabras solo lee la primera. Por ejemplo, si queremos ingresar la cadenas "Buenos dias", solo lee la palabra "Buenos", por
ello esta funcion unicamente es util si conocemos con anticipacion que la
cadenas que vamos a leer esta formada por una sola palabra.*/
printf("\nLa cadena cad5 es: ");
printf("%s", cad5);
fflush(stdin);

char p;
int i = 0;
/*La declaracion de variables siempre se debe realizar en la parte inicial del
programa. En este caso se colocan en esta seccion (char p e int i = 0) para
que puedas observar la relacion directa con las lineas de programacion que se
muestras a continuacion. */
printf("\nIngrese una linea de texto -se lee cada caracter con getchar-: ");
/*Se utiliza la funcion getchar para leer caracteres de la linea de texto y 
asignarlos a la variable de tipo cadena de caracteres cad6. Observa que se leen
caracteres minetras no ese encuentre al caracter que indica fin de linea '\n'. */

while((p = getchar()) != '\n')
    cad6[i++] = p;
cad6[i] = '\0';
/*Al final de la cadena se incorpora el caracter de terminancion NULL
para indicar el fin de la misma. */
printf("\nLa cadena cad6 es: ");
puts(cad6);
}
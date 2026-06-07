#include <stdio.h>

/* Prueba de variables globales, locales y estaticas.
El programa utiliza funciones en las que se usan diferentes tipos de
variables. */

int f1(void);
int f2(void);
int f3(void);
int f4(void);

int K = 3;
void main(void)
{
    int I;
    for (I=1; I<=3; I++)
    {
        printf("\nEl resultado de la funcion f1 es: $d", f1());
        printf("\nEl resultado de la funcion f2 es: $d", f1());
        printf("\nEl resultado de la funcion f3 es: $d", f1());
        printf("\nEl resultado de la funcion f4 es: $d", f1());
    }
}

int f1(void)
/*La funcion f1 utiliza la varieble global. */
{
    K += K;
    return(K);
}
int f2(void)
/*La funcion f2 utiliza la varieble local. */
{
    int K = 1;
    K++;
    return(K);
}
int f3(void)
/*La funcion f3 utiliza la varieble estatica. */
{
    static int K = 8;
    K += 2;
    return(K);
}
int f4(void)
/*La funcion f4 utiliza dos variables con el mismo nombre: local
y global. */
{
    static int K = 8;
    K = K + ::K;        /*Uso de la variable local (K) y global (::K) */
    return(K);
}

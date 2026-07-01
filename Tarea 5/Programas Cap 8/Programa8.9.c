#include <stdio.h>
#include <string.h>

/*Bienes raices
El programa maneja informacion sobre las propiedades que tiene una empresa de bienes raices de la
ciudad de Lima, Peru, tanto para venta como para renta*/

typedef struct      /*Declaracion de la estructura ubicacion*/
{
    char zona[20];
    char calle[20];
    char colo[20];     /*Colonia*/
}ubicacion;

typedef struct      /*Declaracion de la estructura propiedades*/
{
    char clave[5];
    float scu;      /*Superficie cubierta*/
    float ste;      /*Superficie terreno*/
    char car[50];   /*Caracteristicas*/
    ubicacion ubi;  /*Observa que este campo es de tipo estructura ubicacion*/
    float precio;
    char dispo;     /*Disponibilidad*/
}propiedades;

void Lectura(propiedades *, int);
void F1(propiedades *, int);
void F2(propiedades *, int);

void main(void)
{
propiedades PROPIE[100];
/*Se declara un arreglo unidimensional de tipo estructura propiedades*/
int TAM;
do
{
    printf("Ingrese el numero de propiedades: ");
} while (TAM > 100 || TAM < 1);
/*Se veridica que el tamano del arreglo sea correcto*/
Lectura(PROPIE, TAM);
F1(PROPIE, TAM);
F2(PROPIE, TAM);
}

void Lectura(propiedades A[], int T)
/*Esta funcion se utiliza para leer un arreglo unidimensional de tipo
estructura propiedades de T elementos*/
{
int I;
for (I=0; I<T; I++)
{
    printf("\n\tIngrese datos de la propiedad %d", I + 1);
    printf("\nClave: ");
    fflush(stdin);
    gets(A[I].clave);
    printf("Superficie cubierta: ");
    scanf("%f", &A[I].scu);
    printf("Superficie terreno: ");
    scanf("%f", &A[I].ste);
    printf("Características: ");
    fflush(stdin);
    gets(A[I].car);
    printf("\tZona: ");
    fflush(stdin);
    gets(A[I].ubi.zona);
    printf("\tCalle: ");
    fflush(stdin);
    gets(A[I].ubi.calle);
    printf("\tColonia: ");
    fflush(stdin);
    gets(A[I].ubi.colo);
    printf("Precio: ");
    scanf("%f", &A[I].precio);
    printf("Disponibilidad (Venta-V Renta-R): ");
    scanf("%c", &A[I].dispo);
}
}

void F1(propiedades A[], int T)
/*Esta funcion se utiliza para generar un listado de las propiedades
disponibles para venta en la zona de Miraflores, cuyo valor oscila entre
450000 y 650000 nuevos soles*/
{
int I;
printf("\n\t\tListado de Propiedades para ventas de Miraflores");
for (I=0; I<T; I++)
    if ((A[I].dispo == 'V') && (strcmp (A[I].ubi.zona, "Miraflores") == 0))
        if ((A[I].precio >= 450000) && (A[I].precio <= 650000))
            {
                printf("\nClave de la propiedad: ");
                puts(A[I].clave);
                printf("\nSuperficie cubierta: %f", A[I].scu);
                printf("\nnSuperficie terremo: %f ", A[I].ste);
                printf("\Caractereisticas: ");
                puts(A[I].car);
                printf("\nCalle: ");
                puts(A[I].ubi.calle);
                printf("\nColonia: ");
                puts(A[I].ubi.colo);
                printf("\nPrecio: %.2f\n ", A[I].precio);
                
            }
}

void F2(propiedades A[], int T)
/*Al recibir como datos una zona geografica de Lima, Peru y un cierto rango
respecto al monto, esta funcion genera un listado de todas las propiedades
disponibles para renta*/
{
int I;
float li, ls;
char zon[20];
printf("\n\t\tListado de Propiedades para REnta");
printf("\nIngrese zona geografica: ");
fflush(stdin);
gets(zon);
printf("Ingrese el limete inferior del precio: ");
scanf("%f", &li);
printf("Ingrese el limete superior del precio: ");
scanf("%f", &ls);
for (I=0; I<T; I++)
    if ((A[I].dispo == 'R') && (strcmp(A[I].ubi.zona, zon) == 0))
        if ((A[I].dispo == 'R') && (A[I].precio <= ls))
        {
            printf("\nClave de la propiedad: ");
            puts(A[I].clave);
            printf("\nSuperficie cubierta: %d", A[I].scu);
            printf("\nSuperficie terreno: %d", A[I].ste);
            printf("\nCaracteristicas: ");
            puts(A[I].car);
            printf("\nCalle: ");
            puts(A[I].ubi.calle);
            printf("\nColonia: ");
            puts(A[I].ubi.colo);
            printf("\nPrecio: %.2f", A[I].precio);
        }
}


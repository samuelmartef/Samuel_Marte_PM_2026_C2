#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*Crear un programa que lea un archivo XML con una cantidad de elementos 
n y cree un array con memoria dinámica para guardarlos en memoria e imprimirlos. 
Es decir primero verifican la cantidad de elementos y después crean la memoria 
para cargarlos.*/

typedef struct        /*Estructura alumno*/
{
    char nombre[20];
    char apellido[20];      /*Declaracion de la estructura*/
    int matricula;
    float promedio;
}alumno;

void main(void)
{
FILE *ar;
if ((ar = fopen("alumnos.json", "r+")) != NULL)
{
alumno *lista = NULL;
int capacidad = 2;
int cantidad = 0;
lista = (alumno *)malloc(capacidad * sizeof(alumno));

if (lista == NULL)
{
    printf("No se pudo reservar la memoria");
    free(lista);
    fclose(ar);
}
char linea[256];
alumno temporal;
while (fgets(linea, sizeof(linea), ar))
{
    if (strstr(linea, "}"))
    {
        if (cantidad >= capacidad) 
        {
            capacidad *= 2; /* Duplicamos la capacidad (de 2 a 4, 4 a 8, etc.)*/
            lista = (alumno *) realloc(lista, capacidad * sizeof(alumno));
            if (lista == NULL) 
                printf("Error al reasignar memoria.\n");
        }
        lista[cantidad] = temporal;
        cantidad++;
    }
    else if (strstr(linea, "\"nombre\""))
    {
        char *dos_puntos = strstr(linea, ":");
        if (dos_puntos) 
            sscanf(dos_puntos, ": \"%[^\"]\"", temporal.nombre);
    }
    else if (strstr(linea, "\"apellido\""))
    {
        char *dos_puntos = strstr(linea, ":");
        if (dos_puntos) 
            sscanf(dos_puntos, ": \"%[^\"]\"", temporal.apellido);
    }
    else if (strstr(linea, "\"matricula\"")) 
    {
        char *dos_puntos = strstr(linea, ":");
        if (dos_puntos) 
            sscanf(dos_puntos, ": %d", &temporal.matricula);
    }
    else if (strstr(linea, "\"promedio\""))
    {
        char *dos_puntos = strstr(linea, ":");
        if (dos_puntos) 
            sscanf(dos_puntos, ": %f", &temporal.promedio);
    }
}
    
    fclose(ar);
    printf("=== DATOS EXTRAIDOS DEL XML ===\n");
    printf("Total de alumnos procesados: %d\n\n", cantidad);
    
    for (int i = 0; i < cantidad; i++) 
    {
        printf("Alumno %d:\n", i + 1);
        printf("  Nombre completo: %s %s\n", lista[i].nombre, lista[i].apellido);
        printf("  Matricula:       %d\n", lista[i].matricula);
        printf("  Promedio:        %.2f\n", lista[i].promedio);
        printf("-------------------------------\n");
    }
    free(lista);
}
else
    printf("No se puede abrir el archivo");
}
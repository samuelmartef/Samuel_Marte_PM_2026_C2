#include <stdio.h>
#include <math.h>

// Variable global para llevar la cuenta de los movimientos
int contador = 0;

// Se actualiza la función para recibir un puntero al archivo
void hanoi(int n, char ini, char fin, char ayu, FILE *archivo);

int main() {
    int dis;
    FILE *archivo; // Puntero para manejar el archivo de texto

    do {
        printf("Cuantos discos quiere: ");
        scanf("%d", &dis);
        if (dis <= 0) {
            printf("Error esto no va \n");
        }
    } while (dis <= 0);

    // Creamos y abrimos el archivo en modo escritura ("w" = write)
    archivo = fopen("movimientos_hanoi.txt", "w");
    
    // Verificamos que el archivo se haya creado correctamente
    if (archivo == NULL) {
        printf("Error al crear el archivo.\n");
        return 1; // Salir con error
    }

    printf("\nEjecutando y guardando en 'movimientos_hanoi.txt'...\n");
    
    // Escribimos el encabezado en el archivo
    fprintf(archivo, "Movimientos para %d discos:\n", dis);

    // Llamamos a la función pasándole el puntero del archivo
    hanoi(dis, 'A', 'B', 'C', archivo);
    
    int total_movimientos = (int)pow(2, dis) - 1;
    
    // Guardamos el total de movimientos en el archivo
    fprintf(archivo, "\nTotal de movimientos realizados: %d\n", total_movimientos);
    
    // Cerramos el archivo para guardar los cambios correctamente (muy importante)
    fclose(archivo);
    
    printf("\nTotal de movimientos: %d\n", total_movimientos);
    printf("El archivo 'movimientos_hanoi.txt' se ha creado exitosamente\n");
    
    return 0;
}

void hanoi(int n, char ini, char fin, char ayu, FILE *archivo) {
    if (n == 1) {
        contador++;
        // Escribe en el archivo
        fprintf(archivo, "%d) Mover disco 1 de %c a %c\n", contador, ini, fin);
        // También lo muestra en consola para que veas el progreso
        printf("%d) Mover disco 1 de %c a %c\n", contador, ini, fin);
        return;
    }
    
    hanoi(n - 1, ini, ayu, fin, archivo);
    
    contador++;
    // Escribe en el archivo
    fprintf(archivo, "%d) Mover disco %d de %c a %c\n", contador, n, ini, fin);
    // También lo muestra en consola
    printf("%d) Mover disco %d de %c a %c\n", contador, n, ini, fin);
    
    hanoi(n - 1, ayu, fin, ini, archivo);
}
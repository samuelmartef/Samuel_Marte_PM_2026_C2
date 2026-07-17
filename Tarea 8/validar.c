#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

// Solo necesitamos stb_image.h para validar leyendo el archivo
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main() {
    DIR *d;
    struct dirent *dir;
    char archivos[100][256];
    int contador = 0;

    
    d = opendir(".");
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            
            if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0) {
                strcpy(archivos[contador], dir->d_name);
                contador++;
                if (contador >= 100) break; // Límite de seguridad
            }
        }
        closedir(d);
    }

    if (contador == 0) {
        printf("No se encontraron archivos en la carpeta actual.\n");
        return 1;
    }

    printf("--- VALIDADOR DE ARCHIVOS DE IMAGEN ---\n");
    for (int i = 0; i < contador; i++) {
        printf("%d. %s\n", i + 1, archivos[i]);
    }

    int seleccion;
    printf("\nSelecciona el numero del archivo que deseas validar: ");
    scanf("%d", &seleccion);

    if (seleccion < 1 || seleccion > contador) {
        printf("Seleccion no valida.\n");
        return 1;
    }

    char *archivo_elegido = archivos[seleccion - 1];

    
    char *extension = strrchr(archivo_elegido, '.');

    if (extension == NULL || 
        (strcmp(extension, ".png") != 0 && strcmp(extension, ".PNG") != 0 &&
         strcmp(extension, ".jpg") != 0 && strcmp(extension, ".JPG") != 0 &&
         strcmp(extension, ".bmp") != 0 && strcmp(extension, ".BMP") != 0)) {
        
        // Mensaje exacto si la extensión no es válida
        printf("\nEl archivo %s tiene extension %s, no se puede procesar.\n", 
               archivo_elegido, 
               extension ? extension : "desconocida (sin punto)");
        return 1; 
    }

    
    printf("\nExtension aceptada. Verificando el contenido de %s...\n", archivo_elegido);
    
    int ancho, alto, canales;
    
    unsigned char *img = stbi_load(archivo_elegido, &ancho, &alto, &canales, 0);

    if (img == NULL) {
        printf("ERROR: El archivo %s paso la prueba de extension, pero su contenido no es una imagen valida o esta corrupto.\n", archivo_elegido);
        return 1;
    }

    
    printf("Exito el archivo %s es una imagen real y valida.\n", archivo_elegido);
    printf("Detalles -> Ancho: %dpx, Alto: %dpx, Canales: %d\n", ancho, alto, canales);

    
    stbi_image_free(img);

    return 0;
}
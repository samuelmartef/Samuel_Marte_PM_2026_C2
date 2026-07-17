#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


int es_imagen(const char *nombre) {
    const char *ext = strrchr(nombre, '.');
    if (!ext) return 0;
    return (strcmp(ext, ".jpg") == 0 || strcmp(ext, ".png") == 0 || strcmp(ext, ".bmp") == 0 ||
            strcmp(ext, ".JPG") == 0 || strcmp(ext, ".PNG") == 0 || strcmp(ext, ".BMP") == 0);
}

int main() {
    DIR *d;
    struct dirent *dir;
    char archivos[100][256]; 
    int contador = 0;

    
    d = opendir("."); 
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if (es_imagen(dir->d_name)) {
                strcpy(archivos[contador], dir->d_name);
                contador++;
            }
        }
        closedir(d);
    }

    if (contador == 0) {
        printf("No se encontraron imagenes en la carpeta actual.\n");
        return 1;
    }

    
    printf("--- CONVERSOR A BLANCO Y NEGRO ---\n");
    for (int i = 0; i < contador; i++) {
        printf("%d. %s\n", i + 1, archivos[i]);
    }
    
    int seleccion;
    printf("\nSelecciona el numero de la imagen: ");
    scanf("%d", &seleccion);

    if (seleccion < 1 || seleccion > contador) {
        printf("Seleccion no valida.\n");
        return 1;
    }

    char *archivo_elegido = archivos[seleccion - 1];
    printf("Procesando %s...\n", archivo_elegido);

    
    int ancho, alto, canales;
    
    unsigned char *img = stbi_load(archivo_elegido, &ancho, &alto, &canales, 0);

    if (img == NULL) {
        printf("Error al cargar la imagen.\n");
        return 1;
    }

    
    size_t tamano_img = ancho * alto * canales;
    
    
    for (unsigned char *p = img; p < img + tamano_img; p += canales) {
        
        unsigned char gris = (unsigned char)(0.299 * p[0] + 0.587 * p[1] + 0.114 * p[2]);
        
        p[0] = gris;
        p[1] = gris;
        p[2] = gris;
        
    }

    
    char nombre_salida[300];
    sprintf(nombre_salida, "byn_%s", archivo_elegido);

    if (strstr(archivo_elegido, ".png") || strstr(archivo_elegido, ".PNG")) {
        stbi_write_png(nombre_salida, ancho, alto, canales, img, ancho * canales);
    } else if (strstr(archivo_elegido, ".jpg") || strstr(archivo_elegido, ".JPG")) {
        stbi_write_jpg(nombre_salida, ancho, alto, canales, img, 100); // 100 es la calidad
    } else if (strstr(archivo_elegido, ".bmp") || strstr(archivo_elegido, ".BMP")) {
        stbi_write_bmp(nombre_salida, ancho, alto, canales, img);
    }

    printf("Exito! Imagen guardada como %s\n", nombre_salida);

    
    stbi_image_free(img);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOMBRE 100
#define ARCHIVO_EMPRESAS "empresas.txt"

// Estructura para Empresa
typedef struct {
    char nombre[MAX_NOMBRE];
} Empresa;

// Estructura que representa un Riesgo bajo el Metodo Mosler
typedef struct {
    int id;
    char nombre[MAX_NOMBRE];
    // Criterios Mosler (Puntuacion de 1 a 5)
    int F;  // Funcion
    int S;  // Sustitucion
    int P;  // Profundidad
    int E;  // Extension
    int A;  // Agresion
    int V;  // Vulnerabilidad
    // Valores calculados
    int I;  // Importancia (F * S)
    int D;  // Danos (P * E)
    int C;  // Caracter del riesgo (I + D)
    int Pb; // Probabilidad (A * V)
    int ER; // Estimacion del Riesgo (C * Pb)
} Riesgo;

// --- FUNCIONES AUXILIARES Y VALIDACIONES ---

// Determinar la clase de riesgo segun la escala de ER del Metodo Mosler
const char* obtenerClaseRiesgo(int er) {
    if (er >= 2 && er <= 250) return "Muy Pequeno";
    if (er >= 251 && er <= 500) return "Pequeno";
    if (er >= 501 && er <= 750) return "Normal";
    if (er >= 751 && er <= 1000) return "Grande";
    if (er >= 1001 && er <= 1250) return "Elevado";
    return "Fuera de Rango";
}

// Validar que la puntuacion de un criterio este strictly entre 1 y 5
int leerCriterio(const char *mensaje) {
    int valor;
    do {
        printf("%s", mensaje);
        if (scanf("%d", &valor) != 1) {
            while (getchar() != '\n'); // Limpiar buffer de entrada si ingresan letras
            valor = 0;
        }
        if (valor < 1 || valor > 5) {
            printf(">> Error: El valor debe estar entre 1 y 5. Intente de nuevo.\n");
        }
    } while (valor < 1 || valor > 5);
    return valor;
}

// Calcular formulas automaticas del Metodo Mosler
void calcularMosler(Riesgo *r) {
    r->I = r->F * r->S;
    r->D = r->P * r->E;
    r->C = r->I + r->D;
    r->Pb = r->A * r->V;
    r->ER = r->C * r->Pb;
}

// Formatea el nombre del archivo CSV individual por empresa
void obtenerNombreArchivoRiesgos(const char *empresa, char *buffer) {
    snprintf(buffer, 256, "%s_riesgos.csv", empresa);
}

// --- GESTION DINAMICA DE EMPRESAS ---

// Carga en memoria dinamica la lista de empresas desde "empresas.txt"
Empresa* cargarEmpresas(int *cantidad) {
    FILE *archivo = fopen(ARCHIVO_EMPRESAS, "r");
    *cantidad = 0;
    if (!archivo) {
        return NULL;
    }

    Empresa *lista = NULL;
    Empresa temp;

    while (fscanf(archivo, " %[^\n]", temp.nombre) == 1) {
        (*cantidad)++;
        Empresa *ptrTemp = (Empresa*) realloc(lista, (*cantidad) * sizeof(Empresa));
        if (!ptrTemp) {
            printf("Error: Memoria insuficiente al cargar empresas.\n");
            free(lista);
            fclose(archivo);
            return NULL;
        }
        lista = ptrTemp;
        lista[*cantidad - 1] = temp;
    }

    fclose(archivo);
    return lista;
}

// Despliega las empresas registradas y permite seleccionar una mediante un numero
int seleccionarEmpresa(char *empresaSeleccionada) {
    int cantidad = 0;
    Empresa *lista = cargarEmpresas(&cantidad);

    if (cantidad == 0 || !lista) {
        printf("\n>> Error: No hay empresas creadas. Primero debes agregar una empresa (Opcion 1).\n");
        return 0;
    }

    printf("\n--- SELECCIONE UNA EMPRESA ---\n");
    for (int i = 0; i < cantidad; i++) {
        printf("%d. %s\n", i + 1, lista[i].nombre);
    }

    int seleccion = 0;
    do {
        printf("Seleccione el numero de la empresa (1 - %d): ", cantidad);
        if (scanf("%d", &seleccion) != 1) {
            while (getchar() != '\n');
            seleccion = 0;
        }
    } while (seleccion < 1 || seleccion > cantidad);

    strcpy(empresaSeleccionada, lista[seleccion - 1].nombre);
    free(lista);
    return 1;
}

// --- GESTION DINAMICA DE RIESGOS EN CSV ---

// Carga en memoria dinamica los riesgos del CSV de la empresa seleccionada
Riesgo* cargarRiesgos(const char *empresa, int *cantidad) {
    char nombreArchivo[256];
    obtenerNombreArchivoRiesgos(empresa, nombreArchivo);

    FILE *archivo = fopen(nombreArchivo, "r");
    *cantidad = 0;
    if (!archivo) {
        return NULL;
    }

    Riesgo *riesgos = NULL;
    Riesgo temp;

    while (fscanf(archivo, "%d,%99[^,],%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
                  &temp.id, temp.nombre, &temp.F, &temp.S, &temp.P, &temp.E,
                  &temp.A, &temp.V, &temp.I, &temp.D, &temp.C, &temp.Pb, &temp.ER) == 13) {
        
        (*cantidad)++;
        Riesgo *ptrTemp = (Riesgo*) realloc(riesgos, (*cantidad) * sizeof(Riesgo));
        if (!ptrTemp) {
            printf("Error: Memoria insuficiente al cargar riesgos.\n");
            free(riesgos);
            fclose(archivo);
            return NULL;
        }
        riesgos = ptrTemp;
        riesgos[*cantidad - 1] = temp;
    }

    fclose(archivo);
    return riesgos;
}

// Guarda los riesgos en el archivo CSV de la empresa
void guardarRiesgos(const char *empresa, Riesgo *riesgos, int cantidad) {
    char nombreArchivo[256];
    obtenerNombreArchivoRiesgos(empresa, nombreArchivo);

    FILE *archivo = fopen(nombreArchivo, "w");
    if (!archivo) {
        printf("Error al abrir el archivo CSV para guardar datos.\n");
        return;
    }

    for (int i = 0; i < cantidad; i++) {
        fprintf(archivo, "%d,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
                riesgos[i].id, riesgos[i].nombre,
                riesgos[i].F, riesgos[i].S, riesgos[i].P, riesgos[i].E,
                riesgos[i].A, riesgos[i].V,
                riesgos[i].I, riesgos[i].D, riesgos[i].C, riesgos[i].Pb, riesgos[i].ER);
    }

    fclose(archivo);
}

// Muestra la lista general de riesgos en formato tabla incluyendo la Clase de Riesgo
void listarRiesgos(Riesgo *riesgos, int cantidad) {
    printf("\n----------------------------------------------------------------------------------------\n");
    printf("%-4s | %-20s | F S P E A V | I   D   C   Pb  ER   | Clase de Riesgo\n", "ID", "Riesgo");
    printf("----------------------------------------------------------------------------------------\n");
    for (int i = 0; i < cantidad; i++) {
        printf("%-4d | %-20s | %d %d %d %d %d %d | %-3d %-3d %-3d %-3d %-4d | %s\n",
               riesgos[i].id, riesgos[i].nombre,
               riesgos[i].F, riesgos[i].S, riesgos[i].P, riesgos[i].E, riesgos[i].A, riesgos[i].V,
               riesgos[i].I, riesgos[i].D, riesgos[i].C, riesgos[i].Pb, riesgos[i].ER,
               obtenerClaseRiesgo(riesgos[i].ER));
    }
    printf("----------------------------------------------------------------------------------------\n");
}

// Muestra la descripcion de los criterios del Metodo Mosler
void mostrarDescripcionCriterios() {
    printf("\n=== GUIA DE CRITERIOS METODO MOSLER (Escala 1 a 5) ===\n");
    printf("F - Funcion: Consecuencias en la actividad principal (1: Leve, 5: Muy grave)\n");
    printf("S - Sustitucion: Dificultad para reemplazar bienes/servicios (1: Muy facil, 5: Muy dificil)\n");
    printf("P - Profundidad: Perturbacion y efecto en la imagen/operacion (1: Leve, 5: Muy grave)\n");
    printf("E - Extension: Alcance territorial del impacto (1: Muy local, 5: Internacional)\n");
    printf("A - Agresion: Probabilidad de manifestacion del riesgo (1: Muy baja, 5: Muy alta)\n");
    printf("V - Vulnerabilidad: Probabilidad de sufrir danos (1: Muy baja, 5: Muy alta)\n");
    printf("========================================================\n\n");
}

// --- MODULOS PRINCIPALES ---

void agregarEmpresa() {
    char empresa[MAX_NOMBRE];
    printf("\n--- AGREGAR EMPRESA ---\n");
    printf("Nombre de la nueva empresa: ");
    scanf(" %[^\n]", empresa);

    // Verificar si ya existe en el registro
    int cantidad = 0;
    Empresa *lista = cargarEmpresas(&cantidad);
    for (int i = 0; i < cantidad; i++) {
        if (strcmp(lista[i].nombre, empresa) == 0) {
            printf(">> Atencion: La empresa '%s' ya se encuentra registrada.\n", empresa);
            free(lista);
            return;
        }
    }
    if (lista) free(lista);

    // Guardar en empresas.txt
    FILE *archivoMaestro = fopen(ARCHIVO_EMPRESAS, "a");
    if (!archivoMaestro) {
        printf(">> Error al guardar en el registro maestro de empresas.\n");
        return;
    }
    fprintf(archivoMaestro, "%s\n", empresa);
    fclose(archivoMaestro);

    // Crear el archivo CSV individual de la empresa
    char nombreArchivoRiesgos[256];
    obtenerNombreArchivoRiesgos(empresa, nombreArchivoRiesgos);
    FILE *archivoRiesgos = fopen(nombreArchivoRiesgos, "a");
    if (archivoRiesgos) {
        fclose(archivoRiesgos);
        printf(">> Empresa '%s' registrada exitosamente.\n", empresa);
    } else {
        printf(">> Error al generar el archivo CSV para la empresa.\n");
    }
}

void consultarEmpresas() {
    int cantidad = 0;
    Empresa *lista = cargarEmpresas(&cantidad);

    if (cantidad == 0 || !lista) {
        printf("\n>> No hay empresas registradas actualmente.\n");
        return;
    }

    printf("\n=========================================\n");
    printf("       EMPRESAS REGISTRADAS (%d)         \n", cantidad);
    printf("=========================================\n");
    for (int i = 0; i < cantidad; i++) {
        printf("%d. %s\n", i + 1, lista[i].nombre);
    }
    printf("=========================================\n");

    free(lista);
}

void agregarRiesgo() {
    char empresa[MAX_NOMBRE];
    if (!seleccionarEmpresa(empresa)) {
        return;
    }

    printf("\n--- AGREGAR RIESGO A '%s' ---\n", empresa);

    int cantidad = 0;
    Riesgo *riesgos = cargarRiesgos(empresa, &cantidad);

    Riesgo nuevo;
    nuevo.id = (cantidad > 0) ? riesgos[cantidad - 1].id + 1 : 1;

    printf("Nombre / Descripcion del Riesgo: ");
    scanf(" %[^\n]", nuevo.nombre);

    mostrarDescripcionCriterios();

    // Lectura con validacion estricta de escala (1 a 5)
    nuevo.F = leerCriterio("Criterio F - Funcion (Impacto en la actividad de 1 a 5): ");
    nuevo.S = leerCriterio("Criterio S - Sustitucion (Dificultad de reemplazo de 1 a 5): ");
    nuevo.P = leerCriterio("Criterio P - Profundidad (Efecto y perturbacion de 1 a 5): ");
    nuevo.E = leerCriterio("Criterio E - Extension (Alcance territorial de 1 a 5): ");
    nuevo.A = leerCriterio("Criterio A - Agresion (Probabilidad de manifestacion de 1 a 5): ");
    nuevo.V = leerCriterio("Criterio V - Vulnerabilidad (Probabilidad de sufrir danos de 1 a 5): ");

    calcularMosler(&nuevo);

    cantidad++;
    Riesgo *temp = (Riesgo*) realloc(riesgos, cantidad * sizeof(Riesgo));
    if (!temp) {
        printf(">> Error de memoria al guardar el riesgo.\n");
        free(riesgos);
        return;
    }
    riesgos = temp;
    riesgos[cantidad - 1] = nuevo;

    guardarRiesgos(empresa, riesgos, cantidad);
    free(riesgos);

    printf(">> Riesgo agregado correctamente a '%s' con ID %d.\n", empresa, nuevo.id);
    printf(">> ER Calculado: %d | Clase de Riesgo: %s\n", nuevo.ER, obtenerClaseRiesgo(nuevo.ER));
}

void consultarRiesgoEspecifico() {
    char empresa[MAX_NOMBRE];
    if (!seleccionarEmpresa(empresa)) {
        return;
    }

    int cantidad = 0;
    Riesgo *riesgos = cargarRiesgos(empresa, &cantidad);

    if (cantidad == 0 || !riesgos) {
        printf(">> No hay riesgos registrados para la empresa '%s'.\n", empresa);
        return;
    }

    printf("\n--- RIESGOS REGISTRADOS EN '%s' ---\n", empresa);
    printf("%-4s | %s\n", "ID", "Nombre / Descripcion");
    printf("-----------------------------------------\n");
    for (int i = 0; i < cantidad; i++) {
        printf("%-4d | %s\n", riesgos[i].id, riesgos[i].nombre);
    }
    printf("-----------------------------------------\n");

    int idBusqueda;
    printf("Ingrese el ID del riesgo que desea consultar: ");
    scanf("%d", &idBusqueda);

    int indice = -1;
    for (int i = 0; i < cantidad; i++) {
        if (riesgos[i].id == idBusqueda) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        printf(">> El ID ingresado no existe.\n");
        free(riesgos);
        return;
    }

    Riesgo r = riesgos[indice];
    printf("\n=========================================\n");
    printf("  DETALLE DEL RIESGO [ID: %d] - %s\n", r.id, empresa);
    printf("=========================================\n");
    printf(" Nombre / Descripcion: %s\n", r.nombre);
    printf("-----------------------------------------\n");
    printf(" PARAMETROS DE ENTRADA (Escala 1 a 5):\n");
    printf("   F - Funcion:        %d\n", r.F);
    printf("   S - Sustitucion:    %d\n", r.S);
    printf("   P - Profundidad:    %d\n", r.P);
    printf("   E - Extension:      %d\n", r.E);
    printf("   A - Agresion:       %d\n", r.A);
    printf("   V - Vulnerabilidad: %d\n", r.V);
    printf("-----------------------------------------\n");
    printf(" VALORES CALCULADOS (METODO MOSLER):\n");
    printf("   I  - Importancia del perjuicio (F * S): %d\n", r.I);
    printf("   D  - Danos ocasionados (P * E):         %d\n", r.D);
    printf("   C  - Caracter del riesgo (I + D):       %d\n", r.C);
    printf("   Pb - Probabilidad (A * V):              %d\n", r.Pb);
    printf("   ER - Estimacion del Riesgo (C * Pb):    %d\n", r.ER);
    printf("-----------------------------------------\n");
    printf(" CLASE DE RIESGO: %s\n", obtenerClaseRiesgo(r.ER));
    printf("=========================================\n");

    free(riesgos);
}

void modificarRiesgo() {
    char empresa[MAX_NOMBRE];
    if (!seleccionarEmpresa(empresa)) {
        return;
    }

    int cantidad = 0;
    Riesgo *riesgos = cargarRiesgos(empresa, &cantidad);

    if (cantidad == 0 || !riesgos) {
        printf(">> No se encontraron riesgos registrados para la empresa '%s'.\n", empresa);
        return;
    }

    printf("\n--- MODIFICAR RIESGO EN '%s' ---\n", empresa);
    listarRiesgos(riesgos, cantidad);

    int idBusqueda;
    printf("Ingrese el ID del riesgo a modificar: ");
    scanf("%d", &idBusqueda);

    int indice = -1;
    for (int i = 0; i < cantidad; i++) {
        if (riesgos[i].id == idBusqueda) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        printf(">> El ID ingresado no existe.\n");
        free(riesgos);
        return;
    }

    printf("\nParametro a modificar para '%s':\n", riesgos[indice].nombre);
    printf("1. Nombre / Descripcion\n");
    printf("2. Criterio F - Funcion (Impacto en la actividad de 1 a 5)\n");
    printf("3. Criterio S - Sustitucion (Dificultad de reemplazo de 1 a 5)\n");
    printf("4. Criterio P - Profundidad (Efecto y perturbacion de 1 a 5)\n");
    printf("5. Criterio E - Extension (Alcance territorial de 1 a 5)\n");
    printf("6. Criterio A - Agresion (Probabilidad de manifestacion de 1 a 5)\n");
    printf("7. Criterio V - Vulnerabilidad (Probabilidad de sufrir danos de 1 a 5)\n");
    printf("Seleccione una opcion: ");

    int opcion;
    scanf("%d", &opcion);

    switch (opcion) {
        case 1: printf("Nuevo Nombre / Descripcion: "); scanf(" %[^\n]", riesgos[indice].nombre); break;
        case 2: riesgos[indice].F = leerCriterio("Nuevo F (Funcion 1-5): "); break;
        case 3: riesgos[indice].S = leerCriterio("Nuevo S (Sustitucion 1-5): "); break;
        case 4: riesgos[indice].P = leerCriterio("Nuevo P (Profundidad 1-5): "); break;
        case 5: riesgos[indice].E = leerCriterio("Nuevo E (Extension 1-5): "); break;
        case 6: riesgos[indice].A = leerCriterio("Nuevo A (Agresion 1-5): "); break;
        case 7: riesgos[indice].V = leerCriterio("Nuevo V (Vulnerabilidad 1-5): "); break;
        default: printf("Opcion no valida.\n"); free(riesgos); return;
    }

    calcularMosler(&riesgos[indice]); // Recalcular metricas automaticas

    guardarRiesgos(empresa, riesgos, cantidad);
    free(riesgos);

    printf(">> Parametro actualizado y metricas recalculadas exitosamente.\n");
}

void borrarRiesgo() {
    char empresa[MAX_NOMBRE];
    if (!seleccionarEmpresa(empresa)) {
        return;
    }

    int cantidad = 0;
    Riesgo *riesgos = cargarRiesgos(empresa, &cantidad);

    if (cantidad == 0 || !riesgos) {
        printf(">> No hay riesgos registrados para la empresa '%s'.\n", empresa);
        return;
    }

    printf("\n--- BORRAR RIESGO EN '%s' ---\n", empresa);
    listarRiesgos(riesgos, cantidad);

    int idBusqueda;
    printf("Ingrese el ID del riesgo a borrar: ");
    scanf("%d", &idBusqueda);

    int indice = -1;
    for (int i = 0; i < cantidad; i++) {
        if (riesgos[i].id == idBusqueda) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        printf(">> El ID ingresado no existe.\n");
        free(riesgos);
        return;
    }

    // Desplazar elementos hacia la izquierda
    for (int i = indice; i < cantidad - 1; i++) {
        riesgos[i] = riesgos[i + 1];
    }

    cantidad--;

    if (cantidad > 0) {
        Riesgo *temp = (Riesgo*) realloc(riesgos, cantidad * sizeof(Riesgo));
        if (temp) riesgos = temp;
    } else {
        free(riesgos);
        riesgos = NULL;
    }

    guardarRiesgos(empresa, riesgos, cantidad);
    if (riesgos) free(riesgos);

    printf(">> Riesgo eliminado correctamente.\n");
}

// --- MENU PRINCIPAL ---

int main() {
    int opcion;

    do {
        printf("\n=========================================\n");
        printf("     SISTEMA DE GESTION METODO MOSLER    \n");
        printf("=========================================\n");
        printf("1. Agregar Empresa\n");
        printf("2. Consultar Empresas Registradas\n");
        printf("3. Agregar Riesgo\n");
        printf("4. Consultar Riesgo Especifico por ID\n");
        printf("5. Modificar Parametro de Riesgo\n");
        printf("6. Borrar Riesgo\n");
        printf("7. Salir\n");
        printf("=========================================\n");
        printf("Seleccione una opcion: ");
        if (scanf("%d", &opcion) != 1) {
            while (getchar() != '\n'); // Evitar bucles infinitos
            opcion = 0;
        }

        switch (opcion) {
            case 1: agregarEmpresa(); break;
            case 2: consultarEmpresas(); break;
            case 3: agregarRiesgo(); break;
            case 4: consultarRiesgoEspecifico(); break;
            case 5: modificarRiesgo(); break;
            case 6: borrarRiesgo(); break;
            case 7: printf("\nHasta luego!\n"); break;
            default: printf("Opcion invalida. Intente de nuevo.\n");
        }
    } while (opcion != 7);

    return 0;
}
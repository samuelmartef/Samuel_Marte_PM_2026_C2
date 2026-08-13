#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --------------------------------------------------------
// ESTRUCTURAS DE DATOS
// --------------------------------------------------------
typedef struct {
    int id;
    char modelo[50];
    double costo_vehiculo;        // Precio de compra en RD$
    int vida_util_anios;          // Años estimados de uso
    double vida_util_km;          // Kilómetros estimados de vida útil
    double costo_mantenimiento;   // Gasto total en mantenimiento (RD$)
    double costo_neumaticos;      // Gasto total en neumáticos (RD$)
    double seguro_anual;          // Costo del seguro por año (RD$)
    double rend_ciudad;           // Rendimiento: km por galón en ciudad
    double rend_autopista;        // Rendimiento: km por galón en autopista
} Vehiculo;

// Estructura para manejar ambos precios
typedef struct {
    double premium;
    double regular;
} PreciosCombustible;

// Variables globales para nombres de archivos
const char *ARCHIVO_VEHICULOS = "vehiculos.dat";
const char *ARCHIVO_PRECIOS = "precios.txt";

// --------------------------------------------------------
// FUNCIONES DE UTILIDAD
// --------------------------------------------------------
void limpiar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

PreciosCombustible leer_precios() {
    // Precios por defecto según mercado actual
    PreciosCombustible p = {338.10, 302.50}; 
    
    FILE *f = fopen(ARCHIVO_PRECIOS, "r");
    if (f != NULL) {
        fscanf(f, "%lf %lf", &p.premium, &p.regular);
        fclose(f);
    } else {
        // Si no existe, lo creamos con los valores por defecto
        f = fopen(ARCHIVO_PRECIOS, "w");
        if (f != NULL) {
            fprintf(f, "%.2f %.2f", p.premium, p.regular);
            fclose(f);
        }
    }
    return p;
}

void guardar_precio(int tipo_gasolina, double nuevo_precio) {
    PreciosCombustible p = leer_precios();
    
    if (tipo_gasolina == 1) {
        p.premium = nuevo_precio;
        printf("\n[Exito] Precio de Gasolina Premium actualizado a RD$%.2f\n", p.premium);
    } else if (tipo_gasolina == 2) {
        p.regular = nuevo_precio;
        printf("\n[Exito] Precio de Gasolina Regular actualizado a RD$%.2f\n", p.regular);
    }

    FILE *f = fopen(ARCHIVO_PRECIOS, "w");
    if (f != NULL) {
        fprintf(f, "%.2f %.2f", p.premium, p.regular);
        fclose(f);
    }
}

// --------------------------------------------------------
// LÓGICA DE CÁLCULO
// --------------------------------------------------------
void imprimir_analisis_costos(Vehiculo v, double precio_comb) {
    if (v.vida_util_km <= 0 || v.rend_ciudad <= 0 || v.rend_autopista <= 0) {
        printf("Error: Datos del vehiculo invalidos (division por cero).\n");
        return;
    }

    // 1. Cálculo de Amortización y Gastos Fijos por KM
    double amortizacion_km = v.costo_vehiculo / v.vida_util_km;
    double mantenimiento_km = v.costo_mantenimiento / v.vida_util_km;
    double neumaticos_km = v.costo_neumaticos / v.vida_util_km;
    double seguro_total_vida = v.seguro_anual * v.vida_util_anios;
    double seguro_km = seguro_total_vida / v.vida_util_km;
    
    double costo_fijo_por_km = amortizacion_km + mantenimiento_km + neumaticos_km + seguro_km;

    // 2. Costo de combustible por KM
    double costo_comb_ciudad = precio_comb / v.rend_ciudad;
    double costo_comb_autopista = precio_comb / v.rend_autopista;
    
    // 3. Costo REAL por KM (Fijos + Combustible)
    double costo_real_ciudad = costo_fijo_por_km + costo_comb_ciudad;
    double costo_real_autopista = costo_fijo_por_km + costo_comb_autopista;
    double promedio_mixto = (costo_real_ciudad + costo_real_autopista) / 2.0;

    printf("\n--- ANALISIS DE COSTOS REALES: %s ---\n", v.modelo);
    printf("Amortizacion e infraestructura: RD$%.4f / km\n", costo_fijo_por_km);
    printf("Costo Combustible (Ciudad):     RD$%.4f / km\n", costo_comb_ciudad);
    printf("Costo Combustible (Autopista):  RD$%.4f / km\n", costo_comb_autopista);
    printf("--------------------------------------------\n");
    printf("COSTO REAL POR KM (CIUDAD):    RD$%.2f\n", costo_real_ciudad);
    printf("COSTO REAL POR KM (AUTOPISTA): RD$%.2f\n", costo_real_autopista);
    printf("COSTO REAL PROMEDIO MIXTO:     RD$%.2f\n", promedio_mixto);
    printf("--------------------------------------------\n");
}

// --------------------------------------------------------
// SISTEMA CRUD Y ARCHIVOS
// --------------------------------------------------------
void agregar_vehiculo() {
    FILE *f = fopen(ARCHIVO_VEHICULOS, "ab");
    if (f == NULL) { printf("Error al abrir archivo.\n"); return; }

    Vehiculo v;
    printf("\n--- NUEVO VEHICULO ---\n");
    printf("ID del vehiculo (numero entero): ");
    scanf("%d", &v.id);
    limpiar_buffer();
    
    printf("Modelo: ");
    fgets(v.modelo, 50, stdin);
    v.modelo[strcspn(v.modelo, "\n")] = 0;

    printf("Costo de compra (RD$): "); scanf("%lf", &v.costo_vehiculo);
    printf("Vida util estimada en anos: "); scanf("%d", &v.vida_util_anios);
    printf("Vida util estimada en kilometros: "); scanf("%lf", &v.vida_util_km);
    printf("Costo TOTAL mantto. en vida util (RD$): "); scanf("%lf", &v.costo_mantenimiento);
    printf("Costo TOTAL neumaticos en vida util (RD$): "); scanf("%lf", &v.costo_neumaticos);
    printf("Costo de seguro anual (RD$): "); scanf("%lf", &v.seguro_anual);
    printf("Rendimiento en ciudad (km/galon): "); scanf("%lf", &v.rend_ciudad);
    printf("Rendimiento en autopista (km/galon): "); scanf("%lf", &v.rend_autopista);

    fwrite(&v, sizeof(Vehiculo), 1, f);
    fclose(f);
    printf("\n[Exito] Vehiculo guardado.\n");
}

void ver_vehiculos() {
    FILE *f = fopen(ARCHIVO_VEHICULOS, "rb");
    if (f == NULL) { printf("No hay vehiculos registrados.\n"); return; }

    Vehiculo v;
    printf("\n--- LISTA DE VEHICULOS ---\n");
    while (fread(&v, sizeof(Vehiculo), 1, f)) {
        printf("ID: %d | Modelo: %s | Costo: RD$%.2f\n", v.id, v.modelo, v.costo_vehiculo);
    }
    fclose(f);
}

void borrar_vehiculo() {
    FILE *f = fopen(ARCHIVO_VEHICULOS, "rb");
    if (f == NULL) { printf("No hay vehiculos.\n"); return; }

    FILE *temp = fopen("temp.dat", "wb");
    int id_borrar, encontrado = 0;
    Vehiculo v;

    printf("\nIngrese el ID del vehiculo a borrar: ");
    scanf("%d", &id_borrar);

    while (fread(&v, sizeof(Vehiculo), 1, f)) {
        if (v.id == id_borrar) {
            encontrado = 1;
        } else {
            fwrite(&v, sizeof(Vehiculo), 1, temp);
        }
    }

    fclose(f);
    fclose(temp);

    remove(ARCHIVO_VEHICULOS);
    rename("temp.dat", ARCHIVO_VEHICULOS);

    if (encontrado) printf("\n[Exito] Vehiculo borrado.\n");
    else printf("\n[Error] ID no encontrado.\n");
}

void calcular_viaje() {
    FILE *f = fopen(ARCHIVO_VEHICULOS, "rb");
    if (f == NULL) { printf("No hay vehiculos.\n"); return; }

    int id_buscar, encontrado = 0;
    Vehiculo v;
    double km_ciudad, km_autopista;
    
    // Leer precios actuales
    PreciosCombustible precios_actuales = leer_precios();
    int tipo_comb;
    double precio_usar = 0.0;

    printf("\nIngrese el ID del vehiculo para el viaje: ");
    scanf("%d", &id_buscar);

    while (fread(&v, sizeof(Vehiculo), 1, f)) {
        if (v.id == id_buscar) {
            encontrado = 1;
            break;
        }
    }
    fclose(f);

    if (!encontrado) { printf("\nVehiculo no encontrado.\n"); return; }

    // Seleccionar tipo de combustible para el viaje
    printf("\n¿Que combustible utilizara en este viaje?\n");
    printf("1. Premium (RD$%.2f / galon)\n", precios_actuales.premium);
    printf("2. Regular (RD$%.2f / galon)\n", precios_actuales.regular);
    printf("Seleccion (1 o 2): ");
    scanf("%d", &tipo_comb);

    if (tipo_comb == 1) {
        precio_usar = precios_actuales.premium;
    } else if (tipo_comb == 2) {
        precio_usar = precios_actuales.regular;
    } else {
        printf("Seleccion invalida. Usando Premium por defecto.\n");
        precio_usar = precios_actuales.premium;
    }

    imprimir_analisis_costos(v, precio_usar);

    printf("\n--- PLANIFICADOR DE VIAJE ---\n");
    printf("Km a recorrer en Ciudad: "); scanf("%lf", &km_ciudad);
    printf("Km a recorrer en Autopista: "); scanf("%lf", &km_autopista);

    // Costos de Combustible
    double comb_ciudad = km_ciudad / v.rend_ciudad;
    double comb_autopista = km_autopista / v.rend_autopista;
    double gasto_comb_total = (comb_ciudad + comb_autopista) * precio_usar;

    // Costos Reales (Incluyendo desgaste del vehiculo)
    double costo_fijo_km = (v.costo_vehiculo + v.costo_mantenimiento + v.costo_neumaticos + (v.seguro_anual * v.vida_util_anios)) / v.vida_util_km;
    double desgaste_vehiculo_viaje = (km_ciudad + km_autopista) * costo_fijo_km;
    double costo_real_viaje = gasto_comb_total + desgaste_vehiculo_viaje;

    printf("\n--- RESULTADO DEL VIAJE ---\n");
    printf("Combustible estimado:    %.2f Galones\n", comb_ciudad + comb_autopista);
    printf("Gasto en combustible:    RD$%.2f\n", gasto_comb_total);
    printf("Desgaste del vehiculo:   RD$%.2f\n", desgaste_vehiculo_viaje);
    printf("----------------------------------\n");
    printf("COSTO REAL DEL VIAJE:    RD$%.2f\n", costo_real_viaje);
}

// --------------------------------------------------------
// MENÚ PRINCIPAL
// --------------------------------------------------------
int main() {
    int opcion;

    do {
        PreciosCombustible p = leer_precios(); // Leer precios actualizados en cada ciclo
        
        printf("\n=========================================\n");
        printf("       SISTEMA DE FLOTA Y COSTOS\n");
        printf(" Precios Actuales (RD$/galon):\n");
        printf("   - Premium: RD$%.2f\n", p.premium);
        printf("   - Regular: RD$%.2f\n", p.regular);
        printf("=========================================\n");
        printf("1. Crear vehiculo nuevo\n");
        printf("2. Ver vehiculos registrados\n");
        printf("3. Calcular viaje y Costos Reales\n");
        printf("4. Borrar un vehiculo\n");
        printf("5. Modificar precio de combustible\n");
        printf("6. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: agregar_vehiculo(); break;
            case 2: ver_vehiculos(); break;
            case 3: calcular_viaje(); break;
            case 4: ver_vehiculos(); borrar_vehiculo(); break;
            case 5: {
                int tipo_gas;
                double nuevo_precio;
                printf("\n¿Cual precio deseas modificar?\n");
                printf("1. Gasolina Premium\n");
                printf("2. Gasolina Regular\n");
                printf("Seleccion (1 o 2): ");
                scanf("%d", &tipo_gas);
                
                if (tipo_gas == 1 || tipo_gas == 2) {
                    printf("Ingrese el nuevo precio (RD$/galon): ");
                    scanf("%lf", &nuevo_precio);
                    guardar_precio(tipo_gas, nuevo_precio);
                } else {
                    printf("Opcion no valida.\n");
                }
                break;
            }
            case 6: printf("Saliendo...\n"); break;
            default: printf("Opcion no valida.\n");
        }
    } while (opcion != 6);

    return 0;
}
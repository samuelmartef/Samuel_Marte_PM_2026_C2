#include <stdio.h>
#include <math.h>

// Variable global para llevar la cuenta de los movimientos
int contador = 0;

void hanoi(int n, char ini, char fin, char ayu);

int main() {
    int dis;
    do {
        printf("Cuantos discos quiere: ");
        scanf("%d", &dis);
        if (dis <= 0) {
            printf("Error\n");
        }
    } while (dis <= 0);

    printf("\nMovimientos:\n");
    hanoi(dis, 'A', 'C', 'B');
    
    int total_movimientos = (int)pow(2, dis) - 1;
    printf("\nTotal de movimientos realizados: %d\n", total_movimientos);
    
    return 0;
}

void hanoi(int n, char ini, char fin, char ayu) {
    if (n == 1) {
        contador++; // Incrementamos el contador
        printf("%d) Mover disco 1 de %c a %c\n", contador, ini, fin);
        return;
    }
    
    hanoi(n - 1, ini, ayu, fin);
    
    contador++; // Incrementamos el contador
    printf("%d) Mover disco %d de %c a %c\n", contador, n, ini, fin);
    
    hanoi(n - 1, ayu, fin, ini);
}
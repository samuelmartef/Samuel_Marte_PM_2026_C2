#include <stdio.h>
#include <math.h>

void hanoi(int n, char ini, char fin, char ayu);

int main() {
    int dis;
    do {
        printf("Cuantos discos quiere: ");
        scanf("%d", &dis);
        if (dis <= 0) {
            printf("Error esto no va jalar \n");
        }
    } while (dis <= 0);

    printf("\nMovimiento\n");
    hanoi(dis, 'A', 'B', 'C');
    
    int total_movimientos = (int)pow(2, dis) - 1;
    printf("Total de movimientos: %d\n", total_movimientos);
    
    return 0;
}

void hanoi(int n, char ini, char fin, char ayu) {
    if (n == 1) {
        printf("Mover disco 1 de %c a %c\n", ini, fin);
        return;
    }
    hanoi(n - 1, ini, ayu, fin);
    printf("Mover disco %d de %c a %c\n", n, ini, fin);
    hanoi(n - 1, ayu, fin, ini);
}
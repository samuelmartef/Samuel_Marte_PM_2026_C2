#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TOCA3 DE LOTEKA 1
#define NUMERO GANADOR 2
#define MAX 50
/*Programa de Loteria*/

/*Funciones*/
void Lectura(int A[MAX], int, int D[]);
void ArregloR(int *, int);
void Compare(int *, int *, int, int *);

int *AU;

int main(void)
{
int MENU = 0, I;
int JUG[MAX]={0}, RAM[MAX]={0}, TAM, PRU, PRD, DIN[MAX]={0};

printf("\n-------LOTERIA-------\n");
do
{
    printf("\n\nQUE MODALIDAD DESEA JUGAR....\nTOCA3 DE LOTEKA\t(Marque 1)\nNUMERO GANADOR\t(Marque 2)\n(---MARQUE 0 PARA SALIR---)\n");
    printf("-------------------\n");
    scanf("%d", &MENU);
    
    if (MENU == 1)
    {
        TAM = 3;
        printf("---TIENE QUE INGRESAR 3 JUGADAS CON NUMEROS DEL 1 AL 100---\n");
        for (I=0; I<3; I++)
        {
            printf("Ingrese la jugada numero %d y cuanto dinero apuesta: ", I+1);
            scanf("%d %d", &PRU, &PRD);
            if (PRU <= 100 && PRU >= 1)
            {
                JUG[I]=PRU;
                DIN[I]=PRD;
            }
            else
            {
                printf("El numero no es valido, intente de nuevo...\n");
                I--;
            }
        }
        ArregloR(RAM, TAM);
        Compare(JUG, RAM, TAM, DIN);
    }
    else if (MENU == 2)
    {
        do
            {
            printf("INGRESE LA CANTIDAD DE JUGADAS QUE QUIERE HACER\n(LIMITE 50 JUGADAS)...");
            scanf("%d", &TAM);
            if (TAM > 50)
            {
                printf("LAS JUGADAS EXCEDEN EL LIMITE, INTENTE DE NUEVO..\n");
            }
            else if (TAM < 1)
                printf("LAS JUGADAS NO PUEDE SER MENORES DE 1..\n\n");
            }
        while (TAM > 50 || TAM < 1);
        Lectura(JUG, TAM, DIN);
        ArregloR(RAM, TAM);
        Compare(JUG, RAM, TAM, DIN);
    }
}
while (MENU != 0);
printf("GRACIAS POR JUGAR...");

}



void ArregloR(int A[], int T)
{
int I;
srand(time(NULL));
printf("\nNUMEROS DE LA LOTERIA\n");
for (I=0; I<T; I++)
{
    A[I] = (rand() % (100 - 1 + 1)) + 1;
    printf("%d\t", A[I]);
}
}

void Compare(int A[], int B[], int T, int D[])
{
int I, J, PR = 0;
for (I=0; I<T; I++)
{
    for (J=0; J<T; J++)
    {
        if (A[I] == B[J])
        {
            printf("\nACERTASTE CON EL NUMERO %d", A[I]);
            D[I] = D[I]*1000;
            PR += D[I];
            printf("\nHAS GANADO %d", D[I]);
        }
    }
}
if (PR == 0)
    printf("\nNO GANASTE NADA INTENTALO DE NUEVO...");
else
    printf("\nEN TOTAL GANASTE %d", PR);
}


void Lectura(int A[], int T, int D[])
{
int I, PRU, PRD;
for (I=0; I<T; I++)
{
    printf("LOS NUMEROS NO PUEDESN SER MAYORES A 100 NI MENORES A 1");
    printf("\nINEGRESE EL NUMERO QUE QUIERE JUEGAR Y EL DINERO QUE APUESTA A ESE NUMERO(%d): ", I+1);
    scanf("%d %d", &PRU, &PRD);
     if (PRU <= 100 && PRU >= 1)
    {
        A[I]=PRU;
        D[I]=PRD;
    }
    else
    {
        printf("El numero no es valido, intente de nuevo...\n");
        I--;
    }
}
}
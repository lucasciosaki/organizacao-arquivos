// Artur Domitti Camargo - 15441661
// Lucas Mello Ciosaki - 14591305

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "funcionalidades/funcionalidades.h"

int main() {
    int func;
    // Lê a funcionalidade desejada
    if (scanf("%d", &func) != 1) {
        printf("Entrada inválida.\n");
        return 1;
    }

    // Funcionalidade 1: Converter CSV para binário
    if (func == 1) {
        char nomeCSV[100], nomeBin[100];
        if (scanf("%s %s", nomeCSV, nomeBin) != 2) { 
            printf("Nome de arquivo inválido.\n");
            return 1;
        }
        funcionalidade1(nomeCSV, nomeBin);
    }
    
    //  Funcionalidade 2: Ler arquivo binário e imprimir os registros válidos
    if (func == 2) {
        char nomeBin[100];
        if (scanf("%s", nomeBin) != 1) {
            printf("Nome de arquivo inválido.\n");
            return 1;
        }
        funcionalidade2(nomeBin);
    }

    //  Funcionalidade 3: Ler arquivo binário e imprimir os registros válidos filtrados
    if (func == 3){
        char nomeBin[100];
        int n;
        if(scanf("%s %d", nomeBin, &n) != 2){
            printf("Nome de arquivo inválido.\n");
            return 1;
        }
        funcionalidade3(nomeBin, n);
    }   

    //  Funcionalidade 4: Remover um registro escolhido do arquivo binário
    if (func == 4){
        char nomeBin[100];
        int n;
        if(scanf("%s %d", nomeBin, &n) != 2){
            printf("Nome de arquivo inválido.\n");
            return 1;
        }
        funcionalidade4(nomeBin, n);
    }   

    //  Funcionalidade 5: Adicionar um novo registro ao arquivo binário
    if (func == 5){
        char nomeBin[100];
        int n;
        if(scanf("%s %d", nomeBin, &n) != 2){
            printf("Nome de arquivo inválido.\n");
            return 1;
        }
        funcionalidade5(nomeBin, n);
    }   

    if (func == 6){
        char nomeBin[100];
        int n;
        if(scanf("%s %d", nomeBin, &n) != 2){
            printf("Nome de arquivo inválido.\n");
            return 1;
        }
        funcionalidade6(nomeBin, n);
    }   

    if (func == 7) {
        char nomeBinDados[100];
        char nomeBinArvB[100];
        if(scanf("%s %s", nomeBinDados, nomeBinArvB) != 2){
            printf("Nome de arquivo inválido.\n");
            return 1;
        }
        funcionalidade7(nomeBinDados,nomeBinArvB);
    }

    if (func == 8) {
        char nomeBinDados[100];
        char nomeBinArvB[100];
        int n;
        if(scanf("%s %s %d", nomeBinDados, nomeBinArvB, &n) != 3){
            printf("Nome de arquivo inválido.\n");
            return 1;
        }
        funcionalidade8(nomeBinDados,nomeBinArvB, n);
    }

    if (func == 10) {
        char nomeBinDados[100];
        char nomeBinArvB[100];
        int n;
        if(scanf("%s %s %d", nomeBinDados, nomeBinArvB, &n) != 3){
            printf("Nome de arquivo inválido.\n");
            return 1;
        }
        funcionalidade10(nomeBinDados,nomeBinArvB, n);
    }

    if (func == 11) {
        char nomeBinDados[100];
        char nomeBinArvB[100];
        int n;
        if(scanf("%s %s %d", nomeBinDados, nomeBinArvB, &n) != 3){
            printf("Nome de arquivo inválido.\n");
            return 1;
        }
        funcionalidade11(nomeBinDados,nomeBinArvB, n);
    }


    return 0;
}

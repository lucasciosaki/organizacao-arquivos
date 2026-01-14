// Artur Domitti Camargo - 15441661
// Lucas Mello Ciosaki - 14591305

#ifndef _REGISTRO_H
#define _REGISTRO_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdbool.h>
    #include "cabecalho.h"

    typedef struct _registro Registro;
    // Cria o registro e inicializa os valores
    Registro* registro_criar(char removido, long int prox, int idAttack, int year, float financialLoss, char *country, char *attackType, char *targetIndustry, char *defenseMechanism);

    // Getters para os campos do registro
    bool registro_removido(Registro *registro); // Verifica se o registro foi removido
    int registro_get_tamanhoRegistro(Registro *registro);
    long int registro_get_prox(Registro *registro);
    int registro_get_idAttack(Registro *registro);
    int registro_get_year(Registro *registro);
    float registro_get_financialLoss(Registro *registro);
    char *registro_get_country(Registro *registro);
    char *registro_get_attackType(Registro *registro);
    char *registro_get_targetIndustry(Registro *registro);
    char *registro_get_defenseMechanism(Registro *registro);

    bool registro_set_tamanhoRegistro(Registro *registro, int tamanhoRegistro);
    bool registro_set_prox(Registro *registro, long int prox);

    // Funções auxiliares
    bool registro_escrever(FILE *bin, Registro *registro);
    Registro *registro_ler_csv(FILE *csv, char linha[]);
    Registro *registro_ler_bin(FILE *bin);
    bool registro_imprimir(Registro *registro, Cabecalho *cabecalho);
    bool registro_comparar(Registro *registro, int cmp_idAttack, int cmp_year, float cmp_financialLoss, char cmp_country[], char cmp_attackType[], char cmp_targetIndustry[], char cmp_defenseMechanism[]);
    bool registro_remover(FILE *bin, Registro *registro, Cabecalho *cabecalho);
    bool registro_apagar(Registro **registro);
    long int registro_inserir(FILE *bin, Registro *novo, Cabecalho *cabecalho);
#endif
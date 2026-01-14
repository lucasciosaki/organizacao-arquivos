#ifndef _ARV_B_H
#define _ARV_B_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include "arvB_registro.h"
    #include "arvB_cabecalho.h" 
    #include "../arquivo_de_dados/registro.h"
    #include "../arquivo_de_dados/cabecalho.h"
    
    #define TAM_NO 44
    
    bool arvb_inserir(FILE *bin_arvb, ArvB_Cabecalho *arvb_cabecalho, int C, long int Pr);
    long arvb_buscar(FILE *bin_arvb, ArvB_Cabecalho *cabecalho, int chave);
    bool arvb_dfs_busca(FILE *bin_arvb, FILE *bin_dados, Cabecalho *cabecalho, int RRN, int cmp_year, float cmp_financialLoss, char cmp_country[], char cmp_attackType[], char cmp_targetIndustry[], char cmp_defenseMechanism[]);
    bool arvb_update(FILE *bin_arvb, ArvB_Cabecalho *arvb_cabecalho, int C, long int Pr);
    bool arvb_dfs_update(FILE *bin_arvb, FILE *bin_dados, Cabecalho *cabecalho, ArvB_Cabecalho *arvb_cabecalho,int RRN, int cmp_year, float cmp_financialLoss, char cmp_country[], char cmp_attackType[], char cmp_targetIndustry[], char cmp_defenseMechanism[], bool campos[], int year, float financialLoss, char country[], char attackType[], char targetIndustry[], char defenseMechanism[]);

#endif
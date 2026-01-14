// Artur Domitti Camargo - 15441661
// Lucas Mello Ciosaki - 14591305

#ifndef _CABECALHO_H
#define _CABECALHO_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdbool.h>

    #define TAM_CABECALHO_CSV 254
    #define TAM_CABECALHO_BIN 276

    typedef struct _cabecalho Cabecalho;

    // Cria o cabeçalho e inicializa os campos
    Cabecalho *cabecalho_criar();

    // Setters para os campos do cabeçalho
    bool cabecalho_set_status(Cabecalho *cabecalho, char status);
    bool cabecalho_set_topo(Cabecalho *cabecalho, long int topo);
    bool cabecalho_set_proxByteOffset(Cabecalho *cabecalho, long int proxByteOffset);
    bool cabecalho_set_nroRegArq(Cabecalho *cabecalho, int nroRegArq);
    bool cabecalho_set_nroRegRem(Cabecalho *cabecalho, int nroRegRem);
    bool cabecalho_update(Cabecalho *cabecalho, char status, long int topo, long int proxByteOffset, int nroRegArq, int nroRegRem);

    // Getters para os campos do cabeçalho
    bool cabecalho_estavel(Cabecalho *cabecalho); // Verifica se o cabeçalho está estável (status '1')
    long int cabecalho_get_topo(Cabecalho *cabecalho);
    long int cabecalho_get_proxByteOffset(Cabecalho *cabecalho);
    int cabecalho_get_nroRegArq(Cabecalho *cabecalho);
    int cabecalho_get_nroRegRem(Cabecalho *cabecalho);
    char *cabecalho_get_descreveIdentificador(Cabecalho *cabecalho);
    char *cabecalho_get_descreveYear(Cabecalho *cabecalho);
    char *cabecalho_get_descreveFinancialLoss(Cabecalho *cabecalho);
    char cabecalho_get_codDescreveCountry(Cabecalho *cabecalho);
    char *cabecalho_get_descreveCountry(Cabecalho *cabecalho);
    char cabecalho_get_codDescreveType(Cabecalho *cabecalho);
    char *cabecalho_get_descreveType(Cabecalho *cabecalho);
    char cabecalho_get_codDescreveTargetIndustry(Cabecalho *cabecalho);
    char *cabecalho_get_descreveTargetIndustry(Cabecalho *cabecalho);
    char cabecalho_get_codDescreveDefense(Cabecalho *cabecalho);
    char *cabecalho_get_descreveDefense(Cabecalho *cabecalho);

    // Funções auxiliares
    bool cabecalho_escrever(FILE *bin, Cabecalho *cabecalho);
    Cabecalho *cabecalho_ler_bin(FILE *bin);
    bool cabecalho_apagar(Cabecalho **cabecalho);
#endif
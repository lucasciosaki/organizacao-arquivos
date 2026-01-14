#ifndef _ARVB_CABECALHO_H

    #define _ARVB_CABECALHO_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    typedef struct _arvb_cabecalho ArvB_Cabecalho;

    ArvB_Cabecalho *arvb_cabecalho_criar();
    ArvB_Cabecalho *arvb_cabecalho_ler(FILE *bin_arvb);
    bool arvb_cabecalho_escrever(FILE *bin_arvb, ArvB_Cabecalho *arvb_cabecalho);
    bool arvb_cabecalho_apagar(ArvB_Cabecalho **arvb_cabecalho);
    char arvb_cabecalho_get_status(ArvB_Cabecalho *arvb_cabecalho);
    int arvb_cabecalho_get_noRaiz(ArvB_Cabecalho *arvb_cabecalho);
    int arvb_cabecalho_get_proxRRN(ArvB_Cabecalho *arvb_cabecalho);
    int arvb_cabecalho_get_nroNos(ArvB_Cabecalho *arvb_cabecalho);
    bool arvb_cabecalho_set_status(ArvB_Cabecalho *arvb_cabecalho, char status);
    bool arvb_cabecalho_set_noRaiz(ArvB_Cabecalho *arvb_cabecalho, int noRaiz);
    bool arvb_cabecalho_set_proxRRN(ArvB_Cabecalho *arvb_cabecalho, int proxRRN);
    bool arvb_cabecalho_set_nroNos(ArvB_Cabecalho *arvb_cabecalho, int nroNos);
#endif
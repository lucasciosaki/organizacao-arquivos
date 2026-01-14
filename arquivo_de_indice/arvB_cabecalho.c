#include "arvB_cabecalho.h"

struct _arvb_cabecalho{
    char status;
    int noRaiz;
    int proxRRN;
    int nroNos;
    char lixo[31];
};

bool arvb_cabecalho_escrever(FILE *bin_arvb, ArvB_Cabecalho *arvb_cabecalho){
    if(!bin_arvb) return false;
    fseek(bin_arvb, 0, SEEK_SET);
    fwrite(&arvb_cabecalho->status, sizeof(char), 1, bin_arvb);
    fwrite(&arvb_cabecalho->noRaiz, sizeof(int), 1, bin_arvb);
    fwrite(&arvb_cabecalho->proxRRN, sizeof(int), 1, bin_arvb);
    fwrite(&arvb_cabecalho->nroNos, sizeof(int), 1, bin_arvb);
    fwrite(arvb_cabecalho->lixo, sizeof(char), sizeof(arvb_cabecalho->lixo), bin_arvb);
    return true;
}

ArvB_Cabecalho *arvb_cabecalho_criar(){
    ArvB_Cabecalho *arvb_cabecalho = (ArvB_Cabecalho *)malloc(sizeof(ArvB_Cabecalho));
    if(arvb_cabecalho == NULL) return NULL;

    arvb_cabecalho->status = '0';
    arvb_cabecalho->noRaiz = -1;
    arvb_cabecalho->proxRRN = 0;
    arvb_cabecalho->nroNos = 0;
    for (int i = 0; i < sizeof(arvb_cabecalho->lixo); i++){
        arvb_cabecalho->lixo[i] = '$';
    }
    return arvb_cabecalho;
}

ArvB_Cabecalho *arvb_cabecalho_ler(FILE *bin_arvb){
    fseek(bin_arvb, 0, SEEK_SET);
    ArvB_Cabecalho *arvb_cabecalho = arvb_cabecalho_criar();
    if(arvb_cabecalho == NULL) return NULL;

    fread(&(arvb_cabecalho->status), sizeof(char), 1, bin_arvb);
    fread(&(arvb_cabecalho->noRaiz), sizeof(int), 1, bin_arvb);
    fread(&(arvb_cabecalho->proxRRN), sizeof(int), 1, bin_arvb);
    fread(&(arvb_cabecalho->nroNos), sizeof(int), 1, bin_arvb);
    
    return arvb_cabecalho;
}

bool arvb_cabecalho_apagar(ArvB_Cabecalho **arvb_cabecalho) {
    if(*arvb_cabecalho == NULL) return false;
    free(*arvb_cabecalho);
    *arvb_cabecalho = NULL;
    return true;
}

char arvb_cabecalho_get_status(ArvB_Cabecalho *arvb_cabecalho){
    if(arvb_cabecalho == NULL) return '0';

    return arvb_cabecalho->status;
}


int arvb_cabecalho_get_noRaiz(ArvB_Cabecalho *arvb_cabecalho){
    if(arvb_cabecalho == NULL) return -1;

    return arvb_cabecalho->noRaiz;
}

int arvb_cabecalho_get_proxRRN(ArvB_Cabecalho *arvb_cabecalho){
    if(arvb_cabecalho == NULL) return -1;

    return arvb_cabecalho->proxRRN;
}

int arvb_cabecalho_get_nroNos(ArvB_Cabecalho *arvb_cabecalho){
    if(arvb_cabecalho == NULL) return -1;

    return arvb_cabecalho->nroNos;
}


bool arvb_cabecalho_set_status(ArvB_Cabecalho *arvb_cabecalho, char status){
    if(arvb_cabecalho == NULL) return false;

    arvb_cabecalho->status = status;
    return true;
} 


bool arvb_cabecalho_set_noRaiz(ArvB_Cabecalho *arvb_cabecalho, int noRaiz){
    if(arvb_cabecalho == NULL) return false;

    arvb_cabecalho->noRaiz = noRaiz;
    return true;
} 

bool arvb_cabecalho_set_proxRRN(ArvB_Cabecalho *arvb_cabecalho, int proxRRN){
    if(arvb_cabecalho == NULL) return false;

    arvb_cabecalho->proxRRN = proxRRN;
    return true;
} 

bool arvb_cabecalho_set_nroNos(ArvB_Cabecalho *arvb_cabecalho, int nroNos){
    if(arvb_cabecalho == NULL) return false;

    arvb_cabecalho->nroNos = nroNos;
    return true;
} 

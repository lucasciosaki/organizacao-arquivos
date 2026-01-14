#include "arvB_registro.h"

struct _arvb_registro{
    int tipoNo;
    int nroChaves;
    int P1;
    int C1;
    long int Pr1;
    int P2;
    int C2;
    long int Pr2;
    int P3;
};

int arvb_registro_get_tipoNo(ArvB_Registro *arvb_registro) {
    return (arvb_registro == NULL) ? -2 : arvb_registro->tipoNo;
}

int arvb_registro_get_nroChaves(ArvB_Registro *arvb_registro) {
    return (arvb_registro == NULL) ? -2 : arvb_registro->nroChaves;
}

int arvb_registro_get_P1(ArvB_Registro *arvb_registro) {
    return (arvb_registro == NULL) ? -2 : arvb_registro->P1;
}

int arvb_registro_get_C1(ArvB_Registro *arvb_registro) {
    return (arvb_registro == NULL) ? -2 : arvb_registro->C1;
}

long int arvb_registro_get_Pr1(ArvB_Registro *arvb_registro) {
    return (arvb_registro == NULL) ? -2 : arvb_registro->Pr1;
}

int arvb_registro_get_P2(ArvB_Registro *arvb_registro) {
    return (arvb_registro == NULL) ? -2 : arvb_registro->P2;
}

int arvb_registro_get_C2(ArvB_Registro *arvb_registro) {
    return (arvb_registro == NULL) ? -2 : arvb_registro->C2;
}

long int arvb_registro_get_Pr2(ArvB_Registro *arvb_registro) {
    return (arvb_registro == NULL) ? -2 : arvb_registro->Pr2;
}

int arvb_registro_get_P3(ArvB_Registro *arvb_registro) {
    return (arvb_registro == NULL) ? -2 : arvb_registro->P3;
}

bool arvb_registro_set_tipoNo(ArvB_Registro *arvb_registro, int tipoNo){
    if(arvb_registro == NULL) return false;

    arvb_registro->tipoNo = tipoNo;
    return true;
}

bool arvb_registro_set_nroChaves(ArvB_Registro *arvb_registro, int nroChaves) {
    if(arvb_registro == NULL) return false;
    arvb_registro->nroChaves = nroChaves;
    return true;
}

bool arvb_registro_set_P1(ArvB_Registro *arvb_registro, int P1) {
    if(arvb_registro == NULL) return false;
    arvb_registro->P1 = P1;
    return true;
}

bool arvb_registro_set_C1(ArvB_Registro *arvb_registro, int C1) {
    if(arvb_registro == NULL) return false;
    arvb_registro->C1 = C1;
    return true;
}

bool arvb_registro_set_Pr1(ArvB_Registro *arvb_registro, long int Pr1) {
    if(arvb_registro == NULL) return false;
    arvb_registro->Pr1 = Pr1;
    return true;
}

bool arvb_registro_set_P2(ArvB_Registro *arvb_registro, int P2) {
    if(arvb_registro == NULL) return false;
    arvb_registro->P2 = P2;
    return true;
}

bool arvb_registro_set_C2(ArvB_Registro *arvb_registro, int C2) {
    if(arvb_registro == NULL) return false;
    arvb_registro->C2 = C2;
    return true;
}

bool arvb_registro_set_Pr2(ArvB_Registro *arvb_registro, long int Pr2) {
    if(arvb_registro == NULL) return false;
    arvb_registro->Pr2 = Pr2;
    return true;
}

bool arvb_registro_set_P3(ArvB_Registro *arvb_registro, int P3) {
    if(arvb_registro == NULL) return false;
    arvb_registro->P3 = P3;
    return true;
}

bool arvb_registro_inserirChave(ArvB_Registro *arvb_registro, int C, long int Pr, int P){
    if(arvb_registro == NULL || arvb_registro->nroChaves >= 2) return false;

    arvb_registro->nroChaves++;

    // Caso 1: A nova chave é a menor de todas
    if (arvb_registro->nroChaves == 1 || C < arvb_registro->C1) {
        // Desloca o que já existe para a direita
        arvb_registro->C2 = arvb_registro->C1;
        arvb_registro->Pr2 = arvb_registro->Pr1;
        arvb_registro->P3 = arvb_registro->P2;
        
        // Insere a nova chave na primeira posição
        arvb_registro->C1 = C;
        arvb_registro->Pr1 = Pr;
        arvb_registro->P2 = P; 
        // P1 não precisa ser modificado, pois continua sendo o ponteiro mais à esquerda.
    } 
    // Caso 2: A nova chave fica na segunda posição
    else {
        // Insere a nova chave na segunda posição
        arvb_registro->C2 = C;
        arvb_registro->Pr2 = Pr;
        arvb_registro->P3 = P;
    }

    return true;
}

ArvB_Registro *arvb_registro_criar(int tipoNo, int nroChaves, int P1, int C1, long int Pr1, int P2, int C2, long int Pr2, int P3){
    ArvB_Registro *arvb_registro = (ArvB_Registro *)malloc(sizeof(ArvB_Registro));
    if(arvb_registro == NULL) return NULL;

    arvb_registro->tipoNo = tipoNo;
    arvb_registro->nroChaves = nroChaves;
    arvb_registro->P1 = P1;
    arvb_registro->C1 = C1;
    arvb_registro->Pr1 = Pr1;
    arvb_registro->P2 = P2;
    arvb_registro->C2 = C2;
    arvb_registro->Pr2 = Pr2;
    arvb_registro->P3 = P3; 

    return arvb_registro;
}

ArvB_Registro *arvb_registro_ler(FILE *bin_arvb){
    if(bin_arvb == NULL) return NULL;

    int tipoNo;
    int nroChaves;
    int P1;
    int C1;
    long int Pr1;
    int P2;
    int C2;
    long int Pr2;
    int P3;

    fread(&tipoNo, sizeof(int), 1, bin_arvb);
    fread(&nroChaves, sizeof(int), 1, bin_arvb);
    fread(&P1, sizeof(int), 1, bin_arvb);
    fread(&C1, sizeof(int), 1, bin_arvb);
    fread(&Pr1, sizeof(long int), 1, bin_arvb);
    fread(&P2, sizeof(int), 1, bin_arvb);
    fread(&C2, sizeof(int), 1, bin_arvb);
    fread(&Pr2, sizeof(long int), 1, bin_arvb);
    fread(&P3, sizeof(int), 1, bin_arvb);

    ArvB_Registro *arvb_registro = arvb_registro_criar(tipoNo, nroChaves, P1, C1, Pr1, P2, C2, Pr2, P3);
    
    return arvb_registro;
}

bool arvb_registro_atualizar(ArvB_Registro *arvb_registro, int tipoNo, int nroChaves, int P1, int C1, long int Pr1, int P2, int C2, long int Pr2, int P3){
    if(arvb_registro == NULL) return false;
    
    arvb_registro->tipoNo = tipoNo;
    arvb_registro->nroChaves = nroChaves;
    arvb_registro->P1 = P1;
    arvb_registro->C1 = C1;
    arvb_registro->Pr1 = Pr1;
    arvb_registro->P2 = P2;
    arvb_registro->C2 = C2;
    arvb_registro->Pr2 = Pr2;
    arvb_registro->P3 = P3;
    return true;
}

bool arvb_registro_escrever(FILE *bin_arvb, ArvB_Registro *arvb_registro) {
    if(bin_arvb == NULL || arvb_registro == NULL) return false;

    fwrite(&(arvb_registro->tipoNo), sizeof(int), 1, bin_arvb);
    fwrite(&(arvb_registro->nroChaves), sizeof(int), 1, bin_arvb);
    fwrite(&(arvb_registro->P1), sizeof(int), 1, bin_arvb);
    fwrite(&(arvb_registro->C1), sizeof(int), 1, bin_arvb);
    fwrite(&(arvb_registro->Pr1), sizeof(long int), 1, bin_arvb);
    fwrite(&(arvb_registro->P2), sizeof(int), 1, bin_arvb);
    fwrite(&(arvb_registro->C2), sizeof(int), 1, bin_arvb);
    fwrite(&(arvb_registro->Pr2), sizeof(long int), 1, bin_arvb);
    fwrite(&(arvb_registro->P3), sizeof(int), 1, bin_arvb);

    return true;
}

bool arvb_registro_apagar(ArvB_Registro **arvb_registro){
    if(*arvb_registro == NULL) return false;
    free(*arvb_registro);
    (*arvb_registro) = NULL;
    return true;
}
#ifndef _ARVB_REGISTRO_H
#define _ARVB_REGISTRO_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _arvb_registro ArvB_Registro;

ArvB_Registro *arvb_registro_criar(int tipoNo, int nroChaves, int P1, int C1, long int Pr1, int P2, int C2, long int Pr2, int P3);
ArvB_Registro *arvb_registro_ler(FILE *bin_arvb);
bool arvb_registro_inserirChave(ArvB_Registro *arvb_registro, int C, long int Pr, int P);
bool arvb_registro_escrever(FILE *bin_arvb, ArvB_Registro *arvb_registro);
bool arvb_registro_apagar(ArvB_Registro **arvb_registro);
bool arvb_registro_atualizar(ArvB_Registro *arvb_registro, int tipoNo, int nroChaves, int P1, int C1, long int Pr1, int P2, int C2, long int Pr2, int P3);

int arvb_registro_get_tipoNo(ArvB_Registro *arvb_registro);
int arvb_registro_get_nroChaves(ArvB_Registro *arvb_registro);
int arvb_registro_get_P1(ArvB_Registro *arvb_registro);
int arvb_registro_get_C1(ArvB_Registro *arvb_registro);
long int arvb_registro_get_Pr1(ArvB_Registro *arvb_registro);
int arvb_registro_get_P2(ArvB_Registro *arvb_registro);
int arvb_registro_get_C2(ArvB_Registro *arvb_registro);
long int arvb_registro_get_Pr2(ArvB_Registro *arvb_registro);
int arvb_registro_get_P3(ArvB_Registro *arvb_registro);

bool arvb_registro_set_tipoNo(ArvB_Registro *arvb_registro, int tipoNo);
bool arvb_registro_set_nroChaves(ArvB_Registro *arvb_registro, int nroChaves);
bool arvb_registro_set_P1(ArvB_Registro *arvb_registro, int P1);
bool arvb_registro_set_C1(ArvB_Registro *arvb_registro, int C1);
bool arvb_registro_set_Pr1(ArvB_Registro *arvb_registro, long int Pr1);
bool arvb_registro_set_P2(ArvB_Registro *arvb_registro, int P2);
bool arvb_registro_set_C2(ArvB_Registro *arvb_registro, int C2);
bool arvb_registro_set_Pr2(ArvB_Registro *arvb_registro, long int Pr2);
bool arvb_registro_set_P3(ArvB_Registro *arvb_registro, int P3);
#endif
// Artur Domitti Camargo - 15441661
// Lucas Mello Ciosaki - 14591305

#include "cabecalho.h"

// Struct Cabecalho
struct _cabecalho{
    char status; 
    long int topo; 
    long int proxByteOffset; 
    int nroRegArq; 
    int nroRegRem; 
    char descreveIdentificador[23];
    char descreveYear[27];
    char descreveFinancialLoss[28];
    char codDescreveCountry;
    char descreveCountry[26];
    char codDescreveType;
    char descreveType[38];
    char codDescreveTargetIndustry;
    char descreveTargetIndustry[38];
    char codDescreveDefense;
    char descreveDefense[67];
};

// Cria o cabeçalho e inicializa os campos
Cabecalho *cabecalho_criar(){
    // Aloca memória para o cabeçalho
    Cabecalho *cabecalho = (Cabecalho *) malloc(sizeof(Cabecalho));
    if(cabecalho == NULL) return NULL;

    // Inicializa os campos do cabeçalho
    cabecalho->status = '0';
    cabecalho->topo = -1;
    cabecalho->proxByteOffset = 0;
    cabecalho->nroRegArq = 0;
    cabecalho->nroRegRem = 0;
    memcpy(cabecalho->descreveIdentificador, "IDENTIFICADOR DO ATAQUE", 23);
    memcpy(cabecalho->descreveYear, "ANO EM QUE O ATAQUE OCORREU", 27);
    memcpy(cabecalho->descreveFinancialLoss, "PREJUIZO CAUSADO PELO ATAQUE", 28);
    cabecalho->codDescreveCountry = '1';
    memcpy(cabecalho->descreveCountry, "PAIS ONDE OCORREU O ATAQUE", 26);
    cabecalho->codDescreveType = '2';
    memcpy(cabecalho->descreveType, "TIPO DE AMEACA A SEGURANCA CIBERNETICA", 38);
    cabecalho->codDescreveTargetIndustry = '3';
    memcpy(cabecalho->descreveTargetIndustry, "SETOR DA INDUSTRIA QUE SOFREU O ATAQUE", 38);
    cabecalho->codDescreveDefense = '4';
    memcpy(cabecalho->descreveDefense, "ESTRATEGIA DE DEFESA CIBERNETICA EMPREGADA PARA RESOLVER O PROBLEMA", 67);

    return cabecalho;
}

// Setters para os campos do cabeçalho

// Atualiza o status do cabeçalho
bool cabecalho_set_status(Cabecalho *cabecalho, char status){
    if(cabecalho == NULL) return false;
    cabecalho->status = status;
    return true;
}

// Atualiza o topo do cabeçalho
bool cabecalho_set_topo(Cabecalho *cabecalho, long int topo){
    if(cabecalho == NULL) return false;
    cabecalho->topo = topo;
    return true;
}

// Atualiza o próximo byte offset do cabeçalho
bool cabecalho_set_proxByteOffset(Cabecalho *cabecalho, long int proxByteOffset){
    if(cabecalho == NULL) return false;
    cabecalho->proxByteOffset = proxByteOffset;
    return true;
}

// Atualiza o número de registros arquivados
bool cabecalho_set_nroRegArq(Cabecalho *cabecalho, int nroRegArq){
    if(cabecalho == NULL) return false;
    cabecalho->nroRegArq = nroRegArq;
    return true;
}

// Atualiza o número de registros removidos
bool cabecalho_set_nroRegRem(Cabecalho *cabecalho, int nroRegRem){
    if(cabecalho == NULL) return false;
    cabecalho->nroRegRem = nroRegRem;
    return true;
}

// Atualiza todos os campos do cabeçalho que são alteráveis
bool cabecalho_update(Cabecalho *cabecalho, char status, long int topo, long int proxByteOffset, int nroRegArq, int nroRegRem){
    if(cabecalho == NULL) return false;
    cabecalho->status = status;
    cabecalho->topo = topo;
    cabecalho->proxByteOffset = proxByteOffset;
    cabecalho->nroRegArq = nroRegArq;
    cabecalho->nroRegRem = nroRegRem;
    return true;
}

// Getters para os campos do cabeçalho

// Retorna o status 
long int cabecalho_get_topo(Cabecalho *cabecalho){
    if(cabecalho == NULL) return -1;
    return cabecalho->topo;
}

// Retorna o próximo byte offset
long int cabecalho_get_proxByteOffset(Cabecalho *cabecalho){
    if(cabecalho == NULL) return -1;
    return cabecalho->proxByteOffset;
}

// Retorna o número de registros arquivados
int cabecalho_get_nroRegArq(Cabecalho *cabecalho){
    if(cabecalho == NULL) return -1;
    return cabecalho->nroRegArq;
}

// Retorna o número de registros removidos
int cabecalho_get_nroRegRem(Cabecalho *cabecalho){
    if(cabecalho == NULL) return -1;
    return cabecalho->nroRegRem;
}

// Retorna a descrição do identificador do ataque
char* cabecalho_get_descreveIdentificador(Cabecalho *cabecalho){
    if(cabecalho == NULL) return NULL;
    return cabecalho->descreveIdentificador;
}

// Retorna a descrição do ano do ataque
char *cabecalho_get_descreveYear(Cabecalho *cabecalho){
    if(cabecalho == NULL) return NULL;
    return cabecalho->descreveYear;
}

// Retorna a descrição do prejuízo financeiro
char *cabecalho_get_descreveFinancialLoss(Cabecalho *cabecalho){
    if(cabecalho == NULL) return NULL;
    return cabecalho->descreveFinancialLoss;
}

// Retorna a keyword do país
char cabecalho_get_codDescreveCountry(Cabecalho *cabecalho){
    if(cabecalho == NULL) return '\0';
    return cabecalho->codDescreveCountry;
}

// Retorna a descrição do país
char *cabecalho_get_descreveCountry(Cabecalho *cabecalho){
    if(cabecalho == NULL) return NULL;
    return cabecalho->descreveCountry;
}

// Retorna a keyword do tipo de ataque
char cabecalho_get_codDescreveType(Cabecalho *cabecalho){
    if(cabecalho == NULL) return '\0';
    return cabecalho->codDescreveType;
}

//  Retorna a descrição do tipo de ataque
char *cabecalho_get_descreveType(Cabecalho *cabecalho){
    if(cabecalho == NULL) return NULL;
    return cabecalho->descreveType;
}

// Retorna a keyword do setor da indústria
char cabecalho_get_codDescreveTargetIndustry(Cabecalho *cabecalho){
    if(cabecalho == NULL) return '\0';
    return cabecalho->codDescreveTargetIndustry;
}

// Retorna a descrição do setor da indústria
char *cabecalho_get_descreveTargetIndustry(Cabecalho *cabecalho){
    if(cabecalho == NULL) return NULL;
    return cabecalho->descreveTargetIndustry;
}

// Retorna a keyword da defesa cibernética
char cabecalho_get_codDescreveDefense(Cabecalho *cabecalho){
    if(cabecalho == NULL) return '\0';
    return cabecalho->codDescreveDefense;
}

// Retorna a descrição da defesa cibernética
char *cabecalho_get_descreveDefense(Cabecalho *cabecalho){
    if(cabecalho == NULL) return NULL;
    return cabecalho->descreveDefense;
}

// Funções auxiliares

// Escreve o cabeçalho no arquivo binário
bool cabecalho_escrever(FILE *bin, Cabecalho *cabecalho){
    
    if(cabecalho == NULL) return false;
    //Move para o comeco do arquivo
    fseek(bin, 0, SEEK_SET);

    // Escreve o cabeçalho no arquivo binário
    fwrite(&cabecalho->status, sizeof(char), 1, bin);
    fwrite(&cabecalho->topo, sizeof(long int), 1, bin);
    fwrite(&cabecalho->proxByteOffset, sizeof(long int), 1, bin);
    fwrite(&cabecalho->nroRegArq, sizeof(int), 1, bin);
    fwrite(&cabecalho->nroRegRem, sizeof(int), 1, bin);
    fwrite(cabecalho->descreveIdentificador, sizeof(char), 23, bin);
    fwrite(cabecalho->descreveYear, sizeof(char), 27, bin);
    fwrite(cabecalho->descreveFinancialLoss, sizeof(char), 28, bin);
    fwrite(&cabecalho->codDescreveCountry, sizeof(char), 1, bin);
    fwrite(cabecalho->descreveCountry, sizeof(char), 26, bin);
    fwrite(&cabecalho->codDescreveType, sizeof(char), 1, bin);
    fwrite(cabecalho->descreveType, sizeof(char), 38, bin);
    fwrite(&cabecalho->codDescreveTargetIndustry, sizeof(char), 1, bin);
    fwrite(cabecalho->descreveTargetIndustry, sizeof(char), 38, bin);
    fwrite(&cabecalho->codDescreveDefense, sizeof(char), 1, bin);
    fwrite(cabecalho->descreveDefense, sizeof(char), 67, bin);

    return true;
}

// Lê o cabeçalho do arquivo binário
Cabecalho *cabecalho_ler_bin(FILE *bin){
    fseek(bin, 0 , SEEK_SET);
     Cabecalho *cabecalho = cabecalho_criar();

    // Lê o cabecalho
    if(cabecalho != NULL){
        fread(&cabecalho->status, sizeof(char), 1, bin);
        fread(&cabecalho->topo, sizeof(long int), 1, bin);
        fread(&cabecalho->proxByteOffset, sizeof(long int), 1, bin);
        fread(&cabecalho->nroRegArq, sizeof(int), 1, bin);
        fread(&cabecalho->nroRegRem, sizeof(int), 1, bin);
        fread(&cabecalho->descreveIdentificador,sizeof(char), 23, bin);
        fread(&cabecalho->descreveYear,sizeof(char), 27, bin);
        fread(&cabecalho->descreveFinancialLoss,sizeof(char), 28, bin);
        fread(&cabecalho->codDescreveCountry,sizeof(char), 1, bin);
        fread(&cabecalho->descreveCountry,sizeof(char), 26, bin);
        fread(&cabecalho->codDescreveType,sizeof(char), 1, bin);
        fread(&cabecalho->descreveType,sizeof(char), 38, bin);
        fread(&cabecalho->codDescreveTargetIndustry,sizeof(char), 1, bin);
        fread(&cabecalho->descreveTargetIndustry,sizeof(char), 38, bin);
        fread(&cabecalho->codDescreveDefense,sizeof(char), 1, bin);
        fread(&cabecalho->descreveDefense,sizeof(char), 67, bin);
    }
    return cabecalho;
}

// Libera a memória alocada para o cabeçalho
bool cabecalho_apagar(Cabecalho **cabecalho){
    if(*cabecalho == NULL) return false;
    free(*cabecalho);
    *cabecalho = NULL;
    return true;
}

// Verifica se o cabeçalho está estável (status '1')
bool cabecalho_estavel(Cabecalho *cabecalho){
    if(cabecalho == NULL) return false;
    if(cabecalho->status == '1') return true;
    else return false;
}
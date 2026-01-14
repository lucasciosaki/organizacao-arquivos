// Artur Domitti Camargo - 15441661
// Lucas Mello Ciosaki - 14591305

#include <stdio.h>
#include "registro.h"

// Struct do registro de dados
struct _registro{
    // Campos de controle
    char removido; 
    int tamanhoRegistro; 
    long int prox; 

    // Campos de tamanho fixo
    int idAttack; 
    int year; 
    float financialLoss; 

    // Campos de tamanho variável
    char *country;
    char *attackType;
    char *targetIndustry;
    char *defenseMechanism;
};

// Cria o registro e inicia os valores
Registro* registro_criar(char removido, long int prox, int idAttack, int year, float financialLoss, char *country, char *attackType, char *targetIndustry, char *defenseMechanism){
    // Aloca memória para o registro
    Registro *registro = (Registro*) malloc(sizeof(Registro));
    if(registro == NULL) return NULL;

    // Inicializa os valores do registro
    registro->removido = removido;
    registro->prox = prox;
    registro->idAttack = idAttack;
    registro->year = year;
    registro->financialLoss = financialLoss;                                                                             
    registro->country = country;                                                 
    registro->attackType = attackType;
    registro->targetIndustry = targetIndustry;
    registro->defenseMechanism = defenseMechanism;

    int tamanhoCampoVariavel = 0;
    tamanhoCampoVariavel += ((registro->country != NULL && strcmp(registro->country, "") != 0)) ? (strlen(registro->country)+2) : 0;
    tamanhoCampoVariavel += (registro->attackType != NULL && strcmp(registro->attackType, "") != 0) ? (strlen(registro->attackType)+2) : 0;
    tamanhoCampoVariavel += (registro->targetIndustry != NULL && strcmp(registro->targetIndustry, "") != 0) ? (strlen(registro->targetIndustry)+2) : 0;
    tamanhoCampoVariavel += (registro->defenseMechanism != NULL && strcmp(registro->defenseMechanism, "") != 0) ? (strlen(registro->defenseMechanism)+2) : 0;
    registro->tamanhoRegistro = sizeof(registro->prox) + sizeof(registro->idAttack) + sizeof(registro->year) + sizeof(registro->financialLoss) + tamanhoCampoVariavel;

    return registro;
}

// Verifica se o registro foi removido
bool registro_removido(Registro *registro){
    	if(registro == NULL) return true;
        if(registro->removido == '1') return true;
        return false;
}

// Getters para os campos do registro

// Retorna o tamanho do registro
int registro_get_tamanhoRegistro(Registro *registro){
    if(registro == NULL) return -1;
    return registro->tamanhoRegistro;
}

// Retorna o campo prox (byteoffset do próximo registro logicamente removido)
long int registro_get_prox(Registro *registro){
    if(registro == NULL) return -1;
    return registro->prox;
}

// Retorna o campo idAttack (identificador do ataque)
int registro_get_idAttack(Registro *registro){
    if(registro == NULL) return -1;
    return registro->idAttack;
}

// Retorna o campo year 
int registro_get_year(Registro *registro){
    if(registro == NULL) return -1;
    return registro->year;
}

// Retorna o campo financialLoss 
float registro_get_financialLoss(Registro *registro){
    if(registro == NULL) return -1;
    return registro->financialLoss;
}

// Retorna o campo country
char *registro_get_country(Registro *registro){
    if(registro == NULL) return NULL;
    return registro->country;
}

// Retorna o campo attackType
char *registro_get_attackType(Registro *registro){
    if(registro == NULL) return NULL;
    return registro->attackType;
}

// Retorna o campo targetIndustry
char *registro_get_targetIndustry(Registro *registro){
    if(registro == NULL) return NULL;
    return registro->targetIndustry;
}

// Retorna o campo defenseMechanism
char *registro_get_defenseMechanism(Registro *registro){
    if(registro == NULL) return NULL;
    return registro->defenseMechanism;
}

bool registro_set_tamanhoRegistro(Registro *registro, int tamanhoRegistro){
    if(registro == NULL) return false;
    registro->tamanhoRegistro = tamanhoRegistro;
    return true;
}

bool registro_set_prox(Registro *registro, long int prox){
    if(registro == NULL) return false;
    registro->prox = prox;
    return true;
}


// Escreve o registro no arquivo binário
bool registro_escrever(FILE *bin, Registro *registro){

    if (registro == NULL || bin == NULL)   return false;

    char separacao = '|'; // Delimiter para os campos de tamanho variável

    fwrite(&registro->removido, sizeof(char), 1, bin);
    fwrite(&registro->tamanhoRegistro, sizeof(int), 1, bin);
    fwrite(&registro->prox, sizeof(long int), 1, bin);

    if(registro_removido(registro)){
        fseek(bin, registro->tamanhoRegistro - sizeof(registro->prox), SEEK_CUR);
        return true;
    }

    fwrite(&registro->idAttack, sizeof(int), 1, bin);
    fwrite(&registro->year, sizeof(int), 1, bin);
    fwrite(&registro->financialLoss, sizeof(float), 1, bin);
    
    int tamCountry, tamAttackType, tamTargetIndustry, tamDefenseMechanism;
    tamCountry = 0;
    tamAttackType = 0;
    tamTargetIndustry = 0;
    tamDefenseMechanism = 0;

    if(registro->country != NULL && strcmp(registro->country, "") != 0){
        char id = '1';
        fwrite(&id, sizeof(char), 1, bin);
        fwrite(registro->country, sizeof(char), strlen(registro->country), bin);
        fwrite(&separacao, sizeof(char), 1, bin);
        tamCountry = strlen(registro->country) + 2;
    }

    if(registro->attackType != NULL && strcmp(registro->attackType, "") != 0){
        char id = '2';
        fwrite(&id, sizeof(char), 1, bin);
        fwrite(registro->attackType, sizeof(char), strlen(registro->attackType), bin);
        fwrite(&separacao, sizeof(char), 1, bin);
        tamAttackType = strlen(registro->attackType) + 2;
    }
    
    if(registro->targetIndustry != NULL && strcmp(registro->targetIndustry, "") != 0){
        char id = '3';
        fwrite(&id, sizeof(char), 1, bin);
        fwrite(registro->targetIndustry, sizeof(char), strlen(registro->targetIndustry), bin);
        fwrite(&separacao, sizeof(char), 1, bin);
        tamTargetIndustry = strlen(registro->targetIndustry) + 2;
    }
    
    if(registro->defenseMechanism != NULL && strcmp(registro->defenseMechanism, "") != 0){
        char id = '4';
        fwrite(&id, sizeof(char), 1, bin);
        fwrite(registro->defenseMechanism, sizeof(char), strlen(registro->defenseMechanism), bin);
        fwrite(&separacao, sizeof(char), 1, bin);
        tamDefenseMechanism = strlen(registro->defenseMechanism) + 2;
    }

    int bytesRestantes = registro->tamanhoRegistro - (sizeof(registro->prox) + sizeof(registro->idAttack) + sizeof(registro->year) + sizeof(registro->financialLoss) + tamCountry + tamAttackType + tamTargetIndustry + tamDefenseMechanism);
    
    char lixo = '$';
    while(bytesRestantes > 0){
        fwrite(&lixo, sizeof(char), 1, bin);
        bytesRestantes--;
    }

    return true;
}

// Lê o registro de um arquivo CSV e cria um objeto Registro
Registro *registro_ler_csv(FILE *csv, char linha[]){
    
    if (linha[strlen(linha) - 1] == '\n') {
        linha[strlen(linha) - 1] = '\0'; // Substitui o \n pelo \0
    }

    char removido = '0';
    long int prox = -1;
    int idAttack = -1;
    int year = -1;
    float financialLoss = -1;
    char *country = NULL;
    char *attackType = NULL;
    char *targetIndustry = NULL;
    char *defenseMechanism = NULL;

    char *pt = linha;
    char *campos;
    int campoAtual = 0;
    while ((campos = strsep(&pt, ",")) != NULL && campoAtual < 7) {
                    
        switch (campoAtual) {
            case 0:
                idAttack = (strcmp(campos, "") != 0) ?  atoi(campos) : -1;                 
            break;
            case 1:
                year = (strcmp(campos, "") != 0) ?  atoi(campos) : -1;
                break;
            case 2:
                financialLoss = (strcmp(campos, "") != 0) ?  atof(campos) : -1;
                break;
            case 3:
                country = (strcmp(campos, "") !=0 ) ? (malloc(strlen(campos)+1)) : NULL;
                if(country != NULL) strcpy(country, campos); 
                break;
            case 4:
                attackType = (strcmp(campos, "") !=0 ) ? (malloc(strlen(campos)+1)) : NULL;
                if(attackType != NULL) strcpy(attackType, campos); 
                break;
            case 5:
                targetIndustry = (strcmp(campos, "") !=0 ) ? (malloc(strlen(campos)+1)) : NULL;
                if(targetIndustry != NULL) strcpy(targetIndustry, campos); 
                break;
            case 6:
                defenseMechanism = (strcmp(campos, "") !=0 ) ? (malloc(strlen(campos)+1)) : NULL;
                if(defenseMechanism != NULL) strcpy(defenseMechanism, campos);       
                break;        
        }
        campoAtual++;
    }
    Registro *registro = registro_criar(removido, prox, idAttack, year, financialLoss, country, attackType, targetIndustry, defenseMechanism);
    return registro;
}

// Lê o registro de um arquivo binário e cria um objeto Registro
Registro *registro_ler_bin(FILE *bin){
    char removido;
    int tamanhoRegistro;
    long int prox;
    int idAttack, year;
    float financialLoss;
    char *country, *attackType, *targetIndustry, *defenseMechanism;
    
    fread(&removido, sizeof(char), 1, bin);
    fread(&tamanhoRegistro, sizeof(int), 1, bin);
    fread(&prox, sizeof(long int), 1, bin);

    if(removido == '1') {
        fseek(bin, tamanhoRegistro - sizeof(prox), SEEK_CUR);
        Registro *registro = (Registro *)malloc(sizeof(Registro));
        registro->removido = removido;
        registro->tamanhoRegistro = tamanhoRegistro;
        registro->prox = prox;
        return registro;
    }
    fread(&idAttack, sizeof(int), 1, bin);
    fread(&year, sizeof(int), 1, bin);
    fread(&financialLoss, sizeof(float), 1, bin);
    
    country = NULL;
    attackType = NULL;
    targetIndustry = NULL;
    defenseMechanism = NULL;

    int bytesLidos = sizeof(long int) + sizeof(int) + sizeof(int) + sizeof(float);
    int bytesRestantes = tamanhoRegistro - bytesLidos;

    char *buffer = (char *)malloc(bytesRestantes + 1);
    fread(buffer, sizeof(char), bytesRestantes, bin);
    buffer[bytesRestantes] = '\0';
    
    char *campos = strtok(buffer, "|");
    
    while(campos != NULL) {
        char keyword = campos[0];
        char *valorCampo = campos + 1;
        
        switch(keyword) {
            case '1':
                country = (strcmp(campos, "") == 0) ? NULL : (char*) malloc((strlen(valorCampo)+1)*sizeof(char));
                if(country != NULL) {
                    strcpy(country, valorCampo);
                }
                break;
            case '2':
                attackType = (strcmp(valorCampo, "") == 0) ? NULL : (char*) malloc((strlen(valorCampo)+1)*sizeof(char));
                if(attackType != NULL) {
                    strcpy(attackType, valorCampo);
                }
                break;
            case '3':
                targetIndustry = (strcmp(valorCampo, "") == 0) ? NULL : (char*) malloc((strlen(valorCampo)+1)*sizeof(char));
                if(targetIndustry != NULL) {
                    strcpy(targetIndustry, valorCampo);
                }
                break;
            case '4':
                defenseMechanism = (strcmp(valorCampo, "") == 0) ? NULL : (char*) malloc((strlen(valorCampo)+1)*sizeof(char));
                if(defenseMechanism != NULL) {
                    strcpy(defenseMechanism, valorCampo);
                }
                break;
        }
        campos = strtok(NULL, "|");
        
    }
    free(buffer);

    
    Registro *registro;
    
    registro = registro_criar(removido, prox, idAttack, year, financialLoss, country, attackType, targetIndustry, defenseMechanism);
    registro->tamanhoRegistro = tamanhoRegistro;

    return registro;

}

// Compara os campos do registro com os valores passados como parâmetro
bool registro_comparar(Registro *registro, int cmp_idAttack, int cmp_year, float cmp_financialLoss, char cmp_country[], char cmp_attackType[], char cmp_targetIndustry[], char cmp_defenseMechanism[]){
    if(registro == NULL) return false;

    if(registro_removido(registro)) return false;

    if(cmp_idAttack != -1 && registro->idAttack != cmp_idAttack) return false;

    if(cmp_year != -1 && registro->year != cmp_year) return false;

    if(cmp_financialLoss != -1 && registro->financialLoss != cmp_financialLoss) return false;
    
    if(strcmp(cmp_country, "") != 0 && registro->country == NULL) return false;
    if(strcmp(cmp_country, "") != 0 && (strcmp(registro->country, cmp_country)) != 0) {
        return false;
    }
    
    
    if(strcmp(cmp_attackType, "") != 0 && registro->attackType == NULL) return false;
    if(strcmp(cmp_attackType, "") != 0 && (strcmp(registro->attackType, cmp_attackType)) != 0) {
        return false;
    }

    if(strcmp(cmp_targetIndustry, "") != 0 && registro->targetIndustry == NULL) return false;
    if(strcmp(cmp_targetIndustry, "") != 0 && (strcmp(registro->targetIndustry, cmp_targetIndustry)) != 0) {
        return false;
    }

    if(strcmp(cmp_defenseMechanism, "") != 0 && registro->defenseMechanism == NULL) return false;
    if(strcmp(cmp_defenseMechanism, "") != 0 && (strcmp(registro->defenseMechanism, cmp_defenseMechanism)) != 0) {
        return false;
    }
    return true;
}

// Imprime os campos do registro
bool registro_imprimir(Registro *registro, Cabecalho *cabecalho){
    if(registro == NULL) return false;

    char *descreveIdentificador = cabecalho_get_descreveIdentificador(cabecalho);
    printf("%.*s: ", 23, descreveIdentificador);
    if(registro->idAttack != -1) printf("%d\n", registro->idAttack);
    else printf("NADA CONSTA");
    

    char *descreveYear = cabecalho_get_descreveYear(cabecalho);
    printf("%.*s: ", 27, descreveYear);
    printf(registro->year != -1 ? "%d\n" : "NADA CONSTA\n", registro->year);

    char *descreveCountry = cabecalho_get_descreveCountry(cabecalho);
    printf("%.*s: ", 26, descreveCountry);
    printf(registro->country != NULL && registro->country[0] != '\0' ? "%s\n" : "NADA CONSTA\n", registro->country ? registro->country : "");

    char *descreveTargetIndustry = cabecalho_get_descreveTargetIndustry(cabecalho);
    printf("%.*s: ", 38, descreveTargetIndustry);
    printf(registro->targetIndustry != NULL && registro->targetIndustry[0] != '\0' ? "%s\n" : "NADA CONSTA\n", registro->targetIndustry ? registro->targetIndustry : "");

    char *descreveType = cabecalho_get_descreveType(cabecalho);
    printf("%.*s: ", 38, descreveType);
    printf(registro->attackType != NULL && registro->attackType[0] != '\0' ? "%s\n" : "NADA CONSTA\n", registro->attackType ? registro->attackType : "");

    char *descreveFinancialLoss = cabecalho_get_descreveFinancialLoss(cabecalho);
    printf("%.*s: ", 28, descreveFinancialLoss);
    printf(registro->financialLoss != -1 ? "%.2f\n" : "NADA CONSTA\n", registro->financialLoss);

    char *descreveDefense = cabecalho_get_descreveDefense(cabecalho);
    printf("%.*s: ", 67, descreveDefense);
    printf(registro->defenseMechanism != NULL && registro->defenseMechanism[0] != '\0' ? "%s\n" : "NADA CONSTA\n", registro->defenseMechanism ? registro->defenseMechanism : "");

    printf("\n");
}

//Remove lógicamente o registro do arquivo de dados, atualizando a pilha
bool registro_remover(FILE *bin, Registro *registro, Cabecalho *cabecalho){
    if(registro == NULL || registro_removido(registro)) return false;
    
    long int byteOffset = ftell(bin) - (sizeof(registro->removido) + sizeof(registro->tamanhoRegistro) + registro->tamanhoRegistro);

    registro->prox = cabecalho_get_topo(cabecalho);
    if(!cabecalho_set_topo(cabecalho, byteOffset)) return false;
    registro->removido = '1';

    cabecalho_set_nroRegRem(cabecalho, cabecalho_get_nroRegRem(cabecalho) + 1);
    cabecalho_set_nroRegArq(cabecalho, cabecalho_get_nroRegArq(cabecalho)-1);
    if(!cabecalho_escrever(bin, cabecalho)) return false;
    fseek(bin, byteOffset, SEEK_SET);
    if(!registro_escrever(bin, registro)) return false;
    
    
    return true;
}


// Apaga o registro e libera a memória alocada
bool registro_apagar(Registro **registro){
    if (registro == NULL || *registro == NULL) return false;
    if(registro_removido(*registro)){
        free(*registro);
        return true;
    }

    if((*registro)->country != NULL) free((*registro)->country);
    if((*registro)->attackType != NULL) free((*registro)->attackType);
    if((*registro)->targetIndustry != NULL) free((*registro)->targetIndustry);
    if((*registro)->defenseMechanism != NULL) free((*registro)->defenseMechanism);
    free(*registro);
    *registro = NULL;
    return true;
}

long int registro_inserir(FILE *bin, Registro *novo, Cabecalho *cabecalho){
    if(novo == NULL || cabecalho == NULL) return -1;

    long int atual = cabecalho_get_topo(cabecalho);
   
    long int anterior = -1;
    while(atual != -1){
        fseek(bin, atual, SEEK_SET);
        Registro *no = registro_ler_bin(bin);
        if(registro_get_tamanhoRegistro(novo) <= registro_get_tamanhoRegistro(no)){
            registro_set_tamanhoRegistro(novo, registro_get_tamanhoRegistro(no));
            if(atual == cabecalho_get_topo(cabecalho)){
                cabecalho_set_topo(cabecalho, registro_get_prox(no));
            }
            else{
                fseek(bin, anterior, SEEK_SET);
                Registro *ant = registro_ler_bin(bin);
                registro_set_prox(ant, registro_get_prox(no));
                fseek(bin, anterior, SEEK_SET);
                registro_escrever(bin, ant);
                registro_apagar(&ant);
            }
            break;
        }
        else{
            anterior = atual;
            atual = registro_get_prox(no);
        }
        registro_apagar(&no);
    }
    if(atual != -1){
         cabecalho_set_nroRegRem(cabecalho, cabecalho_get_nroRegRem(cabecalho)-1);
    }
    else{
        atual = cabecalho_get_proxByteOffset(cabecalho);
        cabecalho_set_proxByteOffset(cabecalho, atual + sizeof(novo->removido) + sizeof(novo->tamanhoRegistro) + registro_get_tamanhoRegistro(novo));
    }
    

    fseek(bin, atual, SEEK_SET);
    registro_escrever(bin, novo);
    cabecalho_set_nroRegArq(cabecalho, cabecalho_get_nroRegArq(cabecalho)+1);

    return atual;
}

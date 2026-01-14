#include "arvB.h"





long int busca(FILE *bin_arvb, int RRN, int C, int *noAchado, int *posAchado) {
    
    if (RRN == -1) {
        return -1;
    }
    
    
    fseek(bin_arvb, (long)(RRN + 1) * TAM_NO, SEEK_SET);
    ArvB_Registro *no_atual = arvb_registro_ler(bin_arvb);

    if (no_atual == NULL) {
        return -1; 
    }

    
    if (arvb_registro_get_nroChaves(no_atual) >= 1) {
        
        if (C == arvb_registro_get_C1(no_atual)) {
            (*noAchado) = RRN;
            (*posAchado) = 1;
            long int Pr1 = arvb_registro_get_Pr1(no_atual);
            arvb_registro_apagar(&no_atual);
            return Pr1;
        }
    }
    if (arvb_registro_get_nroChaves(no_atual) == 2) {
        
        if (C == arvb_registro_get_C2(no_atual)) {
            (*noAchado) = RRN;
            (*posAchado) = 2;
            long int Pr2 = arvb_registro_get_Pr2(no_atual);
            arvb_registro_apagar(&no_atual);
            return Pr2;
        }
    }

   
    if (arvb_registro_get_tipoNo(no_atual) == -1) {
        arvb_registro_apagar(&no_atual);
        return -1;
    }

    
    int proximo_RRN;
    int nroChaves = arvb_registro_get_nroChaves(no_atual);
    int C1 = arvb_registro_get_C1(no_atual);

    if (nroChaves == 1) {
        if (C < C1) {
            proximo_RRN = arvb_registro_get_P1(no_atual);
        } else {
            proximo_RRN = arvb_registro_get_P2(no_atual);
        }
    } else { // nroChaves == 2
        int C2 = arvb_registro_get_C2(no_atual);
        if (C < C1) {
            proximo_RRN = arvb_registro_get_P1(no_atual);
        } else if (C < C2) {
            proximo_RRN = arvb_registro_get_P2(no_atual);
        } else {
            proximo_RRN = arvb_registro_get_P3(no_atual);
        }
    }

   
    arvb_registro_apagar(&no_atual);
    return busca(bin_arvb, proximo_RRN, C, noAchado, posAchado);
}

long arvb_buscar(FILE *bin_arvb, ArvB_Cabecalho *arvb_cabecalho, int chave) {
    if (bin_arvb == NULL || arvb_cabecalho == NULL) {
        return -1;
    }

    int noAchado, posAchado;
    int RRN_raiz = arvb_cabecalho_get_noRaiz(arvb_cabecalho);
    
    // Utiliza a função busca existente
    long int resultado = busca(bin_arvb, RRN_raiz, chave, &noAchado, &posAchado);
    
    return resultado;
}

void split(FILE *bin_arvb, ArvB_Cabecalho *arvb_cabecalho, int RRN, int C, long int Pr, int P, ArvB_Registro *arvb_registro, int *promoC, long int *promoPr, int *promoP){
    int new_RRN = arvb_cabecalho_get_proxRRN(arvb_cabecalho);
    (*promoP) = new_RRN;
    arvb_cabecalho_set_proxRRN(arvb_cabecalho, new_RRN+1);
    arvb_cabecalho_set_nroNos(arvb_cabecalho, arvb_cabecalho_get_nroNos(arvb_cabecalho)+1);
    ArvB_Registro *novo_no;


    if(C < arvb_registro_get_C1(arvb_registro)){
        
        (*promoC) = arvb_registro_get_C1(arvb_registro);
        (*promoPr) = arvb_registro_get_Pr1(arvb_registro);

        int tipoNo1;
        if(arvb_registro_get_P2(arvb_registro) != -1 || arvb_registro_get_P3(arvb_registro) != -1) tipoNo1 = 1;
        else tipoNo1 = -1;

        novo_no = arvb_registro_criar(tipoNo1, 1, arvb_registro_get_P2(arvb_registro), arvb_registro_get_C2(arvb_registro), arvb_registro_get_Pr2(arvb_registro), arvb_registro_get_P3(arvb_registro), -1, -1, -1);
        
        int tipoNo2;
        if(arvb_registro_get_P1(arvb_registro) != -1 || P != -1) tipoNo2 = 1;
        else tipoNo2 = -1;

        arvb_registro_atualizar(arvb_registro, tipoNo2, 1, arvb_registro_get_P1(arvb_registro), C, Pr, P, -1, -1, -1);
        
    }
    else{ 
        if(C < arvb_registro_get_C2(arvb_registro)){

            (*promoC) = C;
            (*promoPr) = Pr;

            int tipoNo1;
            if(P != -1 || arvb_registro_get_P3(arvb_registro) != -1) tipoNo1 = 1;
            else tipoNo1 = -1;

            novo_no = arvb_registro_criar(tipoNo1, 1, P, arvb_registro_get_C2(arvb_registro), arvb_registro_get_Pr2(arvb_registro), arvb_registro_get_P3(arvb_registro), -1, -1, -1);
            
            int tipoNo2;
            if(arvb_registro_get_P1(arvb_registro) != -1 || arvb_registro_get_P2(arvb_registro) != -1) tipoNo2 = 1;
            else tipoNo2 = -1;

            arvb_registro_atualizar(arvb_registro, tipoNo2, 1, arvb_registro_get_P1(arvb_registro), arvb_registro_get_C1(arvb_registro), arvb_registro_get_Pr1(arvb_registro), arvb_registro_get_P2(arvb_registro) , -1, -1, -1);
            
            
        }
        else{

            (*promoC) = arvb_registro_get_C2(arvb_registro);
            (*promoPr) = arvb_registro_get_Pr2(arvb_registro);

            int tipoNo1;
            if(arvb_registro_get_P3(arvb_registro) != -1 || P != -1) tipoNo1 = 1;
            else tipoNo1 = -1;

            novo_no = arvb_registro_criar(tipoNo1, 1, arvb_registro_get_P3(arvb_registro), C, Pr, P, -1, -1, -1);
            
            int tipoNo2;
            if(arvb_registro_get_P1(arvb_registro) != -1 || arvb_registro_get_P2(arvb_registro) != -1) tipoNo2 = 1;
            else tipoNo2 = -1;
            arvb_registro_atualizar(arvb_registro, tipoNo2, 1, arvb_registro_get_P1(arvb_registro), arvb_registro_get_C1(arvb_registro), arvb_registro_get_Pr1(arvb_registro), arvb_registro_get_P2(arvb_registro) , -1, -1, -1);
            
        }
    }
    fseek(bin_arvb, (RRN+1)*TAM_NO, SEEK_SET);
    arvb_registro_escrever(bin_arvb, arvb_registro);

    fseek(bin_arvb, (new_RRN+1)*TAM_NO, SEEK_SET);
    arvb_registro_escrever(bin_arvb, novo_no);

    arvb_registro_apagar(&novo_no);
    return;

}

int inserir(FILE *bin_arvb, ArvB_Cabecalho *arvb_cabecalho, int RRN, int C, long int Pr, int *promoRRN, int *promoC, long int *promoPr){
    if(RRN == -1){
        (*promoC) = C;
        (*promoPr) = Pr;
        (*promoRRN) = -1;
        return 1;
    }

    fseek(bin_arvb, (RRN + 1)*TAM_NO, SEEK_SET);
    ArvB_Registro *arvb_registro = arvb_registro_ler(bin_arvb);

    int P;

    if (arvb_registro_get_nroChaves(arvb_registro) == 1) {
        
        int C1 = arvb_registro_get_C1(arvb_registro);
        if (C == C1) { 
            arvb_registro_apagar(&arvb_registro);
            return -1;
        }
        
        if (C < C1) {
            P = arvb_registro_get_P1(arvb_registro);
        } else {
            P = arvb_registro_get_P2(arvb_registro);
        }
    } else {
        
        int C1 = arvb_registro_get_C1(arvb_registro);
        int C2 = arvb_registro_get_C2(arvb_registro);
        if (C == C1 || C == C2) { 
            arvb_registro_apagar(&arvb_registro);
            return -1;
        }

        if (C < C1) {
            P = arvb_registro_get_P1(arvb_registro);
        } else if (C < C2) {
            P = arvb_registro_get_P2(arvb_registro);
        } else {
            P = arvb_registro_get_P3(arvb_registro);
        }
    }

    int vret = inserir(bin_arvb, arvb_cabecalho, P, C, Pr, promoRRN, promoC, promoPr);

    if(vret == -1 || vret == 0){
        arvb_registro_apagar(&arvb_registro);
        return vret;
    }

    if(arvb_registro_get_nroChaves(arvb_registro) < 2){
        arvb_registro_inserirChave(arvb_registro, (*promoC), (*promoPr), (*promoRRN));
        fseek(bin_arvb, (RRN + 1)*TAM_NO, SEEK_SET);
        arvb_registro_escrever(bin_arvb, arvb_registro);
        arvb_registro_apagar(&arvb_registro);
        return 0;
    }
    else{
        
        split(bin_arvb, arvb_cabecalho, RRN, (*promoC), (*promoPr), (*promoRRN), arvb_registro, promoC, promoPr, promoRRN);
        arvb_registro_apagar(&arvb_registro);
        return 1;
    }

}



bool arvb_inserir(FILE *bin_arvb, ArvB_Cabecalho *arvb_cabecalho, int C, long int Pr){
    int RRN_Raiz = arvb_cabecalho_get_noRaiz(arvb_cabecalho);
    int promoC, promoRRN; 
    long int promoPr; 
    
    int vret = inserir(bin_arvb, arvb_cabecalho, RRN_Raiz, C, Pr, &promoRRN, &promoC, &promoPr);
    if(vret == -1) return false;
    else if(vret == 1){
        ArvB_Registro *nova_raiz = arvb_registro_criar(0, 1, RRN_Raiz, promoC, promoPr, promoRRN, -1, -1, -1);
        int novoRRN = arvb_cabecalho_get_proxRRN(arvb_cabecalho);
        arvb_cabecalho_set_nroNos(arvb_cabecalho, arvb_cabecalho_get_nroNos(arvb_cabecalho)+1);
        arvb_cabecalho_set_proxRRN(arvb_cabecalho, novoRRN+1);
        arvb_cabecalho_set_noRaiz(arvb_cabecalho, novoRRN);
        fseek(bin_arvb, (novoRRN+1)*TAM_NO, SEEK_SET);
        arvb_registro_escrever(bin_arvb, nova_raiz);
        arvb_registro_apagar(&nova_raiz);
    }
    
    return true;
}



bool arvb_dfs_busca(FILE *bin_arvb, FILE *bin_dados, Cabecalho *cabecalho, int RRN, int cmp_year, float cmp_financialLoss, char cmp_country[], char cmp_attackType[], char cmp_targetIndustry[], char cmp_defenseMechanism[]){
    if (RRN == -1) {
        return false;
    }

    
    fseek(bin_arvb, (RRN + 1) * TAM_NO, SEEK_SET);

    
    ArvB_Registro *no_atual = arvb_registro_ler(bin_arvb);
    if (no_atual == NULL) {
        return false; 
    }

    int nroChaves = arvb_registro_get_nroChaves(no_atual);
    if(nroChaves == 0) return false;
    
    bool findAtual = false;
    bool find1 = false;
    bool find2 = false;
    bool find3 = false;
    
    find1 = arvb_dfs_busca(bin_arvb, bin_dados, cabecalho, arvb_registro_get_P1(no_atual), cmp_year, cmp_financialLoss, cmp_country, cmp_attackType, cmp_targetIndustry, cmp_defenseMechanism);
    
    long int Pr1 = arvb_registro_get_Pr1(no_atual);
    
    fseek(bin_dados, Pr1, SEEK_SET);
    Registro *R1 = registro_ler_bin(bin_dados);
    if(registro_comparar(R1, -1, cmp_year, cmp_financialLoss, cmp_country, cmp_attackType, cmp_targetIndustry, cmp_defenseMechanism)){
        registro_imprimir(R1, cabecalho);
        
        findAtual = true;
    }
    registro_apagar(&R1);

    find2 = arvb_dfs_busca(bin_arvb, bin_dados, cabecalho, arvb_registro_get_P2(no_atual), cmp_year, cmp_financialLoss, cmp_country, cmp_attackType, cmp_targetIndustry, cmp_defenseMechanism); 
   

    
    if (nroChaves == 2) {
        long int Pr2 = arvb_registro_get_Pr2(no_atual);
        fseek(bin_dados, Pr2, SEEK_SET);
        Registro *R2 = registro_ler_bin(bin_dados);
        if(registro_comparar(R2, -1, cmp_year, cmp_financialLoss, cmp_country, cmp_attackType, cmp_targetIndustry, cmp_defenseMechanism)){
            registro_imprimir(R2, cabecalho);
            
            findAtual = true;
        }
        registro_apagar(&R2);
        find3 = arvb_dfs_busca(bin_arvb, bin_dados, cabecalho, arvb_registro_get_P3(no_atual), cmp_year, cmp_financialLoss, cmp_country, cmp_attackType, cmp_targetIndustry, cmp_defenseMechanism); 
    }

    
    arvb_registro_apagar(&no_atual);

    return (findAtual || find1 || find2 || find3);
}

bool arvb_update(FILE *bin_arvb, ArvB_Cabecalho *arvb_cabecalho, int C, long int Pr){
    int noAchado;
    int posAchado;
    if(busca(bin_arvb, arvb_cabecalho_get_noRaiz(arvb_cabecalho), C, &noAchado, &posAchado) != -1){
        fseek(bin_arvb, (noAchado+1)*TAM_NO, SEEK_SET);
        ArvB_Registro *arvb_registro = arvb_registro_ler(bin_arvb);
        if(posAchado == 1){
            arvb_registro_set_Pr1(arvb_registro, Pr);
        }
        else{
            arvb_registro_set_Pr2(arvb_registro, Pr);
        }
        fseek(bin_arvb, (noAchado + 1 )*TAM_NO, SEEK_SET);
        arvb_registro_escrever(bin_arvb, arvb_registro);
        arvb_registro_apagar(&arvb_registro);
        
        return true;
    }
    return false;

}

bool arvb_dfs_update(FILE *bin_arvb, FILE *bin_dados, Cabecalho *cabecalho, ArvB_Cabecalho *arvb_cabecalho, int RRN, int cmp_year, float cmp_financialLoss, char cmp_country[], char cmp_attackType[], char cmp_targetIndustry[], char cmp_defenseMechanism[], bool campos[], int year, float financialLoss, char country[], char attackType[], char targetIndustry[], char defenseMechanism[]){
    if (RRN == -1) {
        return false;
    }

    
    fseek(bin_arvb, (RRN + 1) * TAM_NO, SEEK_SET);

    
    ArvB_Registro *no_atual = arvb_registro_ler(bin_arvb);
    if (no_atual == NULL) {
        return false; 
    }

    int nroChaves = arvb_registro_get_nroChaves(no_atual);
    if(nroChaves == 0) return false;
    
    bool findAtual = false;
    bool find1 = false;
    bool find2 = false;
    bool find3 = false;
    
    find1 = arvb_dfs_update(bin_arvb, bin_dados, cabecalho, arvb_cabecalho, arvb_registro_get_P1(no_atual), cmp_year, cmp_financialLoss, cmp_country, cmp_attackType, cmp_targetIndustry, cmp_defenseMechanism, campos, year, financialLoss, country, attackType, targetIndustry, defenseMechanism);
    
    long int Pr1 = arvb_registro_get_Pr1(no_atual);
    
    fseek(bin_dados, Pr1, SEEK_SET);
    Registro *R1 = registro_ler_bin(bin_dados);
    if(registro_comparar(R1, -1, cmp_year, cmp_financialLoss, cmp_country, cmp_attackType, cmp_targetIndustry, cmp_defenseMechanism)){
        




        if(!campos[1]) year = registro_get_year(R1);
        if(!campos[2]) financialLoss = registro_get_financialLoss(R1);
        if(!campos[3]) strcpy(country, registro_get_country(R1));
        if(!campos[4]) strcpy(attackType, registro_get_attackType(R1));
        if(!campos[5]) strcpy(targetIndustry, registro_get_targetIndustry(R1));
        if(!campos[6]) strcpy(defenseMechanism, registro_get_defenseMechanism(R1));
        
        char *cpy_country = (char *)malloc(sizeof(char)*50);
    
        strcpy(cpy_country, country);

        char *cpy_attackType = (char *)malloc(sizeof(char)*50);
        strcpy(cpy_attackType, attackType);

        char *cpy_targetIndustry = (char *)malloc(sizeof(char)*50);
        strcpy(cpy_targetIndustry, targetIndustry);

        char *cpy_defenseMechanism = (char *)malloc(sizeof(char)*50);
        strcpy(cpy_defenseMechanism, defenseMechanism);

        Registro *novo = registro_criar('0', -1, registro_get_idAttack(R1), year, financialLoss, cpy_country, cpy_attackType, cpy_targetIndustry, cpy_defenseMechanism);
        
        if(registro_get_tamanhoRegistro(novo) <= registro_get_tamanhoRegistro(R1)){
            
            registro_set_tamanhoRegistro(novo, registro_get_tamanhoRegistro(R1));
            fseek(bin_dados, Pr1, SEEK_SET);
            registro_escrever(bin_dados, novo);
        }
        else{
            registro_remover(bin_dados, R1, cabecalho);
            long int byteOffset = registro_inserir(bin_dados, novo, cabecalho);
            arvb_update(bin_arvb, arvb_cabecalho, registro_get_idAttack(novo), byteOffset);
        }
        registro_apagar(&novo);  
        
        findAtual = true;
    }
    if(R1) registro_apagar(&R1);

    find2 = arvb_dfs_update(bin_arvb, bin_dados, cabecalho, arvb_cabecalho, arvb_registro_get_P2(no_atual), cmp_year, cmp_financialLoss, cmp_country, cmp_attackType, cmp_targetIndustry, cmp_defenseMechanism, campos, year, financialLoss, country, attackType, targetIndustry, defenseMechanism); 
   

    
    if (nroChaves == 2) {
        long int Pr2 = arvb_registro_get_Pr2(no_atual);
        fseek(bin_dados, Pr2, SEEK_SET);
        Registro *R2 = registro_ler_bin(bin_dados);
        if(registro_comparar(R2, -1, cmp_year, cmp_financialLoss, cmp_country, cmp_attackType, cmp_targetIndustry, cmp_defenseMechanism)){
           
            if(!campos[1]) year = registro_get_year(R2);
            if(!campos[2]) financialLoss = registro_get_financialLoss(R2);
            if(!campos[3]) strcpy(country, registro_get_country(R2));
            if(!campos[4]) strcpy(attackType, registro_get_attackType(R2));
            if(!campos[5]) strcpy(targetIndustry, registro_get_targetIndustry(R2));
            if(!campos[6]) strcpy(defenseMechanism, registro_get_defenseMechanism(R2));
            
            char *cpy_country = (char *)malloc(sizeof(char)*50);
            strcpy(cpy_country, country);

            char *cpy_attackType = (char *)malloc(sizeof(char)*50);
            strcpy(cpy_attackType, attackType);

            char *cpy_targetIndustry = (char *)malloc(sizeof(char)*50);
            strcpy(cpy_targetIndustry, targetIndustry);

            char *cpy_defenseMechanism = (char *)malloc(sizeof(char)*50);
            strcpy(cpy_defenseMechanism, defenseMechanism);

            Registro *novo = registro_criar('0', -1, registro_get_idAttack(R2), year, financialLoss, cpy_country, cpy_attackType, cpy_targetIndustry, cpy_defenseMechanism);
            
            if(registro_get_tamanhoRegistro(novo) <= registro_get_tamanhoRegistro(R2)){
                
                registro_set_tamanhoRegistro(novo, registro_get_tamanhoRegistro(R2));
                fseek(bin_dados, Pr2, SEEK_SET);
                registro_escrever(bin_dados, novo);
            }
            else{
                registro_remover(bin_dados, R2, cabecalho);
                long int byteOffset = registro_inserir(bin_dados, novo, cabecalho);
                arvb_update(bin_arvb, arvb_cabecalho, registro_get_idAttack(novo), byteOffset);
            }
            registro_apagar(&novo);  
            
            findAtual = true;
        }
        if(R2) registro_apagar(&R2);
        find3 = arvb_dfs_update(bin_arvb, bin_dados, cabecalho, arvb_cabecalho, arvb_registro_get_P3(no_atual), cmp_year, cmp_financialLoss, cmp_country, cmp_attackType, cmp_targetIndustry, cmp_defenseMechanism, campos, year, financialLoss, country, attackType, targetIndustry, defenseMechanism); 
    }

    
    arvb_registro_apagar(&no_atual);

    return (findAtual || find1 || find2 || find3);
}
// Artur Domitti Camargo - 15441661
// Lucas Mello Ciosaki - 14591305

#include "funcionalidades.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

void binarioNaTela(char *nomeArquivoBinario) { /* Você não precisa entender o código dessa função. */

	/* Use essa função para comparação no run.codes. Lembre-se de ter fechado (fclose) o arquivo anteriormente.
	*  Ela vai abrir de novo para leitura e depois fechar (você não vai perder pontos por isso se usar ela). */

	unsigned long i, cs;
	unsigned char *mb;
	size_t fl;
	FILE *fs;
	if(nomeArquivoBinario == NULL || !(fs = fopen(nomeArquivoBinario, "rb"))) {
		fprintf(stderr, "ERRO AO ESCREVER O BINARIO NA TELA (função binarioNaTela): não foi possível abrir o arquivo que me passou para leitura. Ele existe e você tá passando o nome certo? Você lembrou de fechar ele com fclose depois de usar?\n");
		return;
	}
	fseek(fs, 0, SEEK_END);
	fl = ftell(fs);
	fseek(fs, 0, SEEK_SET);
	mb = (unsigned char *) malloc(fl);
	fread(mb, 1, fl, fs);

	cs = 0;
	for(i = 0; i < fl; i++) {
		cs += (unsigned long) mb[i];
	}
	printf("%lf\n", (cs / (double) 100));
	free(mb);
	fclose(fs);
}

void scan_quote_string(char *str) {

	/*
	*	Use essa função para ler um campo string delimitado entre aspas (").
	*	Chame ela na hora que for ler tal campo. Por exemplo:
	*
	*	A entrada está da seguinte forma:
	*		nomeDoCampo "MARIA DA SILVA"
	*
	*	Para ler isso para as strings já alocadas str1 e str2 do seu programa, você faz:
	*		scanf("%s", str1); // Vai salvar nomeDoCampo em str1
	*		scan_quote_string(str2); // Vai salvar MARIA DA SILVA em str2 (sem as aspas)
	*
	*/

	char R;

	while((R = getchar()) != EOF && isspace(R)); // ignorar espaços, \r, \n...

	if(R == 'N' || R == 'n') { // campo NULO
		getchar(); getchar(); getchar(); // ignorar o "ULO" de NULO.
		strcpy(str, ""); // copia string vazia
	} else if(R == '\"') {
		if(scanf("%[^\"]", str) != 1) { // ler até o fechamento das aspas
			strcpy(str, "");
		}
		getchar(); // ignorar aspas fechando
	} else if(R != EOF){ // vc tá tentando ler uma string que não tá entre aspas! Fazer leitura normal %s então, pois deve ser algum inteiro ou algo assim...
		str[0] = R;
		scanf("%s", &str[1]);
	} else { // EOF
		strcpy(str, "");
	}
}

void funcionalidade1(char nomeCSV[], char nomeBin[]) {
    // Abre o arquivo csv para leitura e o arquivo binário para escrita
    FILE *csv = fopen(nomeCSV, "r");
    FILE *bin = fopen(nomeBin, "wb");

    // Verifica se os arquivos foram abertos corretamente
    if(!csv || !bin) {
        printf("Falha no processamento do arquivo.\n");
        if(csv) fclose(csv);
        if(bin) fclose(bin);
        return;
    }

    // Cria e escreve o cabeçalho do arquivo binário (status = '0')
    Cabecalho *cabecalho = cabecalho_criar();
    cabecalho_escrever(bin, cabecalho);
    
    // Pula a primeira linha (cabeçalho) do arquivo csv
    fseek(csv, TAM_CABECALHO_CSV, SEEK_SET);

    // Contador de registros
    int nroRegArq = 0;

    // Buffer para ler as linhas do arquivo csv (O tamanho foi escolhido arbitrariamente, mas deve ser suficiente para a maioria dos casos)
    char linha[1024];
    int pos = 0;
    char c;

    // Enquanto houver linhas no arquivo csv, lê e escreve os registros no arquivo binário
    while(fread(&c, sizeof(char), 1, csv) == 1) {
        if (c == '\n') {
            linha[pos] = '\0';
        

            if (pos > 0 && linha[pos - 1] == '\r') {
                linha[pos] = '\0';
            }

            Registro *registro;
            // Lê o registro do arquivo csv e cria um novo registro
            registro = registro_ler_csv(csv, linha);
            nroRegArq++;
            // Escreve no arquivo binário
            registro_escrever(bin, registro);
            // Libera memória
            registro_apagar(&registro);

            pos = 0;
        } else {
            linha[pos] = c;
            pos++;
        }
    }

    if (pos > 0) {
        linha[pos] = '\0';
        Registro *registro = registro_ler_csv(csv, linha);
        nroRegArq++;
        registro_escrever(bin, registro);
        registro_apagar(&registro);
    }

    long int proxByteOffset = ftell(bin); // Atualiza o proxByteOffset disponível
    char status = '1'; // Atualiza o status para consistente

    // Atualiza o cabeçalho com os novos valores
    cabecalho_set_nroRegArq(cabecalho, nroRegArq);
    cabecalho_set_proxByteOffset(cabecalho, proxByteOffset);
    cabecalho_set_status(cabecalho, status);
    cabecalho_escrever(bin, cabecalho);
    cabecalho_apagar(&cabecalho);

    // Fecha os arquivos
    fclose(csv);
    fclose(bin);

    binarioNaTela(nomeBin);
}

void funcionalidade2(char nomeBin[]) {
    // Abre o arquivo binário para leitura
    FILE *bin = fopen(nomeBin, "rb");

    // Verifica se o arquivo foi aberto corretamente
    if(!bin) {
        printf("Falha no processamento do arquivo.\n");
        return;
    }
    
    // Calcula o tamanho do arquivo
    fseek(bin, 0, SEEK_END);
    long int tamanhoArquivo = ftell(bin);
    
    Cabecalho *cabecalho;
    cabecalho = cabecalho_ler_bin(bin); // Essa função ajusta o ponteiro para o início do arquivo binário e lê o cabeçalho
    
    // Verifica se o arquivo binário é consistente, senão fecha o arquivo e retorna
    if(!cabecalho_estavel(cabecalho)) {
        printf("Falha no processamento do arquivo.\n");
        fclose(bin);
        return;
    }
    
    // Verifica se o arquivo contém registros válidos, senão fecha o arquivo e retorna
    if(cabecalho_get_nroRegArq(cabecalho) == 0 || cabecalho_get_nroRegArq(cabecalho) - cabecalho_get_nroRegRem(cabecalho) == 0) {
        printf("Registro inexistente.\n");
        fclose(bin);
        return;
    }

    // Enquanto o ponteiro não atingir o final do arquivo, lê e imprime os registros
    while(ftell(bin) < tamanhoArquivo) {
        Registro *registro; 
        
        registro = registro_ler_bin(bin);
        if(registro == NULL) continue;
        
        // Imprime os dados do registro
        registro_imprimir(registro, cabecalho);

        // Libera a memória alocada
        registro_apagar(&registro);
    }

    // Libera a memória e fecha o arquivo
    cabecalho_apagar(&cabecalho);
    fclose(bin);
}

void funcionalidade3(char nomeBin[], int n){
    // Abre o arquivo binário para leitura
    FILE *bin = fopen(nomeBin, "rb");

    // Verifica se o arquivo foi aberto corretamente
    if(!bin) {
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    // Verifica se o arquivo binário é consistente, senão fecha o arquivo e retorna
    Cabecalho *cabecalho = cabecalho_ler_bin(bin);
    if(!cabecalho_estavel(cabecalho)){
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    // Verifica se o arquivo contém registros válidos, senão fecha o arquivo e retorna
    if(cabecalho_get_nroRegArq(cabecalho) == 0 || cabecalho_get_nroRegArq(cabecalho) - cabecalho_get_nroRegRem(cabecalho) == 0) {
        printf("Registro inexistente.\n");
        fclose(bin);
        return;
    }

    // Calcula o tamanho do arquivo
    fseek(bin, 0, SEEK_END);
    long int tamanhoArquivo = ftell(bin);

    // Executa o processo de busca n vezes
    for(int buscaAtual = 0; buscaAtual < n; buscaAtual++){
        // Inicializa variáveis de comparação com valores padrão
        int cmp_idAttack = -1;
        int cmp_year = -1;
        float cmp_financialLoss = -1;
        char cmp_country[50] = "";
        char cmp_attackType[50] = "";
        char cmp_targetIndustry[50] = "";
        char cmp_defenseMechanism[50] = "";
        
        int registrosEncontrados = 0;
        
        //Lê a quantidade de campos a serem comparados
        int m;
        scanf("%d", &m);

        //Loop para receber os campos e valores de comparação
        for(int parCampoValor = 0; parCampoValor < m; parCampoValor++){
            
            char campo[30];
            scanf("%s ", campo);
            if(strcmp(campo, "idAttack") == 0){
                scanf("%d", &cmp_idAttack);
            }
            if(strcmp(campo, "year") == 0){
                scanf("%d", &cmp_year);
            }
            if(strcmp(campo, "financialLoss") == 0){
                scanf("%f", &cmp_financialLoss);
            }
            if(strcmp(campo, "country") == 0){
                scan_quote_string(cmp_country);
            
            }
            if(strcmp(campo, "attackType") == 0){
                scan_quote_string(cmp_attackType);
            }
            if(strcmp(campo, "targetIndustry") == 0){
                scan_quote_string(cmp_targetIndustry);
            }
            if(strcmp(campo, "defenseMechanism") == 0){
                scan_quote_string(cmp_defenseMechanism);
            }

        }
        
        // Posiciona o ponteiro após o cabeçalho para começar a leitura dos registros
        fseek(bin, TAM_CABECALHO_BIN, SEEK_SET);

        // Percorre o arquivo binário sequencialmente
        while(ftell(bin) < tamanhoArquivo){
            Registro *registro = registro_ler_bin(bin);
            if(registro == NULL) continue;

            // Compara o registro com os filtros de busca
            if(registro_comparar(registro, cmp_idAttack, cmp_year, cmp_financialLoss, cmp_country, cmp_attackType, cmp_targetIndustry, cmp_defenseMechanism)){
                registro_imprimir(registro, cabecalho);
                registrosEncontrados++;
            }
            // Libera a memória alocada
            registro_apagar(&registro);
        }
        // Se não houver registros encontrados, imprime mensagem de erro
        if(registrosEncontrados == 0) printf("Registro inexistente.\n\n");
        printf("**********\n");
    }
    // Libera a memória e fecha o arquivo
    cabecalho_apagar(&cabecalho);
    fclose(bin);
}

void funcionalidade4(char nomeBin[], int n){
   // Abre o arquivo binário para leitura
   
    FILE *bin = fopen(nomeBin, "rb+");

    // Verifica se o arquivo foi aberto corretamente
    if(!bin) {
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    // Verifica se o arquivo binário é consistente, senão fecha o arquivo e retorna
    Cabecalho *cabecalho = cabecalho_ler_bin(bin);
    if(!cabecalho_estavel(cabecalho)){
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    // Verifica se o arquivo contém registros válidos, senão fecha o arquivo e retorna
    if(cabecalho_get_nroRegArq(cabecalho) == 0 || cabecalho_get_nroRegArq(cabecalho) - cabecalho_get_nroRegRem(cabecalho) == 0) {
        printf("Registro inexistente.\n");
        fclose(bin);
        return;
    }

    // Calcula o tamanho do arquivo
    fseek(bin, 0, SEEK_END);
    long int tamanhoArquivo = ftell(bin);

    // Executa o processo de remocao n vezes
    for(int remocaoAtual = 0; remocaoAtual < n; remocaoAtual++){
        
        // Inicializa variáveis de comparação com valores padrão
        int cmp_idAttack = -1;
        int cmp_year = -1;
        float cmp_financialLoss = -1;
        char cmp_country[50] = "";
        char cmp_attackType[50] = "";
        char cmp_targetIndustry[50] = "";
        char cmp_defenseMechanism[50] = "";
        
        //Lê a quantidade de campos a serem comparados
        int m;
        scanf("%d", &m);

        //Loop para receber os campos e valores de comparação
        for(int parCampoValor = 0; parCampoValor < m; parCampoValor++){
            

            char campo[30];
            scanf("%s ", campo);
            if(strcmp(campo, "idAttack") == 0){
                scanf("%d", &cmp_idAttack);
            }
            if(strcmp(campo, "year") == 0){
                scanf("%d", &cmp_year);
            }
            if(strcmp(campo, "financialLoss") == 0){
                scanf("%f", &cmp_financialLoss);
            }
            if(strcmp(campo, "country") == 0){
                scan_quote_string(cmp_country);
            
            }
            if(strcmp(campo, "attackType") == 0){
                scan_quote_string(cmp_attackType);
            }
            if(strcmp(campo, "targetIndustry") == 0){
                scan_quote_string(cmp_targetIndustry);
            }
            if(strcmp(campo, "defenseMechanism") == 0){
                scan_quote_string(cmp_defenseMechanism);
            }

        }
        
        // Posiciona o ponteiro após o cabeçalho para começar a leitura dos registros
        fseek(bin, TAM_CABECALHO_BIN, SEEK_SET);

        // Percorre o arquivo binário sequencialmente
        while(ftell(bin) < tamanhoArquivo){
            
            Registro *registro = registro_ler_bin(bin);
            if(registro == NULL || registro_removido(registro)){
                registro_apagar(&registro);
                continue;
            }
            // Compara o registro com os filtros de busca
            if(registro_comparar(registro, cmp_idAttack, cmp_year, cmp_financialLoss, cmp_country, cmp_attackType, cmp_targetIndustry, cmp_defenseMechanism)){
                registro_remover(bin, registro, cabecalho);
            }
            // Libera a memória alocada
            registro_apagar(&registro);
        }
    }
    // Libera a memória e fecha o arquivo
    cabecalho_apagar(&cabecalho);
    fclose(bin);

    binarioNaTela(nomeBin);
}

void funcionalidade5(char nomeBin[], int n){
    // Abre o arquivo binário para leitura e escrita
    FILE *bin = fopen(nomeBin, "rb+");

    // Verifica se o arquivo foi aberto corretamente
    if(!bin) {
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    // Verifica se o arquivo binário é consistente, senão fecha o arquivo e retorna
    Cabecalho *cabecalho = cabecalho_ler_bin(bin);
    if(!cabecalho_estavel(cabecalho)){
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    // Executa o processo de inserir n vezes
    for(int insercaoAtual = 0; insercaoAtual < n; insercaoAtual++){
        int idAttack, year;
        float financialLoss;
        char *str_country = (char *)malloc(sizeof(char)*50);
        char *str_attackType = (char *)malloc(sizeof(char)*50);
        char *str_targetIndustry = (char *)malloc(sizeof(char)*50);
        char *str_defenseMechanism = (char *)malloc(sizeof(char)*50);
        
        scanf("%d %d %f ", &idAttack, &year, &financialLoss);
        scan_quote_string(str_country);
        scan_quote_string(str_attackType);
        scan_quote_string(str_targetIndustry);
        scan_quote_string(str_defenseMechanism);

        Registro *novo = registro_criar('0', -1, idAttack, year, financialLoss, str_country, str_attackType, str_targetIndustry, str_defenseMechanism);
        registro_inserir(bin, novo, cabecalho);
        registro_apagar(&novo);

    }
    // Libera a memória e fecha o arquivo
    cabecalho_escrever(bin, cabecalho);
    cabecalho_apagar(&cabecalho);
    fclose(bin);

    binarioNaTela(nomeBin);
}

void funcionalidade6(char nomeBin[], int n){
   // Abre o arquivo binário para leitura
   
    FILE *bin = fopen(nomeBin, "rb+");

    // Verifica se o arquivo foi aberto corretamente
    if(!bin) {
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    // Verifica se o arquivo binário é consistente, senão fecha o arquivo e retorna
    Cabecalho *cabecalho = cabecalho_ler_bin(bin);
    if(!cabecalho_estavel(cabecalho)){
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    // Verifica se o arquivo contém registros válidos, senão fecha o arquivo e retorna
    if(cabecalho_get_nroRegArq(cabecalho) == 0 || cabecalho_get_nroRegArq(cabecalho) - cabecalho_get_nroRegRem(cabecalho) == 0) {
        printf("Registro inexistente.\n");
        fclose(bin);
        return;
    }

    // Calcula o tamanho do arquivo
    fseek(bin, 0, SEEK_END);
    long int tamanhoArquivo = ftell(bin);

    // Executa o processo de atualizacao n vezes
    for(int atualizacaoAtual = 0; atualizacaoAtual < n; atualizacaoAtual++){
        
        // Inicializa variáveis de comparação com valores padrão
        int cmp_idAttack = -1;
        int cmp_year = -1;
        float cmp_financialLoss = -1;
        char cmp_country[50] = "";
        char cmp_attackType[50] = "";
        char cmp_targetIndustry[50] = "";
        char cmp_defenseMechanism[50] = "";
        
        //Lê a quantidade de campos a serem comparados
        int m;
        scanf("%d", &m);

        //Loop para receber os campos e valores de comparação
        for(int parCampoValor = 0; parCampoValor < m; parCampoValor++){
            

            char campo[30];
            scanf("%s ", campo);
            if(strcmp(campo, "idAttack") == 0){
                scanf("%d", &cmp_idAttack);
            }
            if(strcmp(campo, "year") == 0){
                scanf("%d", &cmp_year);
            }
            if(strcmp(campo, "financialLoss") == 0){
                scanf("%f", &cmp_financialLoss);
            }
            if(strcmp(campo, "country") == 0){
                scan_quote_string(cmp_country);
            
            }
            if(strcmp(campo, "attackType") == 0){
                scan_quote_string(cmp_attackType);
            }
            if(strcmp(campo, "targetIndustry") == 0){
                scan_quote_string(cmp_targetIndustry);
            }
            if(strcmp(campo, "defenseMechanism") == 0){
                scan_quote_string(cmp_defenseMechanism);
            }

        }

        int idAttack = -1;
        int year = -1;
        float financialLoss = -1;
        char *country = (char *) malloc(sizeof(char)*50);
        char *attackType = (char *) malloc(sizeof(char)*50);
        char *targetIndustry = (char *) malloc(sizeof(char)*50);
        char *defenseMechanism = (char *) malloc(sizeof(char)*50);

        bool campos[7] = {false, false, false, false, false, false, false};

        int p;
        scanf("%d", &p);

        for(int parCampoValor = 0; parCampoValor < p; parCampoValor++){
            

            char campo[30];
            scanf("%s ", campo);
            if(strcmp(campo, "idAttack") == 0){
                scanf("%d", &idAttack);
                campos[0] = true;
            }
            if(strcmp(campo, "year") == 0){
                scanf("%d", &year);
                campos[1] = true;
            }
            if(strcmp(campo, "financialLoss") == 0){
                scanf("%f", &financialLoss);
                campos[2] = true;
            }
            if(strcmp(campo, "country") == 0){
                scan_quote_string(country);
                campos[3] = true;
            
            }
            if(strcmp(campo, "attackType") == 0){
                scan_quote_string(attackType);
                campos[4] = true;
            }
            if(strcmp(campo, "targetIndustry") == 0){
                scan_quote_string(targetIndustry);
                campos[5] = true;
            }
            if(strcmp(campo, "defenseMechanism") == 0){
                scan_quote_string(defenseMechanism);
                campos[6] = true;
            }

        }


        
        
        // Posiciona o ponteiro após o cabeçalho para começar a leitura dos registros
        fseek(bin, TAM_CABECALHO_BIN, SEEK_SET);

        // Percorre o arquivo binário sequencialmente
        while(ftell(bin) < tamanhoArquivo){
            
            Registro *registro = registro_ler_bin(bin);

            if(registro == NULL || registro_removido(registro)){
                registro_apagar(&registro);
                continue;
            }
            // Compara o registro com os filtros de busca
            if(registro_comparar(registro, cmp_idAttack, cmp_year, cmp_financialLoss, cmp_country, cmp_attackType, cmp_targetIndustry, cmp_defenseMechanism)){
                
                if(!campos[0]) idAttack = registro_get_idAttack(registro);
                if(!campos[1]) year = registro_get_year(registro);
                if(!campos[2]) financialLoss = registro_get_financialLoss(registro);
                if(!campos[3]) strcpy(country, registro_get_country(registro));
                if(!campos[4]) strcpy(attackType, registro_get_attackType(registro));
                if(!campos[5]) strcpy(targetIndustry, registro_get_targetIndustry(registro));
                if(!campos[6]) strcpy(defenseMechanism, registro_get_defenseMechanism(registro));
                

                Registro *novo = registro_criar('0', -1, idAttack, year, financialLoss, country, attackType, targetIndustry, defenseMechanism);
                
                if(registro_get_tamanhoRegistro(novo) <= registro_get_tamanhoRegistro(registro)){
                    
                    registro_set_tamanhoRegistro(novo, registro_get_tamanhoRegistro(registro));
                    long int byteOffset = ftell(bin) - (5 + registro_get_tamanhoRegistro(registro));
                    fseek(bin, byteOffset, SEEK_SET);
                    registro_escrever(bin, novo);
                }
                else{
                    registro_remover(bin, registro, cabecalho);
                    registro_inserir(bin, novo, cabecalho);
                }
                registro_apagar(&novo);

            }
            // Libera a memória alocada
            registro_apagar(&registro);
        }
    }
    // Libera a memória e fecha o arquivo
    cabecalho_escrever(bin, cabecalho);
    cabecalho_apagar(&cabecalho);
    fclose(bin);

    binarioNaTela(nomeBin);
}

void funcionalidade7(char nomeBinDados[], char nomeBinArvB[]){
    FILE *bin_dados = fopen(nomeBinDados, "rb");
    FILE *bin_arvb = fopen(nomeBinArvB, "wb+");

    if(!bin_dados || !bin_arvb) {
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    // Verifica se o arquivo binário é consistente, senão fecha o arquivo e retorna
    Cabecalho *cabecalho = cabecalho_ler_bin(bin_dados);
    if(!cabecalho_estavel(cabecalho)){
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    // Verifica se o arquivo contém registros válidos, senão fecha o arquivo e retorna
    if(cabecalho_get_nroRegArq(cabecalho) == 0 || cabecalho_get_nroRegArq(cabecalho) - cabecalho_get_nroRegRem(cabecalho) == 0) {
        printf("Registro inexistente.\n");
        fclose(bin_arvb);
        fclose(bin_dados);
        return;
    }

    ArvB_Cabecalho *arvb_cabecalho = arvb_cabecalho_criar();   
    arvb_cabecalho_escrever(bin_arvb, arvb_cabecalho);
    
    fseek(bin_dados, 0, SEEK_END);
    int tamBinDados = ftell(bin_dados);
    
    fseek(bin_dados, TAM_CABECALHO_BIN, SEEK_SET);
    while(ftell(bin_dados) < tamBinDados){
        long int byteOffset = ftell(bin_dados);
        Registro *registro = registro_ler_bin(bin_dados);
        if(!registro_removido(registro)){
            arvb_inserir(bin_arvb, arvb_cabecalho, registro_get_idAttack(registro), byteOffset);
        }
        registro_apagar(&registro);
    }
    arvb_cabecalho_set_status(arvb_cabecalho, '1');
    arvb_cabecalho_escrever(bin_arvb, arvb_cabecalho);

    arvb_cabecalho_apagar(&arvb_cabecalho);
    cabecalho_apagar(&cabecalho);
    

    fclose(bin_arvb);
    fclose(bin_dados);

    binarioNaTela(nomeBinArvB);

    return;
}

void funcionalidade8(char nomeBinDados[], char nomeBinArvB[], int n) {
    FILE *bin_dados = fopen(nomeBinDados, "rb");
    FILE *bin_arvb = fopen(nomeBinArvB, "rb");

    // Verifica se o arquivo foi aberto corretamente
    if(!bin_dados || !bin_arvb) {
        printf("Falha no processamento do arquivo.\n");
        if(bin_dados) fclose(bin_dados);
        if(bin_arvb) fclose(bin_arvb);
        return;
    }

    // Verifica se o arquivo binário é consistente, senão fecha o arquivo e retorna
    Cabecalho *cabecalho = cabecalho_ler_bin(bin_dados);
    if(!cabecalho_estavel(cabecalho)){
        printf("Falha no processamento do arquivo.\n");
        fclose(bin_dados);
        fclose(bin_arvb);

        return;
    }

    ArvB_Cabecalho *arvb_cabecalho = arvb_cabecalho_ler(bin_arvb); // Nome da variável corrigido
    if(!arvb_cabecalho) {
        printf("Falha no carregamento do índice.\n");
        fclose(bin_dados);
        fclose(bin_arvb);
        cabecalho_apagar(&cabecalho);
        
        return;
    }

    // Verifica se o arquivo contém registros válidos, senão fecha o arquivo e retorna
    if(cabecalho_get_nroRegArq(cabecalho) == 0 || cabecalho_get_nroRegArq(cabecalho) - cabecalho_get_nroRegRem(cabecalho) == 0) {
        printf("Registro inexistente.\n");
        fclose(bin_dados);
        fclose(bin_arvb);
        cabecalho_apagar(&cabecalho);
        arvb_cabecalho_apagar(&arvb_cabecalho);
        return;
    }

    for(int buscaAtual = 0; buscaAtual < n; buscaAtual++) {
        bool encontrou = false;

        int idAttack = -1;
        int year = -1;
        float financialLoss = -1.0;
        char country[50] = "";
        char attackType[50] = "";
        char targetIndustry[50] = "";
        char defenseMechanism[50] = "";

        int usarIndice = 0;
        

        int m;
        scanf("%d", &m);

        for(int parCampoValor = 0; parCampoValor < m; parCampoValor++) {
            char campo[30];
            scanf("%s", campo);
            
            if(strcmp(campo, "idAttack") == 0) {
                scanf("%d", &idAttack);
                usarIndice = 1;
            } 
            else if(strcmp(campo, "year") == 0) {
                scanf("%d", &year);
                
            }
            else if(strcmp(campo, "financialLoss") == 0) {
                scanf("%f", &financialLoss);
                
            }
            else if(strcmp(campo, "country") == 0) {
                scan_quote_string(country);
                
            }
            else if(strcmp(campo, "attackType") == 0) {
                scan_quote_string(attackType);
                
            }
            else if(strcmp(campo, "targetIndustry") == 0) {
                scan_quote_string(targetIndustry);
                
            }
            else if(strcmp(campo, "defenseMechanism") == 0) {
                scan_quote_string(defenseMechanism);
                
            }
        }
        if(usarIndice == 1) {
            long byteOffset = arvb_buscar(bin_arvb, arvb_cabecalho, idAttack);
            if(byteOffset != -1) {

                fseek(bin_dados, byteOffset, SEEK_SET);
                Registro *registro = registro_ler_bin(bin_dados);
                
                if(registro != NULL && !registro_removido(registro)) {

                    
                    if(registro_comparar(registro, -1, year, financialLoss, country, attackType, targetIndustry, defenseMechanism)) {
                        registro_imprimir(registro, cabecalho);
                        
                        encontrou = true;
                    }
                }
                if(registro != NULL) registro_apagar(&registro);
            }
        }
        
        else {
            encontrou = arvb_dfs_busca(bin_arvb, bin_dados, cabecalho, arvb_cabecalho_get_noRaiz(arvb_cabecalho), year, financialLoss, country, attackType, targetIndustry, defenseMechanism);
        }
        if(!encontrou) {
            printf("Registro inexistente.\n\n");
        }
        printf("**********\n");
    }
    
}

void funcionalidade10(char nomeBinDados[], char nomeBinArvB[], int n){
    // Abre o arquivo binário para leitura e escrita
    FILE *bin_dados = fopen(nomeBinDados, "rb+");
    FILE *bin_arvb = fopen(nomeBinArvB, "rb+");

    // Verifica se o arquivo foi aberto corretamente
    if(!bin_dados || !bin_arvb) {
        printf("Falha no processamento do arquivo.\n");
        if(bin_dados) fclose(bin_dados);
        if(bin_arvb) fclose(bin_arvb);
        return;
    }

    // Verifica se o arquivo binário é consistente, senão fecha o arquivo e retorna
    Cabecalho *cabecalho = cabecalho_ler_bin(bin_dados);
    if(!cabecalho_estavel(cabecalho)){
        printf("Falha no processamento do arquivo.\n");
        fclose(bin_dados);
        fclose(bin_arvb);

        return;
    }

    ArvB_Cabecalho *arvb_cabecalho = arvb_cabecalho_ler(bin_arvb); // Nome da variável corrigido
    if(!arvb_cabecalho) {
        printf("Falha no carregamento do índice.\n");
        fclose(bin_dados);
        fclose(bin_arvb);
        cabecalho_apagar(&cabecalho);
        
        return;
    }
    

    // Verifica se o arquivo contém registros válidos, senão fecha o arquivo e retorna
    if(cabecalho_get_nroRegArq(cabecalho) == 0 || cabecalho_get_nroRegArq(cabecalho) - cabecalho_get_nroRegRem(cabecalho) == 0) {
        printf("Registro inexistente.\n");
        fclose(bin_dados);
        fclose(bin_arvb);
        cabecalho_apagar(&cabecalho);
        arvb_cabecalho_apagar(&arvb_cabecalho);
        return;
    }
    arvb_cabecalho_set_status(arvb_cabecalho, '0');
    cabecalho_set_status(cabecalho, '0');

    // Executa o processo de inserir n vezes
    for(int insercaoAtual = 0; insercaoAtual < n; insercaoAtual++){
        int idAttack, year;
        float financialLoss;
        char *str_country = (char *)malloc(sizeof(char)*50);
        char *str_attackType = (char *)malloc(sizeof(char)*50);
        char *str_targetIndustry = (char *)malloc(sizeof(char)*50);
        char *str_defenseMechanism = (char *)malloc(sizeof(char)*50);
        
        scanf("%d %d %f ", &idAttack, &year, &financialLoss);
        scan_quote_string(str_country);
        scan_quote_string(str_attackType);
        scan_quote_string(str_targetIndustry);
        scan_quote_string(str_defenseMechanism);

        Registro *novo = registro_criar('0', -1, idAttack, year, financialLoss, str_country, str_attackType, str_targetIndustry, str_defenseMechanism);
        
        long int byteOffset = registro_inserir(bin_dados, novo, cabecalho);
        arvb_inserir(bin_arvb, arvb_cabecalho, registro_get_idAttack(novo), byteOffset);
        registro_apagar(&novo);

    }
    // Libera a memória e fecha o arquivo
    arvb_cabecalho_set_status(arvb_cabecalho, '1');
    cabecalho_set_status(cabecalho, '1');
    
    cabecalho_escrever(bin_dados, cabecalho);
    arvb_cabecalho_escrever(bin_arvb, arvb_cabecalho);
    cabecalho_apagar(&cabecalho);
    arvb_cabecalho_apagar(&arvb_cabecalho);
    fclose(bin_dados);
    fclose(bin_arvb);

    binarioNaTela(nomeBinDados);
    binarioNaTela(nomeBinArvB);
}


void funcionalidade11(char nomeBinDados[], char nomeBinArvB[], int n){
   
    // Abre o arquivo binário para leitura e escrita
    FILE *bin_dados = fopen(nomeBinDados, "rb+");
    FILE *bin_arvb = fopen(nomeBinArvB, "rb+");

    // Verifica se o arquivo foi aberto corretamente
    if(!bin_dados || !bin_arvb) {
        printf("Falha no processamento do arquivo.\n");
        if(bin_dados) fclose(bin_dados);
        if(bin_arvb) fclose(bin_arvb);
        return;
    }

    // Verifica se o arquivo binário é consistente, senão fecha o arquivo e retorna
    Cabecalho *cabecalho = cabecalho_ler_bin(bin_dados);
    if(!cabecalho_estavel(cabecalho)){
        printf("Falha no processamento do arquivo.\n");
        fclose(bin_dados);
        fclose(bin_arvb);

        return;
    }
    

    ArvB_Cabecalho *arvb_cabecalho = arvb_cabecalho_ler(bin_arvb); // Nome da variável corrigido
    if(!arvb_cabecalho) {
        printf("Falha no carregamento do índice.\n");
        fclose(bin_dados);
        fclose(bin_arvb);
        cabecalho_apagar(&cabecalho);
        
        return;
    }
   

    // Verifica se o arquivo contém registros válidos, senão fecha o arquivo e retorna
    if(cabecalho_get_nroRegArq(cabecalho) == 0 || cabecalho_get_nroRegArq(cabecalho) - cabecalho_get_nroRegRem(cabecalho) == 0) {
        printf("Registro inexistente.\n");
        fclose(bin_dados);
        fclose(bin_arvb);
        cabecalho_apagar(&cabecalho);
        arvb_cabecalho_apagar(&arvb_cabecalho);
        return;
    }
    cabecalho_set_status(cabecalho, '0');
    arvb_cabecalho_set_status(arvb_cabecalho, '0');

    // Executa o processo de atualizacao n vezes
    for(int atualizacaoAtual = 0; atualizacaoAtual < n; atualizacaoAtual++){
        
        // Inicializa variáveis de comparação com valores padrão
        int cmp_idAttack = -1;
        int cmp_year = -1;
        float cmp_financialLoss = -1;
        char cmp_country[50] = "";
        char cmp_attackType[50] = "";
        char cmp_targetIndustry[50] = "";
        char cmp_defenseMechanism[50] = "";
        

        int usarIndice = 0;


        //Lê a quantidade de campos a serem comparados
        int m;
        scanf("%d", &m);

        //Loop para receber os campos e valores de comparação
        for(int parCampoValor = 0; parCampoValor < m; parCampoValor++){
            
            

            char campo[30];
            scanf("%s ", campo);
            if(strcmp(campo, "idAttack") == 0){
                scanf("%d", &cmp_idAttack);
                usarIndice = 1;
            }
            if(strcmp(campo, "year") == 0){
                scanf("%d", &cmp_year);
            }
            if(strcmp(campo, "financialLoss") == 0){
                scanf("%f", &cmp_financialLoss);
            }
            if(strcmp(campo, "country") == 0){
                scan_quote_string(cmp_country);
            
            }
            if(strcmp(campo, "attackType") == 0){
                scan_quote_string(cmp_attackType);
            }
            if(strcmp(campo, "targetIndustry") == 0){
                scan_quote_string(cmp_targetIndustry);
            }
            if(strcmp(campo, "defenseMechanism") == 0){
                scan_quote_string(cmp_defenseMechanism);
            }

        }

        int idAttack = -1;
        int year = -1;
        float financialLoss = -1;
        char *country = (char *) malloc(sizeof(char)*50);
        char *attackType = (char *) malloc(sizeof(char)*50);
        char *targetIndustry = (char *) malloc(sizeof(char)*50);
        char *defenseMechanism = (char *) malloc(sizeof(char)*50);

        bool campos[7] = {false, false, false, false, false, false, false};

        int p;
        scanf("%d", &p);

        for(int parCampoValor = 0; parCampoValor < p; parCampoValor++){
            

            char campo[30];
            scanf("%s ", campo);
            if(strcmp(campo, "idAttack") == 0){
                scanf("%d", &idAttack);
                campos[0] = true;
            }
            if(strcmp(campo, "year") == 0){
                scanf("%d", &year);
                campos[1] = true;
            }
            if(strcmp(campo, "financialLoss") == 0){
                scanf("%f", &financialLoss);
                campos[2] = true;
            }
            if(strcmp(campo, "country") == 0){
                scan_quote_string(country);
                campos[3] = true;
            
            }
            if(strcmp(campo, "attackType") == 0){
                scan_quote_string(attackType);
                campos[4] = true;
            }
            if(strcmp(campo, "targetIndustry") == 0){
                scan_quote_string(targetIndustry);
                campos[5] = true;
            }
            if(strcmp(campo, "defenseMechanism") == 0){
                scan_quote_string(defenseMechanism);
                campos[6] = true;
            }

        }
        bool encontrou = false;

        if(usarIndice == 1) {
            
            long int byteOffset = arvb_buscar(bin_arvb, arvb_cabecalho, cmp_idAttack);
            if(byteOffset != -1) {
                
                fseek(bin_dados, byteOffset, SEEK_SET);
                Registro *registro = registro_ler_bin(bin_dados);
                
                if(registro != NULL && !registro_removido(registro)) {
                        
                    
                    if(registro_comparar(registro, -1, cmp_year, cmp_financialLoss, cmp_country, cmp_attackType, cmp_targetIndustry, cmp_defenseMechanism)) {
                        if(!campos[0]) idAttack = registro_get_idAttack(registro);
                        if(!campos[1]) year = registro_get_year(registro);
                        if(!campos[2]) financialLoss = registro_get_financialLoss(registro);
                        if(!campos[3]) strcpy(country, registro_get_country(registro));
                        if(!campos[4]) strcpy(attackType, registro_get_attackType(registro));
                        if(!campos[5]) strcpy(targetIndustry, registro_get_targetIndustry(registro));
                        if(!campos[6]) strcpy(defenseMechanism, registro_get_defenseMechanism(registro));
                        
                        
                        Registro *novo = registro_criar('0', -1, idAttack, year, financialLoss, country, attackType, targetIndustry, defenseMechanism);
                        
                        if(registro_get_tamanhoRegistro(novo) <= registro_get_tamanhoRegistro(registro)){
                            
                            registro_set_tamanhoRegistro(novo, registro_get_tamanhoRegistro(registro));
                            long int byteOffset = ftell(bin_dados) - (5 + registro_get_tamanhoRegistro(registro));
                            fseek(bin_dados, byteOffset, SEEK_SET);
                            registro_escrever(bin_dados, novo);
                        }
                        else{
                           
                            registro_remover(bin_dados, registro, cabecalho);
                            long int byteOffset = registro_inserir(bin_dados, novo, cabecalho);
                            arvb_update(bin_arvb, arvb_cabecalho, registro_get_idAttack(novo), byteOffset);
                        }
                        registro_apagar(&novo);            
                            encontrou = true;
                    }
                }
                if(registro != NULL) registro_apagar(&registro);
            }
        }
        
        else {
            encontrou = arvb_dfs_update(bin_arvb, bin_dados, cabecalho, arvb_cabecalho, arvb_cabecalho_get_noRaiz(arvb_cabecalho), cmp_year, cmp_financialLoss, cmp_country, cmp_attackType, cmp_targetIndustry, cmp_defenseMechanism, campos, year, financialLoss, country, attackType, targetIndustry, defenseMechanism);
            free(country);
            free(attackType);
            free(targetIndustry);
            free(defenseMechanism);
        }

    }
    // Libera a memória e fecha o arquivo
    arvb_cabecalho_set_status(arvb_cabecalho, '1');
    cabecalho_set_status(cabecalho, '1');

    cabecalho_escrever(bin_dados, cabecalho);
    arvb_cabecalho_escrever(bin_arvb, arvb_cabecalho);
    cabecalho_apagar(&cabecalho);
    arvb_cabecalho_apagar(&arvb_cabecalho);
    fclose(bin_dados);
    fclose(bin_arvb);

    binarioNaTela(nomeBinDados);
    binarioNaTela(nomeBinArvB);


}
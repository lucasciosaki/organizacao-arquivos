# Gerenciador de Dados de Ataques Cibernéticos

Este projeto consiste em um sistema gerenciador de banco de dados relacional simplificado, desenvolvido na linguagem C. O objetivo é manipular registros de ataques cibernéticos de forma eficiente, utilizando arquivos binários para armazenamento de dados e Árvores-B para indexação e recuperação rápida.

Desenvolvido como trabalho acadêmico para a disciplina de Organização de Arquivos.

## 👥 Autores

* **Lucas Mello Ciosaki** (NUSP: 14591305)
* **Artur Domitti Camargo** (NUSP: 15441661)

## 📋 Funcionalidades

O programa implementa operações completas de **CRUD** (Create, Read, Update, Delete) e indexação. As funcionalidades são selecionadas via entrada numérica padrão (`stdin`):

### Manipulação Básica
1.  **Conversão CSV -> Binário**: Importa dados de um arquivo `.csv` e gera o arquivo de dados binário.
2.  **Select All**: Recupera e exibe todos os registros ativos do arquivo binário.
3.  **Select Where**: Busca sequencial baseada em critérios de campo (ex: `year`, `country`).
4.  **Delete**: Remoção lógica de registros que correspondam aos critérios informados.
5.  **Insert**: Inserção de novos registros no arquivo de dados (com reaproveitamento de espaço de removidos).
6.  **Update**: Atualização de campos específicos em registros existentes.

### Indexação com Árvore-B
7.  **Create Index**: Cria um arquivo de índice utilizando uma Árvore-B (B-Tree) baseada no campo chave `idAttack`.
8.  **Select Where (Index)**: Busca otimizada utilizando a Árvore-B para encontrar registros pelo `idAttack`.
10. **Insert (Index)**: Insere um registro no arquivo de dados e atualiza a Árvore-B simultaneamente.
11. **Update (Index)**: Atualiza registros e mantém a consistência da Árvore-B caso a chave primária seja alterada.

## 🗂 Estrutura dos Dados

Cada registro armazena informações sobre incidentes de segurança, contendo os seguintes campos:

| Campo | Tipo | Descrição |
| :--- | :--- | :--- |
| `idAttack` | `int` | Identificador único do ataque (Chave Primária) |
| `year` | `int` | Ano da ocorrência |
| `financialLoss` | `float` | Prejuízo financeiro estimado |
| `country` | `string` | País onde ocorreu o ataque |
| `attackType` | `string` | Tipo de ataque (ex: Malware, DDoS) |
| `targetIndustry` | `string` | Indústria alvo |
| `defenseMechanism` | `string` | Mecanismo de defesa utilizado |

## 🛠️ Compilação e Execução

O projeto inclui um `Makefile` para facilitar a compilação.

### Pré-requisitos
* Compilador `gcc`
* Utilitário `make`

### Como compilar
Para gerar o executável `programaTrab`, execute:

```bash
make all
```
Para limpar arquivos objetos (`.o`) e o executável antigo:
```bash
make clean
```

### Como executar
Existem duas formas de executar o programa:

1. **Via Make**:
   ```bash
   make run
   ```

2. **Manualmente**:
   ```bash
   ./programaTrab
   ```

O programa espera comandos via entrada padrão (`stdin`). Você pode digitar os comandos manualmente após executar ou redirecionar um arquivo de entrada (recomendado para testes):

```bash
./programaTrab < entrada.in
```

### Exemplo de Uso
Para converter um arquivo `dados.csv` para binário `dados.bin` (Funcionalidade 1):
```text
1 dados.csv dados.bin
```

Para buscar (Funcionalidade 3) ataques ocorridos no ano de 2024:
```text
3 dados.bin 1
year 2024
```

## 📂 Estrutura de Arquivos

* `programaTrab.c`: Ponto de entrada (Main) e menu de seleção de funcionalidades.
* `funcionalidades/`: Implementação da lógica de negócio (CRUD e interface com usuário).
* `arquivo_de_dados/`: Manipulação de baixo nível dos registros e cabeçalhos do arquivo de dados.
* `arquivo_de_indice/`: Implementação da estrutura de dados Árvore-B (inserção, busca, split de nós).
* `Makefile`: Automação da compilação.

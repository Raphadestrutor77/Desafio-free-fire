#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20

typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

void limparBuffer();
void removerNovaLinha(char *str);
void mostrarComponentes(Componente vetor[], int qtd);
void cadastrarComponente(Componente vetor[], int *qtd);
void bubbleSortNome(Componente vetor[], int qtd);
void insertionSortTipo(Componente vetor[], int qtd);
void selectionSortPrioridade(Componente vetor[], int qtd);
int buscaBinariaPorNome(Componente vetor[], int qtd, char chave[]);

int main() {
    Componente torre[MAX_COMPONENTES];
    int qtdAtual = 0;
    int opcao;
    int ordenadoPorNome = 0;
    char nomeBusca[30];
    int indiceEncontrado;

    do {
        printf("\n============================================\n");
        printf("   SISTEMA DE MONTAGEM - TORRE DE RESGATE   \n");
        printf("============================================\n");
        printf("1. Cadastrar Componente\n");
        printf("2. Listar Componentes\n");
        printf("--- ESTRATÉGIAS DE ORDENAÇÃO ---\n");
        printf("3. Ordenar por NOME (Bubble Sort)\n");
        printf("4. Ordenar por TIPO (Insertion Sort)\n");
        printf("5. Ordenar por PRIORIDADE (Selection Sort)\n");
        printf("--- OPERAÇÕES AVANÇADAS ---\n");
        printf("6. Buscar Componente (Busca Binária - Requer Nome Ordenado)\n");
        printf("0. Sair\n");
        printf("Escolha sua estratégia: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                cadastrarComponente(torre, &qtdAtual);
                ordenadoPorNome = 0;
                break;
            case 2:
                mostrarComponentes(torre, qtdAtual);
                break;
            case 3:
                bubbleSortNome(torre, qtdAtual);
                ordenadoPorNome = 1;
                mostrarComponentes(torre, qtdAtual);
                break;
            case 4:
                insertionSortTipo(torre, qtdAtual);
                ordenadoPorNome = 0;
                mostrarComponentes(torre, qtdAtual);
                break;
            case 5:
                selectionSortPrioridade(torre, qtdAtual);
                ordenadoPorNome = 0;
                mostrarComponentes(torre, qtdAtual);
                break;
            case 6:
                if (ordenadoPorNome) {
                    printf("Nome do componente chave: ");
                    fgets(nomeBusca, 30, stdin);
                    removerNovaLinha(nomeBusca);
                    
                    clock_t inicio = clock();
                    indiceEncontrado = buscaBinariaPorNome(torre, qtdAtual, nomeBusca);
                    clock_t fim = clock();
                    double tempoGasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

                    if (indiceEncontrado != -1) {
                        printf("\n[SUCESSO] Componente '%s' pronto para instalação na posição %d.\n", 
                               torre[indiceEncontrado].nome, indiceEncontrado + 1);
                        printf("Prioridade: %d | Tipo: %s\n", 
                               torre[indiceEncontrado].prioridade, torre[indiceEncontrado].tipo);
                    } else {
                        printf("\n[ALERTA] Componente não encontrado no inventário.\n");
                    }
                    printf("Tempo de busca: %f segundos.\n", tempoGasto);

                } else {
                    printf("\n[ERRO] A lista precisa estar ordenada por NOME (Opção 3) para usar Busca Binária.\n");
                }
                break;
            case 0:
                printf("Encerrando sistema de engenharia...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void removerNovaLinha(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') str[len - 1] = '\0';
}

void cadastrarComponente(Componente vetor[], int *qtd) {
    if (*qtd >= MAX_COMPONENTES) {
        printf("\n[ERRO] Limite de componentes atingido (20).\n");
        return;
    }
    printf("\n--- NOVO COMPONENTE ---\n");
    printf("Nome (ex: Processador): ");
    fgets(vetor[*qtd].nome, 30, stdin);
    removerNovaLinha(vetor[*qtd].nome);

    printf("Tipo (ex: Eletronico): ");
    fgets(vetor[*qtd].tipo, 20, stdin);
    removerNovaLinha(vetor[*qtd].tipo);

    printf("Prioridade (1-10): ");
    scanf("%d", &vetor[*qtd].prioridade);
    limparBuffer();

    (*qtd)++;
    printf("[REGISTRADO] Componente adicionado.\n");
}

void mostrarComponentes(Componente vetor[], int qtd) {
    printf("\n%-3s | %-20s | %-15s | %s\n", "ID", "NOME", "TIPO", "PRIORIDADE");
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < qtd; i++) {
        printf("%02d  | %-20s | %-15s | %d\n", 
               i + 1, vetor[i].nome, vetor[i].tipo, vetor[i].prioridade);
    }
    printf("------------------------------------------------------------\n");
}

void bubbleSortNome(Componente vetor[], int qtd) {
    printf("\n[PROCESSANDO] Executando Bubble Sort por Nome...\n");
    clock_t inicio = clock();
    long comparacoes = 0;
    Componente temp;

    for (int i = 0; i < qtd - 1; i++) {
        for (int j = 0; j < qtd - i - 1; j++) {
            comparacoes++;
            if (strcmp(vetor[j].nome, vetor[j + 1].nome) > 0) {
                temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }

    clock_t fim = clock();
    double tempoGasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    
    printf("--- RELATÓRIO DE DESEMPENHO (BUBBLE) ---\n");
    printf("Comparações realizadas: %ld\n", comparacoes);
    printf("Tempo de execução: %f segundos\n", tempoGasto);
}

void insertionSortTipo(Componente vetor[], int qtd) {
    printf("\n[PROCESSANDO] Executando Insertion Sort por Tipo...\n");
    clock_t inicio = clock();
    long comparacoes = 0;
    int i, j;
    Componente chave;

    for (i = 1; i < qtd; i++) {
        chave = vetor[i];
        j = i - 1;

        while (j >= 0) {
            comparacoes++;
            if (strcmp(vetor[j].tipo, chave.tipo) > 0) {
                vetor[j + 1] = vetor[j];
                j = j - 1;
            } else {
                break;
            }
        }
        vetor[j + 1] = chave;
    }

    clock_t fim = clock();
    double tempoGasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    printf("--- RELATÓRIO DE DESEMPENHO (INSERTION) ---\n");
    printf("Comparações estimadas: %ld\n", comparacoes);
    printf("Tempo de execução: %f segundos\n", tempoGasto);
}

void selectionSortPrioridade(Componente vetor[], int qtd) {
    printf("\n[PROCESSANDO] Executando Selection Sort por Prioridade...\n");
    clock_t inicio = clock();
    long comparacoes = 0;
    int i, j, min_idx;
    Componente temp;

    for (int i = 0; i < qtd - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < qtd; j++) {
            comparacoes++;
            if (vetor[j].prioridade < vetor[min_idx].prioridade) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            temp = vetor[i];
            vetor[i] = vetor[min_idx];
            vetor[min_idx] = temp;
        }
    }

    clock_t fim = clock();
    double tempoGasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    printf("--- RELATÓRIO DE DESEMPENHO (SELECTION) ---\n");
    printf("Comparações realizadas: %ld\n", comparacoes);
    printf("Tempo de execução: %f segundos\n", tempoGasto);
}

int buscaBinariaPorNome(Componente vetor[], int qtd, char chave[]) {
    int inicio = 0;
    int fim = qtd - 1;
    int meio;
    int comparacoesBusca = 0;

    printf("\n[BUSCA] Iniciando varredura binária...\n");

    while (inicio <= fim) {
        comparacoesBusca++;
        meio = (inicio + fim) / 2;
        
        int resultado = strcmp(vetor[meio].nome, chave);

        if (resultado == 0) {
            printf("Busca Binária - Comparações feitas: %d\n", comparacoesBusca);
            return meio;
        } else if (resultado < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    
    printf("Busca Binária - Comparações feitas: %d\n", comparacoesBusca);
    return -1;
}
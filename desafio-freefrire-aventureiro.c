#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10

struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
};

struct No {
    struct Item dados;
    struct No* proximo;
};

void limparBuffer();
void removerNovaLinha(char *str);
struct Item criarItemInput();

void inserirItemVetor(struct Item mochila[], int *qtdAtual);
void removerItemVetor(struct Item mochila[], int *qtdAtual);
void listarItensVetor(struct Item mochila[], int qtdAtual);
void buscarSequencialVetor(struct Item mochila[], int qtdAtual);
void ordenarVetor(struct Item mochila[], int qtdAtual);
void buscarBinariaVetor(struct Item mochila[], int qtdAtual);

void inserirItemLista(struct No** cabeca);
void removerItemLista(struct No** cabeca);
void listarItensLista(struct No* cabeca);
void buscarSequencialLista(struct No* cabeca);
void liberarLista(struct No* cabeca);

void menuVetor();
void menuLista();

int main() {
    int opcaoPrincipal;

    do {
        printf("\n#############################################\n");
        printf("   SISTEMA DE INVENTÁRIO - SELEÇÃO DE ESTRUTURA\n");
        printf("#############################################\n");
        printf("1. Modo VETOR (Lista Sequencial + Busca Binária)\n");
        printf("2. Modo LISTA ENCADEADA (Alocação Dinâmica)\n");
        printf("0. Sair\n");
        printf("Escolha a arquitetura: ");
        scanf("%d", &opcaoPrincipal);
        limparBuffer();

        switch (opcaoPrincipal) {
            case 1:
                menuVetor();
                break;
            case 2:
                menuLista();
                break;
            case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcaoPrincipal != 0);

    return 0;
}

void menuVetor() {
    struct Item mochila[MAX_ITENS];
    int qtdAtual = 0;
    int opcao;
    int vetorOrdenado = 0;

    do {
        printf("\n--- MODO VETOR (%d/%d) ---\n", qtdAtual, MAX_ITENS);
        printf("1. Inserir Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens\n");
        printf("4. Busca SEQUENCIAL (Nome)\n");
        printf("5. Ordenar Inventário (Necessário para Busca Binária)\n");
        printf("6. Busca BINÁRIA (Nome)\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Opção: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                inserirItemVetor(mochila, &qtdAtual);
                vetorOrdenado = 0;
                break;
            case 2:
                removerItemVetor(mochila, &qtdAtual);
                break;
            case 3:
                listarItensVetor(mochila, qtdAtual);
                break;
            case 4:
                buscarSequencialVetor(mochila, qtdAtual);
                break;
            case 5:
                ordenarVetor(mochila, qtdAtual);
                vetorOrdenado = 1;
                break;
            case 6:
                if (vetorOrdenado) {
                    buscarBinariaVetor(mochila, qtdAtual);
                } else {
                    printf("\n[ALERTA] O vetor precisa estar ORDENADO antes da busca binária.\n");
                    printf("Execute a opção 5 primeiro.\n");
                }
                break;
            case 0:
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);
}

void inserirItemVetor(struct Item mochila[], int *qtdAtual) {
    if (*qtdAtual >= MAX_ITENS) {
        printf("\n[ERRO] Mochila cheia (Limite do Vetor atingido).\n");
        return;
    }
    mochila[*qtdAtual] = criarItemInput();
    (*qtdAtual)++;
    printf("[SUCESSO] Item adicionado ao vetor.\n");
}

void removerItemVetor(struct Item mochila[], int *qtdAtual) {
    if (*qtdAtual == 0) {
        printf("\n[ERRO] Mochila vazia.\n");
        return;
    }
    char nome[30];
    printf("Nome do item a remover: ");
    fgets(nome, 30, stdin);
    removerNovaLinha(nome);

    int i, j, encontrado = 0;
    for (i = 0; i < *qtdAtual; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            encontrado = 1;
            for (j = i; j < *qtdAtual - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*qtdAtual)--;
            printf("[SUCESSO] Item removido.\n");
            break;
        }
    }
    if (!encontrado) printf("[INFO] Item não encontrado.\n");
}

void listarItensVetor(struct Item mochila[], int qtdAtual) {
    printf("\n--- VETOR DE ITENS ---\n");
    if (qtdAtual == 0) printf("Vazio.\n");
    for (int i = 0; i < qtdAtual; i++) {
        printf("[%d] %s (Qtd: %d, Tipo: %s)\n", i, mochila[i].nome, mochila[i].quantidade, mochila[i].tipo);
    }
}

void buscarSequencialVetor(struct Item mochila[], int qtdAtual) {
    char nome[30];
    printf("Buscar (Sequencial): ");
    fgets(nome, 30, stdin);
    removerNovaLinha(nome);

    int comparacoes = 0;
    int encontrado = 0;

    for (int i = 0; i < qtdAtual; i++) {
        comparacoes++;
        if (strcmp(mochila[i].nome, nome) == 0) {
            printf("\n[ACHOU] %s na posição %d.\n", mochila[i].nome, i);
            encontrado = 1;
            break; 
        }
    }
    printf("Total de comparações: %d\n", comparacoes);
    if (!encontrado) printf("Item não encontrado.\n");
}

void ordenarVetor(struct Item mochila[], int qtdAtual) {
    struct Item temp;
    for (int i = 0; i < qtdAtual - 1; i++) {
        for (int j = 0; j < qtdAtual - i - 1; j++) {
            if (strcmp(mochila[j].nome, mochila[j + 1].nome) > 0) {
                temp = mochila[j];
                mochila[j] = mochila[j + 1];
                mochila[j + 1] = temp;
            }
        }
    }
    printf("\n[SUCESSO] Mochila ordenada por nome!\n");
}

void buscarBinariaVetor(struct Item mochila[], int qtdAtual) {
    char nome[30];
    printf("Buscar (Binária): ");
    fgets(nome, 30, stdin);
    removerNovaLinha(nome);

    int inicio = 0;
    int fim = qtdAtual - 1;
    int meio;
    int comparacoes = 0;
    int encontrado = 0;

    while (inicio <= fim) {
        comparacoes++;
        meio = (inicio + fim) / 2;
        int resultado = strcmp(mochila[meio].nome, nome);

        if (resultado == 0) {
            printf("\n[ACHOU] %s na posição %d.\n", mochila[meio].nome, meio);
            encontrado = 1;
            break;
        } else if (resultado < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    printf("Total de comparações: %d\n", comparacoes);
    if (!encontrado) printf("Item não encontrado.\n");
}

void menuLista() {
    struct No* cabeca = NULL;
    int opcao;

    do {
        printf("\n--- MODO LISTA ENCADEADA ---\n");
        printf("1. Inserir Item (Dinâmico)\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens\n");
        printf("4. Busca Sequencial\n");
        printf("0. Voltar e Liberar Memória\n");
        printf("Opção: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                inserirItemLista(&cabeca);
                break;
            case 2:
                removerItemLista(&cabeca);
                break;
            case 3:
                listarItensLista(cabeca);
                break;
            case 4:
                buscarSequencialLista(cabeca);
                break;
            case 0:
                liberarLista(cabeca);
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);
}

void inserirItemLista(struct No** cabeca) {
    struct No* novoNo = (struct No*)malloc(sizeof(struct No));
    if (novoNo == NULL) {
        printf("[ERRO] Falha na alocação de memória.\n");
        return;
    }

    novoNo->dados = criarItemInput();
    novoNo->proximo = NULL;

    if (*cabeca == NULL) {
        *cabeca = novoNo;
    } else {
        struct No* temp = *cabeca;
        while (temp->proximo != NULL) {
            temp = temp->proximo;
        }
        temp->proximo = novoNo;
    }
    printf("[SUCESSO] Item adicionado à lista encadeada.\n");
}

void removerItemLista(struct No** cabeca) {
    if (*cabeca == NULL) {
        printf("[ERRO] Lista vazia.\n");
        return;
    }
    char nome[30];
    printf("Nome do item a remover: ");
    fgets(nome, 30, stdin);
    removerNovaLinha(nome);

    struct No* atual = *cabeca;
    struct No* anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nome) == 0) {
            if (anterior == NULL) {
                *cabeca = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            printf("[SUCESSO] Item removido da memória.\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("[INFO] Item não encontrado.\n");
}

void listarItensLista(struct No* cabeca) {
    printf("\n--- LISTA ENCADEADA ---\n");
    struct No* atual = cabeca;
    int i = 0;
    if (cabeca == NULL) printf("Lista vazia.\n");
    
    while (atual != NULL) {
        printf("Nó[%d] -> %s (Qtd: %d)\n", i++, atual->dados.nome, atual->dados.quantidade);
        atual = atual->proximo;
    }
    printf("NULL\n");
}

void buscarSequencialLista(struct No* cabeca) {
    char nome[30];
    printf("Buscar na Lista: ");
    fgets(nome, 30, stdin);
    removerNovaLinha(nome);

    struct No* atual = cabeca;
    int comparacoes = 0;
    int encontrado = 0;

    while (atual != NULL) {
        comparacoes++;
        if (strcmp(atual->dados.nome, nome) == 0) {
            printf("\n[ACHOU] %s encontrado.\n", atual->dados.nome);
            encontrado = 1;
            break;
        }
        atual = atual->proximo;
    }
    printf("Total de comparações: %d\n", comparacoes);
    if (!encontrado) printf("Item não encontrado.\n");
}

void liberarLista(struct No* cabeca) {
    struct No* atual = cabeca;
    struct No* prox;
    while (atual != NULL) {
        prox = atual->proximo;
        free(atual);
        atual = prox;
    }
}

struct Item criarItemInput() {
    struct Item i;
    printf("Nome: ");
    fgets(i.nome, 30, stdin);
    removerNovaLinha(i.nome);
    printf("Tipo: ");
    fgets(i.tipo, 20, stdin);
    removerNovaLinha(i.tipo);
    printf("Quantidade: ");
    scanf("%d", &i.quantidade);
    limparBuffer();
    return i;
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void removerNovaLinha(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') str[len - 1] = '\0';
}
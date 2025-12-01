#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10

struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
};

void limparBuffer();
void removerNovaLinha(char *str);
void listarItens(struct Item mochila[], int qtdAtual);
void inserirItem(struct Item mochila[], int *qtdAtual);
void removerItem(struct Item mochila[], int *qtdAtual);
void buscarItem(struct Item mochila[], int qtdAtual);

int main() {
    struct Item mochila[MAX_ITENS];
    int qtdAtual = 0;
    int opcao;

    do {
        printf("\n====================================\n");
        printf("      MOCHILA TÁTICA - MENU         \n");
        printf("====================================\n");
        printf("1. Adicionar Item (Loot)\n");
        printf("2. Remover Item (Descartar)\n");
        printf("3. Buscar Item (Equipar/Verificar)\n");
        printf("4. Listar Todos os Itens\n");
        printf("0. Sair do Jogo\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                inserirItem(mochila, &qtdAtual);
                break;
            case 2:
                removerItem(mochila, &qtdAtual);
                break;
            case 3:
                buscarItem(mochila, qtdAtual);
                break;
            case 4:
                listarItens(mochila, qtdAtual);
                break;
            case 0:
                printf("\nEncerrando sistema de inventário...\n");
                break;
            default:
                printf("\n[ERRO] Opção inválida! Tente novamente.\n");
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
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

void listarItens(struct Item mochila[], int qtdAtual) {
    printf("\n--- CONTEÚDO DA MOCHILA (%d/%d) ---\n", qtdAtual, MAX_ITENS);
    
    if (qtdAtual == 0) {
        printf("A mochila está vazia.\n");
    } else {
        printf("%-3s | %-20s | %-15s | %s\n", "ID", "NOME", "TIPO", "QTD");
        printf("----------------------------------------------------------\n");
        for (int i = 0; i < qtdAtual; i++) {
            printf("%02d  | %-20s | %-15s | %d\n", 
                   i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
        }
    }
    printf("----------------------------------------------------------\n");
}

void inserirItem(struct Item mochila[], int *qtdAtual) {
    if (*qtdAtual >= MAX_ITENS) {
        printf("\n[AVISO] Mochila cheia! Descarte itens antes de pegar novos.\n");
        return;
    }

    printf("\n--- NOVO LOOT ---\n");
    
    printf("Nome do item: ");
    fgets(mochila[*qtdAtual].nome, 30, stdin);
    removerNovaLinha(mochila[*qtdAtual].nome);

    printf("Tipo (Arma, Municao, Cura): ");
    fgets(mochila[*qtdAtual].tipo, 20, stdin);
    removerNovaLinha(mochila[*qtdAtual].tipo);

    printf("Quantidade: ");
    scanf("%d", &mochila[*qtdAtual].quantidade);
    limparBuffer();

    (*qtdAtual)++;
    printf("\n[SUCESSO] Item guardado na mochila!\n");
    
    listarItens(mochila, *qtdAtual);
}

void removerItem(struct Item mochila[], int *qtdAtual) {
    if (*qtdAtual == 0) {
        printf("\n[ERRO] A mochila já está vazia.\n");
        return;
    }

    char nomeParaRemover[30];
    printf("\n--- DESCARTAR ITEM ---\n");
    printf("Digite o nome do item para remover: ");
    fgets(nomeParaRemover, 30, stdin);
    removerNovaLinha(nomeParaRemover);

    int encontrado = 0;

    for (int i = 0; i < *qtdAtual; i++) {
        if (strcmp(mochila[i].nome, nomeParaRemover) == 0) {
            encontrado = 1;
            
            for (int j = i; j < *qtdAtual - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            
            (*qtdAtual)--;
            printf("\n[SUCESSO] %s foi removido da mochila.\n", nomeParaRemover);
            break;
        }
    }

    if (!encontrado) {
        printf("\n[ERRO] Item '%s' não encontrado na mochila.\n", nomeParaRemover);
    } else {
        listarItens(mochila, *qtdAtual);
    }
}

void buscarItem(struct Item mochila[], int qtdAtual) {
    if (qtdAtual == 0) {
        printf("\n[AVISO] Mochila vazia. Nada para buscar.\n");
        return;
    }

    char nomeBusca[30];
    printf("\n--- BUSCAR ITEM ---\n");
    printf("Digite o nome do item: ");
    fgets(nomeBusca, 30, stdin);
    removerNovaLinha(nomeBusca);

    int encontrado = 0;

    for (int i = 0; i < qtdAtual; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\n[ITEM ENCONTRADO]\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            printf("Posição na mochila: %d\n", i + 1);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("\n[INFO] O item '%s' não está na sua mochila.\n", nomeBusca);
    }
}
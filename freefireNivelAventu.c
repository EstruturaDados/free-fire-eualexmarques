#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Structs
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// Vetor
#define MAX_ITENS 100
Item mochilaVetor[MAX_ITENS];
int totalItensVetor = 0;
int comparacoesSequencialVetor = 0;
int comparacoesBinariaVetor = 0;

// Lista Encadeada
No* mochilaLista = NULL;
int comparacoesSequencialLista = 0;

// Funções Vetor
void inserirItemVetor(Item novo) {
    if (totalItensVetor < MAX_ITENS) {
        mochilaVetor[totalItensVetor++] = novo;
    } else {
        printf("Mochila cheia!\n");
    }
}

void removerItemVetor(char nome[]) {
    for (int i = 0; i < totalItensVetor; i++) {
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            for (int j = i; j < totalItensVetor - 1; j++) {
                mochilaVetor[j] = mochilaVetor[j + 1];
            }
            totalItensVetor--;
            printf("Item removido.\n");
            return;
        }
    }
    printf("Item não encontrado.\n");
}

void listarItensVetor() {
     printf("\nItens na mochila (%d/10):\n", totalItensVetor);
    for (int i = 0; i < totalItensVetor; i++) {
        printf("Nome: %s | Tipo: %s | Qtd: %d\n", mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
    }
}

int buscarSequencialVetor(char nome[]) {
    comparacoesSequencialVetor = 0;
    for (int i = 0; i < totalItensVetor; i++) {
        comparacoesSequencialVetor++;
        if (strcmp(mochilaVetor[i].nome, nome) == 0) return i;
    }
    return -1;
}

void ordenarVetor() {
    for (int i = 0; i < totalItensVetor - 1; i++) {
        for (int j = 0; j < totalItensVetor - i - 1; j++) {
            if (strcmp(mochilaVetor[j].nome, mochilaVetor[j + 1].nome) > 0) {
                Item temp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j + 1];
                mochilaVetor[j + 1] = temp;
            }
        }
    }
    printf("Itens ordenados.\n");
}

int buscarBinariaVetor(char nome[]) {
    comparacoesBinariaVetor = 0;
    int inicio = 0, fim = totalItensVetor - 1;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoesBinariaVetor++;
        int cmp = strcmp(mochilaVetor[meio].nome, nome);
        if (cmp == 0) return meio;
        else if (cmp < 0) inicio = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

// Funções Lista Encadeada
void inserirItemLista(Item novo) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->dados = novo;
    novoNo->proximo = mochilaLista;
    mochilaLista = novoNo;
}

void removerItemLista(char nome[]) {
    No *atual = mochilaLista, *anterior = NULL;
    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nome) == 0) {
            if (anterior == NULL) mochilaLista = atual->proximo;
            else anterior->proximo = atual->proximo;
            free(atual);
            printf("Item removido.\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("Item não encontrado.\n");
}

int contarItensLista() {
    int contador = 0;
    No* atual = mochilaLista;
    while (atual != NULL) {
        contador++;
        atual = atual->proximo;
    }
    return contador;
}


void listarItensLista() {
    printf("Itens na mochila: (%d/10)\n", contarItensLista());
    No* atual = mochilaLista;
    while (atual != NULL) {
        printf("Nome: %s | Tipo: %s | Qtd: %d\n", atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
    }
}

int buscarSequencialLista(char nome[]) {
    comparacoesSequencialLista = 0;
    No* atual = mochilaLista;
    while (atual != NULL) {
        comparacoesSequencialLista++;
        if (strcmp(atual->dados.nome, nome) == 0) return 1;
        atual = atual->proximo;
    }
    return 0;
}

// Medição de tempo
void mostrarTempo(clock_t inicio, clock_t fim, const char* operacao) {
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo de execução de %s: %.4f segundos\n", operacao, tempo);
    if (tempo > 2.0) {
        printf("Operação excedeu o limite de 2 segundos!\n");
    }
}

// Menu
void menu() {
    int escolha, estrutura;
    char nomeBusca[30];
    Item novo;

    printf("Estruturas de organização\n");
    printf("1 - Vetor\n");
    printf("2 - Lista Encadeada\n");
    printf("Escolha a estrutura: ");
    scanf("%d", &estrutura);
    getchar();

    do {
        printf("\n====================\n");
        printf("Abrindo mochila\n");
        printf("====================\n");
        printf("\n1 - Inserir\n");
        printf("2 - Remover\n");
        printf("3 - Listar\n");
        printf("4 - Buscar Sequencial\n");
        printf("5 - Ordenar (vetor)\n");
        printf("6 - Buscar Binária (vetor)\n");
        printf("0 - Sair\n");
        printf("Escolha opção: ");
        scanf("%d", &escolha);
        getchar();

        clock_t inicio, fim;

        switch (escolha) {
            case 1:
                printf("\nNome: "); fgets(novo.nome, 30, stdin); novo.nome[strcspn(novo.nome, "\n")] = '\0';
                printf("Tipo: "); fgets(novo.tipo, 20, stdin); novo.tipo[strcspn(novo.tipo, "\n")] = '\0';
                printf("Quantidade: "); scanf("%d", &novo.quantidade); getchar();
                inicio = clock();
                if (estrutura == 1) inserirItemVetor(novo);
                else inserirItemLista(novo);
                break;

            case 2:
                printf("Nome do item a remover: "); fgets(nomeBusca, 30, stdin); nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                inicio = clock();
                if (estrutura == 1) removerItemVetor(nomeBusca);
                else removerItemLista(nomeBusca);
                break;

            case 3:
                inicio = clock();
                if (estrutura == 1) listarItensVetor();
                else listarItensLista();
                break;

            case 4:
                printf("Nome do item a buscar: "); fgets(nomeBusca, 30, stdin); nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                inicio = clock();
                if (estrutura == 1) {
                    int pos = buscarSequencialVetor(nomeBusca);
                    fim = clock();
                    mostrarTempo(inicio, fim, "busca sequencial");
                    printf("Comparações: %d\n", comparacoesSequencialVetor);
                    if (pos != -1) printf("Item encontrado na posição %d\n", pos);
                    else printf("Item não encontrado\n");
                } else {
                    int achou = buscarSequencialLista(nomeBusca);
                    fim = clock();
                    mostrarTempo(inicio, fim, "busca sequencial");
                    printf("Comparações: %d\n", comparacoesSequencialLista);
                    if (achou) printf("Item encontrado\n");
                    else printf("Item não encontrado\n");
                }
                break;

            case 5:
                if (estrutura == 1) {
                    inicio = clock();
                    ordenarVetor();
                    fim = clock();
                    mostrarTempo(inicio, fim, "ordenação");
                } else {
                    printf("Ordenação não disponível para lista encadeada.\n");
                }
                break;

            case 6:
                if (estrutura == 1) {
                    printf("Nome do item a buscar: "); fgets(nomeBusca, 30, stdin); nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                    inicio = clock();
                    int pos = buscarBinariaVetor(nomeBusca);
                    fim = clock();
                    mostrarTempo(inicio, fim, "busca binária");
                    printf("Comparações: %d\n", comparacoesBinariaVetor);
                    if (pos != -1) printf("Item encontrado na posição %d\n", pos);
                    else printf("Item não encontrado\n");

                } else {
                    printf("Busca binária não disponível para lista encadeada.\n");
                }
                break;
        }
    } while (escolha != 0);
}

// Principal
int main() {
    menu();
    return 0;
}
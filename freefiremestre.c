#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Estruta componente
typedef struct 
{
    char nome[30];
    char tipo[20];
    int quantidade;
    int prioridade;
}Componente;

#define MAX_ITENS 20//Declarando quantidade maxima de itens

Componente mochila[MAX_ITENS];
int totalItens = 0;
int comparacoesBinaria = 0;
int buscainsertionsort = 0;
int comparacoesBubble = 0;
int trocasBubble = 0;
int comparacoesInsertion = 0;
int trocasInsertion = 0;
int comparacoesSelection = 0;
int trocasSelection = 0;

//Inesrindo os itesn
void inserirItem(Componente novo) {
    if (totalItens < MAX_ITENS) {
        mochila[totalItens++] = novo;
    } else {
        printf("Mochila cheia!\n");
    }
}

//Removendo itens
void removerItem(char nome[]) {
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            for (int j = i; j < totalItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            totalItens--;
            printf("Item removido.\n");
            return;
        }
    }
    printf("Item não encontrado.\n");
}

//Listar itens adicionados
void listarItens() {
    printf("\nItens na mochila (%d/%d):\n", totalItens, MAX_ITENS);
    
    printf("\n%-20s %-15s %-10s %-10s\n", "Nome", "Tipo", "Qtd", "Prioridade");
    printf("---------------------------------------------------------------\n");
        for (int i = 0; i < totalItens; i++) {
        printf("%-20s %-15s %-10d %-10d\n",
           mochila[i].nome,
           mochila[i].tipo,
           mochila[i].quantidade,
           mochila[i].prioridade);
        }
        
    
}

//Ordenação bubbler Sort (ou bolha)
void bubbleSortPorNome() {
    comparacoesBubble = 0;
    trocasBubble = 0;
    for (int i = 0; i < totalItens - 1; i++) {
        for (int j = 0; j < totalItens - i - 1; j++) {
            comparacoesBubble++;
            if (strcmp(mochila[j].nome, mochila[j + 1].nome) > 0) {
                Componente temp = mochila[j];
                mochila[j] = mochila[j + 1];
                mochila[j + 1] = temp;
                trocasBubble++;
            }
        }
    }
    printf("\nItens ordenados.\n");
    printf("Comparações: %d | Trocas: %d\n", comparacoesBubble, trocasBubble);
}

//Ordenação Insertion Sort
void insertionSortPorTipo() {
    comparacoesInsertion = 0;
    trocasInsertion = 0;
    int j;
    Componente chave;
    for (int i = 1; i < totalItens; i++) {
        chave = mochila[i];
        j = i - 1;
        while (j >= 0) {
            comparacoesInsertion++;
            if (strcmp(mochila[j].tipo, chave.tipo) > 0) {
                mochila[j + 1] = mochila[j];
                trocasInsertion++;
                j--;
            } else {
                break;
            }
        }
        mochila[j + 1] = chave;
        trocasInsertion++; // inserção final do elemento
    }
    printf("\nItens ordenados.\n");
    printf("Comparações: %d | Trocas: %d\n", comparacoesInsertion, trocasInsertion);
}

//Ordenação Selection Sort
void selectionSortPrioridade() {
    comparacoesSelection = 0;
    trocasSelection = 0;
    int i, j, indice_min;
    Componente temp;
    for (i = 0; i < totalItens - 1; i++) {
        indice_min = i;
        for (j = i + 1; j < totalItens; j++) {
            comparacoesSelection++;
            if (mochila[j].prioridade > mochila[indice_min].prioridade) {
                indice_min = j;
            }
        }
        if (indice_min != i) {
            temp = mochila[i];
            mochila[i] = mochila[indice_min];
            mochila[indice_min] = temp;
            trocasSelection++;
        }
    }
    printf("\nItens ordenados.\n");
    printf("Comparações: %d | Trocas: %d\n", comparacoesSelection, trocasSelection);
}

//Ordenar por nome 
int estaOrdenadoPorNome() {
    for (int i = 0; i < totalItens - 1; i++) {
        if (strcmp(mochila[i].nome, mochila[i + 1].nome) > 0) {
            return 0; // não está ordenado
        }
    }
    return 1; // está ordenado
}

//Busca binaria
int buscarBinaria(char nome[]) {
    comparacoesBinaria = 0;
    int inicio = 0, fim = totalItens - 1;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoesBinaria++;
        int cmp = strcmp(mochila[meio].nome, nome);
        if (cmp == 0) return meio;
        else if (cmp < 0) inicio = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

//Mostrar o tempo de execução
void mostrarTempo(clock_t inicio, clock_t fim, const char* operacao) {
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo de execução de %s: %.4f segundos\n", operacao, tempo);
    if (tempo > 2.0) {
        printf("Operação excedeu o limite de 2 segundos!\n");
    }
}//Menu
int main() {

    Componente novo;
    int escolha;
    char nomeBusca[30];
    clock_t inicio, fim;

    do {
        printf("\nItens na mochila (%d/%d)", totalItens, MAX_ITENS);
        printf("\n====================\n");
        printf("Abrindo mochila\n");
        printf("====================\n");
        printf("\n1 - Adicionar componente\n");
        printf("2 - Remover componente\n");
        printf("3 - Listar componentes\n");
        printf("4 - Organizar mochila (Ordenar componentes)\n");
        printf("5 - Busca binaria por componentes-chave (por nome)\n");
        printf("0 - Sair\n");
        printf("Escolha opção: ");
        scanf("%d", &escolha);
        getchar();

        switch (escolha){
        case 1:
            printf("\nNome: "); 
            fgets(novo.nome, 30, stdin); novo.nome[strcspn(novo.nome, "\n")] = '\0';

            printf("Tipo: "); 
            fgets(novo.tipo, 20, stdin); novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

            printf("Quantidade: "); 
            scanf("%d", &novo.quantidade); 
            getchar();

            printf("Prioridade: ");
            scanf("%d", &novo.prioridade);
            getchar();

            inserirItem(novo);

            break;

        case 2:
            printf("Nome do item a remover: "); 
            fgets(nomeBusca, 30, stdin); nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

            removerItem(nomeBusca);

            break;

        case 3:
            listarItens();
            break;

        case 4:
            int opcao;

            do
            {
                printf("\nEstrategia de organização\n");
                printf("Como deseja ordenar os componentes\n");
                printf("1. Por nome (Ordem alfabetica)\n");
                printf("2. Por tipo\n");
                printf("3. Por prioridade de montagem\n");
                printf("0. Cancelar\n");
                printf("Escolha o criterio: ");
                scanf("%d", &opcao);
                getchar();

                if (opcao == 1){
                    inicio = clock();
                    bubbleSortPorNome();
                    fim = clock();
                    mostrarTempo(inicio, fim, "Bubble Sort por nome");
                    listarItens();
                }else if (opcao == 2){
                    inicio = clock();
                    insertionSortPorTipo();
                    fim = clock();
                    mostrarTempo(inicio, fim, "Insertion Sort por tipo");
                    listarItens();
                }else if (opcao == 3){
                    inicio = clock();
                    selectionSortPrioridade();
                    fim = clock();
                    mostrarTempo(inicio, fim, "Selection Sort por prioridade");
                    listarItens();
                }
                
            } while (opcao != 0);
            

            break;

        case 5:
            //Verifica primeiro se esta ordenado por nome antes de fazer a busca
            if (!estaOrdenadoPorNome()) {
            printf("ALERTA: Busca binária requer que a mochila esteja ordenada por NOME.\n");
            printf("Use a opção 4 para organizar a mochila primeiro.\n");
             break;
            }

            printf("Nome do item a buscar: "); 
            fgets(nomeBusca, 30, stdin); nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
            inicio = clock();
            int pos = buscarBinaria(nomeBusca);
            fim = clock();
            mostrarTempo(inicio, fim, "busca binária");
            if (pos != -1) {
                Componente encontrado = mochila[pos];
                printf("Item encontrado na posição %d\n", pos);
                printf("Nome: %s | Tipo: %s | Qtd: %d | Prioridade: %d\n",encontrado.nome, encontrado.tipo, encontrado.quantidade, encontrado.prioridade);
                }else {
                    printf("Item não encontrado\n");
                }
                
            break;
        
        default:
            break;
        }

    } while (escolha != 0);
    return 0;
}
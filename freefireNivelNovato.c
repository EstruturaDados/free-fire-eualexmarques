#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10//Declarando a quantidade maxima de itens

typedef struct {
    char nome[30];
    char tipo [20];
    int quantidade;
}Item;
//Adicinando os itens
void adicionarItens(Item mochila[], int *quantidadeatual){
    if (*quantidadeatual >= MAX_ITENS){
        printf("Erro: mochila cheia.\n");
        return;
    }
    Item novo;
    printf("Digite o nome do item: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0'; //Remove o \n

    printf("Digite o tipo do item (arma, munição, cura, ferramenta): ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0'; //Remove o \n

    printf("Digite a quantidade: ");
      char entrada[10];
    fgets(entrada, sizeof(entrada), stdin);
    novo.quantidade = atoi(entrada);//Transforma em um numero inteiro

    mochila[*quantidadeatual] = novo;
    (*quantidadeatual)++;

    printf("Item \"%s\" adicionado com sucesso! Total de itens: %d/%d\n", novo.nome, *quantidadeatual, MAX_ITENS);
}
//Removendo item
void removerItens(Item mochila[], int *quantidadeatual){
    if (*quantidadeatual == 0) {
        printf("Mochila vazia! Nenhum item para remover.\n");
        return;
    }

    char nomeRemover[30];
    printf("Digite o nome do item a ser removido: ");
    fgets(nomeRemover, sizeof(nomeRemover), stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = '\0'; //Remove o \n

    int encontrado = 0;
    for (int i = 0; i < *quantidadeatual; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            //Item encontrado: desloca os próximos para preencher o espaço
            for (int j = i; j < *quantidadeatual - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*quantidadeatual)--;
            printf("Item \"%s\" removido com sucesso! (%d/%d)\n", nomeRemover, *quantidadeatual, MAX_ITENS);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Item \"%s\" não encontrado na mochila.\n", nomeRemover);
    }

    
}
//Mostra os itens que tem na mochila e a quantidade
void listarItens(Item mochila[], int quantidade){
   printf("\nItens na mochila (%d/%d):\n", quantidade, MAX_ITENS);

    if (quantidade == 0) {
        printf("Mochila vazia.\n");
        return;
    }

    for (int i = 0; i < quantidade; i++) {
        printf("%d. Nome: %s      | Tipo: %s      | Quantidade: %d\n", i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }

   
}


int main() {

    int mochila[MAX_ITENS];
    int quantidade =0;
    int opcao;
    //Menu de entrada
    do
    {
        printf("\nAbrindo mochila\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();
        
         switch (opcao) {
            case 1:
                adicionarItens(mochila, &quantidade);
                break;
            case 2:
                removerItens(mochila, &quantidade);
                break;
            case 3:
                listarItens(mochila, quantidade);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 0);
    
return 0;
}
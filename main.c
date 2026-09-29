#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Livro {
    int id;
    char titulo[100];
    char autor[100];
};

int main() {
    struct Livro lista[50];
    int quantidade = 0;
    int opcao;

    // Tentando abrir o arquivo pra carregar os dados
    FILE *arquivo = fopen("livros.txt", "r");
    if (arquivo != NULL) {
        while (fscanf(arquivo, "%d;%[^;];%[^\n]\n", &lista[quantidade].id, lista[quantidade].titulo, lista[quantidade].autor) == 3) {
            quantidade++;
        }
        fclose(arquivo);
    }

    do {
        printf("\n--- MENU ---\n");
        printf("1. Listar livros\n");
        printf("2. Cadastrar livro\n");
        printf("0. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            printf("\n--- Lista de Livros ---\n");
            if (quantidade == 0) {
                printf("Nenhum livro cadastrado.\n");
            } else {
                for (int i = 0; i < quantidade; i++) {
                    printf("ID: %d | Titulo: %s | Autor: %s\n", lista[i].id, lista[i].titulo, lista[i].autor);
                }
            }
        } 
        else if (opcao == 2) {
            if (quantidade >= 50) {
                printf("Biblioteca cheia!\n");
            } else {
                printf("\n--- Cadastro ---\n");
                lista[quantidade].id = quantidade + 1;

                printf("Titulo: ");
                fflush(stdin);
                gets(lista[quantidade].titulo);

                printf("Autor: ");
                gets(lista[quantidade].autor);

                FILE *arq = fopen("livros.txt", "a");
                if (arq != NULL) {
                    fprintf(arq, "%d;%s;%s\n", lista[quantidade].id, lista[quantidade].titulo, lista[quantidade].autor);
                    fclose(arq);
                }

                quantidade++;
                printf("Salvo com sucesso!\n");
            }
        } 
        else if (opcao == 0) {
            printf("\nSaindo...\n");
        } 
        else {
            printf("\nOpcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}

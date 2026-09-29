#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Livro {
    int id;
    char titulo[100];
    char autor[100];
};

struct Usuario {
    int id;
    char nome[100];
    char matricula[30];
};

int main() {
    int opcao;
    FILE *f;

    do {
        printf("\n--- MENU BIBLIOTECA ---\n");
        printf("1. Listar livros\n");
        printf("2. Adicionar livro\n");
        printf("3. Listar usuarios\n");
        printf("4. Adicionar usuario\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        if (opcao == 1) {
            f = fopen("livros.txt", "r");
            if (f == NULL) {
                printf("Erro ao abrir livros.txt ou arquivo nao existe.\n");
            } else {
                struct Livro l;
                printf("\n--- LISTA DE LIVROS ---\n");
                while (fscanf(f, "%d;%99[^;];%99[^\n]\n", &l.id, l.titulo, l.autor) == 3) {
                    printf("ID: %d | Titulo: %s | Autor: %s\n", l.id, l.titulo, l.autor);
                }
                fclose(f);
            }
        } else if (opcao == 2) {
            f = fopen("livros.txt", "a");
            if (f == NULL) {
                printf("Erro ao abrir livros.txt para escrita.\n");
            } else {
                struct Livro l;
                printf("\n--- NOVO LIVRO ---\n");
                printf("ID: ");
                scanf("%d", &l.id);
                getchar();

                printf("Titulo: ");
                fgets(l.titulo, sizeof(l.titulo), stdin);
                l.titulo[strcspn(l.titulo, "\n")] = 0;

                printf("Autor: ");
                fgets(l.autor, sizeof(l.autor), stdin);
                l.autor[strcspn(l.autor, "\n")] = 0;

                fprintf(f, "%d;%s;%s\n", l.id, l.titulo, l.autor);
                fclose(f);
                printf("Livro adicionado com sucesso!\n");
            }
        } else if (opcao == 3) {
            f = fopen("usuarios.txt", "r");
            if (f == NULL) {
                printf("Erro ao abrir usuarios.txt ou arquivo nao existe.\n");
            } else {
                struct Usuario u;
                printf("\n--- LISTA DE USUARIOS ---\n");
                while (fscanf(f, "%d;%99[^;];%29[^\n]\n", &u.id, u.nome, u.matricula) == 3) {
                    printf("ID: %d | Nome: %s | Matricula: %s\n", u.id, u.nome, u.matricula);
                }
                fclose(f);
            }
        } else if (opcao == 4) {
            f = fopen("usuarios.txt", "a");
            if (f == NULL) {
                printf("Erro ao abrir usuarios.txt para escrita.\n");
            } else {
                struct Usuario u;
                printf("\n--- NOVO USUARIO ---\n");
                printf("ID: ");
                scanf("%d", &u.id);
                getchar();

                printf("Nome: ");
                fgets(u.nome, sizeof(u.nome), stdin);
                u.nome[strcspn(u.nome, "\n")] = 0;

                printf("Matricula/RA: ");
                fgets(u.matricula, sizeof(u.matricula), stdin);
                u.matricula[strcspn(u.matricula, "\n")] = 0;

                fprintf(f, "%d;%s;%s\n", u.id, u.nome, u.matricula);
                fclose(f);
                printf("Usuario adicionado com sucesso!\n");
            }
        } else if (opcao != 0) {
            printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}

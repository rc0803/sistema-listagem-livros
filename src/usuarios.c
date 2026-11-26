#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "usuarios.h"
#include "livros.h"

static void removerQuebra(char *str) {
    str[strcspn(str, "\r\n")] = '\0';
}

static int stringVazia(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isspace((unsigned char)str[i])) {
            return 0;
        }
    }
    return 1;
}

int encontrarUsuarioPorMatricula(const Usuario usuarios[], int total, const char matricula[]) {
    for (int i = 0; i < total; i++) {
        if (strcmp(usuarios[i].matricula, matricula) == 0) {
            return i;
        }
    }
    return -1;
}

void cadastrarUsuario(Usuario usuarios[], int *total) {
    if (*total >= MAX_USUARIOS) {
        printf("Erro: limite maximo de usuarios atingido.\n");
        return;
    }

    Usuario novo;
    printf("\n--- CADASTRAR USUARIO ---\n");

    printf("Matricula: ");
    if (!fgets(novo.matricula, sizeof(novo.matricula), stdin)) return;
    removerQuebra(novo.matricula);
    if (stringVazia(novo.matricula)) {
        printf("Erro: matricula nao pode ser vazia.\n");
        return;
    }

    // Bloqueia cadastro com matricula ja existente
    if (encontrarUsuarioPorMatricula(usuarios, *total, novo.matricula) != -1) {
        printf("Erro: matricula ja cadastrada.\n");
        return;
    }

    printf("Nome: ");
    if (!fgets(novo.nome, sizeof(novo.nome), stdin)) return;
    removerQuebra(novo.nome);
    if (stringVazia(novo.nome)) {
        printf("Erro: nome nao pode ser vazio.\n");
        return;
    }

    printf("Curso: ");
    if (!fgets(novo.curso, sizeof(novo.curso), stdin)) return;
    removerQuebra(novo.curso);
    if (stringVazia(novo.curso)) {
        printf("Erro: curso nao pode ser vazio.\n");
        return;
    }

    usuarios[*total] = novo;
    (*total)++;
    printf("Usuario cadastrado com sucesso!\n");
}

void listarUsuarios(const Usuario usuarios[], int total) {
    printf("\n--- LISTA DE USUARIOS ---\n");
    if (total == 0) {
        printf("Nenhum usuario cadastrado.\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        printf("Matricula: %s | Nome: %s | Curso: %s\n",
               usuarios[i].matricula,
               usuarios[i].nome,
               usuarios[i].curso);
    }
}

void buscarUsuario(const Usuario usuarios[], int total) {
    char matricula[MAX_MATRICULA];
    printf("\nDigite a matricula do usuario: ");
    if (!fgets(matricula, sizeof(matricula), stdin)) return;
    removerQuebra(matricula);

    if (stringVazia(matricula)) {
        printf("Erro: matricula vazia.\n");
        return;
    }

    int idx = encontrarUsuarioPorMatricula(usuarios, total, matricula);
    if (idx == -1) {
        printf("Usuario nao encontrado.\n");
        return;
    }

    printf("Matricula: %s | Nome: %s | Curso: %s\n",
           usuarios[idx].matricula,
           usuarios[idx].nome,
           usuarios[idx].curso);
}

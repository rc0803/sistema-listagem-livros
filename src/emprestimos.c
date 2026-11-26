#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "emprestimos.h"

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

// So bloqueia se ja houver emprestimo em aberto; apos devolver, o usuario pode pegar de novo
static int jaTemEmprestimoAtivo(const Emprestimo emprestimos[], int total,
                                const char codigoLivro[], const char matriculaUsuario[]) {
    for (int i = 0; i < total; i++) {
        if (strcmp(emprestimos[i].codigoLivro, codigoLivro) == 0 &&
            strcmp(emprestimos[i].matriculaUsuario, matriculaUsuario) == 0 &&
            strcmp(emprestimos[i].status, "Ativo") == 0) {
            return 1;
        }
    }
    return 0;
}

void realizarEmprestimo(Emprestimo emprestimos[], int *totalEmprestimos,
                        Livro livros[], int totalLivros,
                        const Usuario usuarios[], int totalUsuarios) {
    if (*totalEmprestimos >= MAX_EMPRESTIMOS) {
        printf("Erro: limite maximo de emprestimos atingido.\n");
        return;
    }

    char codigoLivro[MAX_CODIGO];
    char matriculaUsuario[MAX_MATRICULA];

    printf("\n--- REALIZAR EMPRESTIMO ---\n");
    printf("Codigo do livro: ");
    if (!fgets(codigoLivro, sizeof(codigoLivro), stdin)) return;
    removerQuebra(codigoLivro);
    if (stringVazia(codigoLivro)) {
        printf("Erro: codigo do livro nao pode ser vazio.\n");
        return;
    }

    printf("Matricula do usuario: ");
    if (!fgets(matriculaUsuario, sizeof(matriculaUsuario), stdin)) return;
    removerQuebra(matriculaUsuario);
    if (stringVazia(matriculaUsuario)) {
        printf("Erro: matricula do usuario nao pode ser vazia.\n");
        return;
    }

    int idxLivro = encontrarLivroPorCodigo(livros, totalLivros, codigoLivro);
    if (idxLivro == -1) {
        printf("Erro: livro inexistente.\n");
        return;
    }

    int idxUsuario = encontrarUsuarioPorMatricula(usuarios, totalUsuarios, matriculaUsuario);
    if (idxUsuario == -1) {
        printf("Erro: usuario inexistente.\n");
        return;
    }

    if (livros[idxLivro].quantidade <= 0) {
        printf("Erro: livro sem exemplares disponiveis.\n");
        return;
    }

    if (jaTemEmprestimoAtivo(emprestimos, *totalEmprestimos, codigoLivro, matriculaUsuario)) {
        printf("Erro: este usuario ja possui este livro emprestado e ativo.\n");
        return;
    }

    Emprestimo novo;
    strcpy(novo.codigoLivro, codigoLivro);
    strcpy(novo.matriculaUsuario, matriculaUsuario);
    strcpy(novo.status, "Ativo");

    emprestimos[*totalEmprestimos] = novo;
    (*totalEmprestimos)++;
    livros[idxLivro].quantidade--;

    printf("Emprestimo realizado com sucesso!\n");
}

void devolverEmprestimo(Emprestimo emprestimos[], int totalEmprestimos,
                        Livro livros[], int totalLivros) {
    char codigoLivro[MAX_CODIGO];
    char matriculaUsuario[MAX_MATRICULA];

    printf("\n--- DEVOLVER LIVRO ---\n");
    printf("Codigo do livro: ");
    if (!fgets(codigoLivro, sizeof(codigoLivro), stdin)) return;
    removerQuebra(codigoLivro);
    if (stringVazia(codigoLivro)) {
        printf("Erro: codigo do livro nao pode ser vazio.\n");
        return;
    }

    printf("Matricula do usuario: ");
    if (!fgets(matriculaUsuario, sizeof(matriculaUsuario), stdin)) return;
    removerQuebra(matriculaUsuario);
    if (stringVazia(matriculaUsuario)) {
        printf("Erro: matricula do usuario nao pode ser vazia.\n");
        return;
    }

    int idxEmp = -1;
    for (int i = 0; i < totalEmprestimos; i++) {
        if (strcmp(emprestimos[i].codigoLivro, codigoLivro) == 0 &&
            strcmp(emprestimos[i].matriculaUsuario, matriculaUsuario) == 0 &&
            strcmp(emprestimos[i].status, "Ativo") == 0) {
            idxEmp = i;
            break;
        }
    }

    if (idxEmp == -1) {
        printf("Erro: emprestimo ativo nao encontrado.\n");
        return;
    }

    // Troca o status sem apagar a linha para manter o historico
    strcpy(emprestimos[idxEmp].status, "Devolvido");

    int idxLivro = encontrarLivroPorCodigo(livros, totalLivros, codigoLivro);
    if (idxLivro != -1) {
        livros[idxLivro].quantidade++;
    }

    printf("Devolucao realizada com sucesso!\n");
}

void listarEmprestimos(const Emprestimo emprestimos[], int totalEmprestimos) {
    printf("\n--- LISTA DE EMPRESTIMOS ---\n");
    if (totalEmprestimos == 0) {
        printf("Nenhum emprestimo registrado.\n");
        return;
    }

    for (int i = 0; i < totalEmprestimos; i++) {
        printf("Livro: %s | Usuario: %s | Status: %s\n",
               emprestimos[i].codigoLivro,
               emprestimos[i].matriculaUsuario,
               emprestimos[i].status);
    }
}

#include <stdio.h>
#include "persistencia.h"

// Caminhos relativos a pasta raiz de onde o binario e executado
#define ARQ_LIVROS "dados/livros.txt"
#define ARQ_USUARIOS "dados/usuarios.txt"
#define ARQ_EMPRESTIMOS "dados/emprestimos.txt"

void carregarDados(Livro livros[], int *totalLivros,
                   Usuario usuarios[], int *totalUsuarios,
                   Emprestimo emprestimos[], int *totalEmprestimos) {
    *totalLivros = 0;
    *totalUsuarios = 0;
    *totalEmprestimos = 0;

    // Usa ';' como separador para permitir espacos dentro de titulos, nomes e cursos
    FILE *fLivros = fopen(ARQ_LIVROS, "r");
    if (fLivros != NULL) {
        Livro l;
        while (*totalLivros < MAX_LIVROS &&
               fscanf(fLivros, "%19[^;];%119[^;];%99[^;];%d;%d\n",
                      l.codigo, l.titulo, l.autor, &l.ano, &l.quantidade) == 5) {
            livros[*totalLivros] = l;
            (*totalLivros)++;
        }
        fclose(fLivros);
    }

    FILE *fUsuarios = fopen(ARQ_USUARIOS, "r");
    if (fUsuarios != NULL) {
        Usuario u;
        while (*totalUsuarios < MAX_USUARIOS &&
               fscanf(fUsuarios, "%24[^;];%99[^;];%79[^\n]\n",
                      u.matricula, u.nome, u.curso) == 3) {
            usuarios[*totalUsuarios] = u;
            (*totalUsuarios)++;
        }
        fclose(fUsuarios);
    }

    FILE *fEmprestimos = fopen(ARQ_EMPRESTIMOS, "r");
    if (fEmprestimos != NULL) {
        Emprestimo e;
        while (*totalEmprestimos < MAX_EMPRESTIMOS &&
               fscanf(fEmprestimos, "%19[^;];%24[^;];%19[^\n]\n",
                      e.codigoLivro, e.matriculaUsuario, e.status) == 3) {
            emprestimos[*totalEmprestimos] = e;
            (*totalEmprestimos)++;
        }
        fclose(fEmprestimos);
    }
}

void salvarDados(const Livro livros[], int totalLivros,
                 const Usuario usuarios[], int totalUsuarios,
                 const Emprestimo emprestimos[], int totalEmprestimos) {
    // Modo "w" reescreve o arquivo inteiro refletindo exclusoes/alteracoes de estoque e status
    FILE *fLivros = fopen(ARQ_LIVROS, "w");
    if (fLivros != NULL) {
        for (int i = 0; i < totalLivros; i++) {
            fprintf(fLivros, "%s;%s;%s;%d;%d\n",
                    livros[i].codigo,
                    livros[i].titulo,
                    livros[i].autor,
                    livros[i].ano,
                    livros[i].quantidade);
        }
        fclose(fLivros);
    }

    FILE *fUsuarios = fopen(ARQ_USUARIOS, "w");
    if (fUsuarios != NULL) {
        for (int i = 0; i < totalUsuarios; i++) {
            fprintf(fUsuarios, "%s;%s;%s\n",
                    usuarios[i].matricula,
                    usuarios[i].nome,
                    usuarios[i].curso);
        }
        fclose(fUsuarios);
    }

    FILE *fEmprestimos = fopen(ARQ_EMPRESTIMOS, "w");
    if (fEmprestimos != NULL) {
        for (int i = 0; i < totalEmprestimos; i++) {
            fprintf(fEmprestimos, "%s;%s;%s\n",
                    emprestimos[i].codigoLivro,
                    emprestimos[i].matriculaUsuario,
                    emprestimos[i].status);
        }
        fclose(fEmprestimos);
    }
}

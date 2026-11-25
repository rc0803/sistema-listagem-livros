#ifndef EMPRESTIMOS_H
#define EMPRESTIMOS_H

#include "livros.h"
#include "usuarios.h"

#define MAX_STATUS 20
#define MAX_EMPRESTIMOS 200

// Mantem o historico mesmo apos devolucao, mudando apenas o status
typedef struct {
    char codigoLivro[MAX_CODIGO];
    char matriculaUsuario[MAX_MATRICULA];
    char status[MAX_STATUS];
} Emprestimo;

void realizarEmprestimo(Emprestimo emprestimos[], int *totalEmprestimos,
                        Livro livros[], int totalLivros,
                        const Usuario usuarios[], int totalUsuarios);
void devolverEmprestimo(Emprestimo emprestimos[], int totalEmprestimos,
                        Livro livros[], int totalLivros);
void listarEmprestimos(const Emprestimo emprestimos[], int totalEmprestimos);

#endif

#ifndef PERSISTENCIA_H
#define PERSISTENCIA_H

#include "livros.h"
#include "usuarios.h"
#include "emprestimos.h"

// Sincroniza os vetores em memoria com os arquivos .txt na pasta dados/
void carregarDados(Livro livros[], int *totalLivros,
                   Usuario usuarios[], int *totalUsuarios,
                   Emprestimo emprestimos[], int *totalEmprestimos);
void salvarDados(const Livro livros[], int totalLivros,
                 const Usuario usuarios[], int totalUsuarios,
                 const Emprestimo emprestimos[], int totalEmprestimos);

#endif

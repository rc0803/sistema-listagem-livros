#ifndef LIVROS_H // Impede redefinicao de structs e macros se incluido mais de uma vez
#define LIVROS_H

#define MAX_CODIGO 20
#define MAX_TITULO 120
#define MAX_AUTOR 100
#define MAX_LIVROS 100

// Identificador unico usado para evitar duplicidade e vincular emprestimos
typedef struct {
    char codigo[MAX_CODIGO];
    char titulo[MAX_TITULO];
    char autor[MAX_AUTOR];
    int ano;
    int quantidade; // Decrementa em emprestimos ativos e volta na devolucao
} Livro;

void cadastrarLivro(Livro livros[], int *total);
void listarLivros(const Livro livros[], int total);
void buscarLivro(const Livro livros[], int total);
int encontrarLivroPorCodigo(const Livro livros[], int total, const char codigo[]);
void limparBuffer(void);

#endif

#include <stdio.h>
#include "livros.h"
#include "usuarios.h"
#include "emprestimos.h"
#include "persistencia.h"

int main(void) {
    Livro livros[MAX_LIVROS];
    Usuario usuarios[MAX_USUARIOS];
    Emprestimo emprestimos[MAX_EMPRESTIMOS];

    int totalLivros = 0;
    int totalUsuarios = 0;
    int totalEmprestimos = 0;

    carregarDados(livros, &totalLivros,
                  usuarios, &totalUsuarios,
                  emprestimos, &totalEmprestimos);

    int opcao;
    do {
        printf("\n--- MENU BIBLIOTECA ---\n");
        printf("1. Cadastrar livro\n");
        printf("2. Listar livros\n");
        printf("3. Buscar livro\n");
        printf("4. Cadastrar usuario\n");
        printf("5. Listar usuarios\n");
        printf("6. Buscar usuario\n");
        printf("7. Realizar emprestimo\n");
        printf("8. Devolver livro\n");
        printf("9. Listar emprestimos\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");

        // Evita loop infinito caso o usuario digite texto em vez de numero
        if (scanf("%d", &opcao) != 1) {
            limparBuffer();
            printf("Opcao invalida!\n");
            opcao = -1;
            continue;
        }
        limparBuffer();

        switch (opcao) {
            case 1:
                cadastrarLivro(livros, &totalLivros);
                salvarDados(livros, totalLivros, usuarios, totalUsuarios, emprestimos, totalEmprestimos);
                break;
            case 2:
                listarLivros(livros, totalLivros);
                break;
            case 3:
                buscarLivro(livros, totalLivros);
                break;
            case 4:
                cadastrarUsuario(usuarios, &totalUsuarios);
                salvarDados(livros, totalLivros, usuarios, totalUsuarios, emprestimos, totalEmprestimos);
                break;
            case 5:
                listarUsuarios(usuarios, totalUsuarios);
                break;
            case 6:
                buscarUsuario(usuarios, totalUsuarios);
                break;
            case 7:
                realizarEmprestimo(emprestimos, &totalEmprestimos,
                                   livros, totalLivros,
                                   usuarios, totalUsuarios);
                salvarDados(livros, totalLivros, usuarios, totalUsuarios, emprestimos, totalEmprestimos);
                break;
            case 8:
                devolverEmprestimo(emprestimos, totalEmprestimos,
                                   livros, totalLivros);
                salvarDados(livros, totalLivros, usuarios, totalUsuarios, emprestimos, totalEmprestimos);
                break;
            case 9:
                listarEmprestimos(emprestimos, totalEmprestimos);
                break;
            case 0:
                salvarDados(livros, totalLivros, usuarios, totalUsuarios, emprestimos, totalEmprestimos);
                printf("Encerrando...\n");
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}

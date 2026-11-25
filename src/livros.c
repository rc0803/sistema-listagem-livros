#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "livros.h"

// Consome sobras ate o '\n' para nao atravessar o proximo fgets
void limparBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

// Corta '\n' e '\r' (comum em arquivos salvos no Windows)
static void removerQuebra(char *str) {
    str[strcspn(str, "\r\n")] = '\0';
}

// Rejeita entradas vazias ou so com espacos/tabs
static int stringVazia(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isspace((unsigned char)str[i])) {
            return 0;
        }
    }
    return 1;
}

// Busca parcial case-insensitive para facilitar encontrar titulos/autores
static int contemTexto(const char *texto, const char *busca) {
    size_t tLen = strlen(texto);
    size_t bLen = strlen(busca);
    if (bLen == 0 || bLen > tLen) {
        return 0;
    }

    for (size_t i = 0; i <= tLen - bLen; i++) {
        size_t j = 0;
        while (j < bLen &&
               tolower((unsigned char)texto[i + j]) == tolower((unsigned char)busca[j])) {
            j++;
        }
        if (j == bLen) {
            return 1;
        }
    }
    return 0;
}

int encontrarLivroPorCodigo(const Livro livros[], int total, const char codigo[]) {
    for (int i = 0; i < total; i++) {
        if (strcmp(livros[i].codigo, codigo) == 0) {
            return i;
        }
    }
    return -1;
}

void cadastrarLivro(Livro livros[], int *total) {
    if (*total >= MAX_LIVROS) {
        printf("Erro: limite maximo de livros atingido.\n");
        return;
    }

    Livro novo;
    printf("\n--- CADASTRAR LIVRO ---\n");

    printf("Codigo: ");
    if (!fgets(novo.codigo, sizeof(novo.codigo), stdin)) return;
    removerQuebra(novo.codigo);
    if (stringVazia(novo.codigo)) {
        printf("Erro: codigo do livro nao pode ser vazio.\n");
        return;
    }

    if (encontrarLivroPorCodigo(livros, *total, novo.codigo) != -1) {
        printf("Erro: ja existe um livro com esse codigo.\n");
        return;
    }

    printf("Titulo: ");
    if (!fgets(novo.titulo, sizeof(novo.titulo), stdin)) return;
    removerQuebra(novo.titulo);
    if (stringVazia(novo.titulo)) {
        printf("Erro: titulo nao pode ser vazio.\n");
        return;
    }

    printf("Autor: ");
    if (!fgets(novo.autor, sizeof(novo.autor), stdin)) return;
    removerQuebra(novo.autor);
    if (stringVazia(novo.autor)) {
        printf("Erro: autor nao pode ser vazio.\n");
        return;
    }

    printf("Ano de publicacao: ");
    // Se scanf falhar (ex: digitar letra), limpa o buffer antes de sair
    if (scanf("%d", &novo.ano) != 1) {
        limparBuffer();
        printf("Erro: ano invalido.\n");
        return;
    }
    limparBuffer();
    if (novo.ano < 0) {
        printf("Erro: o ano de publicacao nao pode ser negativo.\n");
        return;
    }

    printf("Quantidade disponivel: ");
    if (scanf("%d", &novo.quantidade) != 1) {
        limparBuffer();
        printf("Erro: quantidade invalida.\n");
        return;
    }
    limparBuffer();
    if (novo.quantidade < 0) {
        printf("Erro: a quantidade nao pode ser negativa.\n");
        return;
    }

    livros[*total] = novo;
    (*total)++;
    printf("Livro cadastrado com sucesso!\n");
}

void listarLivros(const Livro livros[], int total) {
    printf("\n--- LISTA DE LIVROS ---\n");
    if (total == 0) {
        printf("Acervo vazio.\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        printf("Codigo: %s | Titulo: %s | Autor: %s | Ano: %d | Quantidade: %d\n",
               livros[i].codigo,
               livros[i].titulo,
               livros[i].autor,
               livros[i].ano,
               livros[i].quantidade);
    }
}

void buscarLivro(const Livro livros[], int total) {
    if (total == 0) {
        printf("Acervo vazio.\n");
        return;
    }

    int tipo;
    char termo[MAX_TITULO];

    printf("\nBuscar por: 1 - Titulo | 2 - Autor: ");
    if (scanf("%d", &tipo) != 1) {
        limparBuffer();
        printf("Opcao invalida.\n");
        return;
    }
    limparBuffer();

    if (tipo != 1 && tipo != 2) {
        printf("Opcao de busca invalida.\n");
        return;
    }

    printf("Digite o termo de busca: ");
    if (!fgets(termo, sizeof(termo), stdin)) return;
    removerQuebra(termo);
    if (stringVazia(termo)) {
        printf("Erro: termo de busca vazio.\n");
        return;
    }

    int achou = 0;
    for (int i = 0; i < total; i++) {
        int bateu = (tipo == 1) ? contemTexto(livros[i].titulo, termo)
                              : contemTexto(livros[i].autor, termo);
        if (bateu) {
            printf("Codigo: %s | Titulo: %s | Autor: %s | Ano: %d | Quantidade: %d\n",
                   livros[i].codigo,
                   livros[i].titulo,
                   livros[i].autor,
                   livros[i].ano,
                   livros[i].quantidade);
            achou++;
        }
    }

    if (!achou) {
        printf("Nenhum livro encontrado.\n");
    }
}

#ifndef USUARIOS_H
#define USUARIOS_H

#define MAX_MATRICULA 25
#define MAX_NOME 100
#define MAX_CURSO 80
#define MAX_USUARIOS 100

// Matricula atua como chave unica para validar cadastros e emprestimos
typedef struct {
    char matricula[MAX_MATRICULA];
    char nome[MAX_NOME];
    char curso[MAX_CURSO];
} Usuario;

void cadastrarUsuario(Usuario usuarios[], int *total);
void listarUsuarios(const Usuario usuarios[], int total);
void buscarUsuario(const Usuario usuarios[], int total);
int encontrarUsuarioPorMatricula(const Usuario usuarios[], int total, const char matricula[]);

#endif

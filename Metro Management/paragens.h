// Trabalho Pratico de Programacao 2022/2023
//
// Realizado por: Lucas Caetano a2020132564

//Tamanho maximo
#define MAX 50

#include "utils.h"

//Paragem
typedef struct paragem{
    char nome[MAX];
    char codigo[MAX];
} Paragem;

// Gestao de Paragens
bool validParagem(Paragem* paragens, int nParagens, const char* nome, const char* codigo);
char* geraCodigo(Paragem* paragens, int nParagens);
void imprimirParagens(Paragem* paragens, int nParagens);


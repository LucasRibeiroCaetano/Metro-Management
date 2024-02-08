// Trabalho Pratico de Programacao 2022/2023
//
// Realizado por: Lucas Caetano a2020132564

#include "paragens.h"

// Verificar se uma paragem existe no sistema
bool validParagem(Paragem* paragens, int nParagens, const char* nome, const char* codigo) {

    // Verificacao sem codigo
    if(codigo == NULL){

        for (int i = 0; i < nParagens; i++) {

            // A paragem existe
            if (strcmp(nome, paragens[i].nome) == 0)
                return true;
        }

        // A paragem nao existe
        return false;
    }

    // Verificacao com codigo

    // Verificar se a paragem existe
    for (int i = 0; i < nParagens; i++) {

        // A paragem existe
        if (strcmp(nome, paragens[i].nome) == 0 && strcmp(codigo, paragens[i].codigo) == 0) {
            return true;
        }
    }

    // A paragem nao existe
    return false;
}

// Imprime todas as paragens no sistema
void imprimirParagens(Paragem* paragens, int nParagens) {
    printf("\n==| Paragens |==\n\n");
    printf("Numero de paragens: %d\n\n", nParagens);

    for (int i = 0; i < nParagens; i++)
        printf("(%d) - Paragem %s: %s\n", i+1, paragens[i].codigo, paragens[i].nome);
}

// Funcao para gerar um codigo unico
char* geraCodigo(Paragem* paragens, int nParagens) {
    char codigo[MAX];
    int codigo_existe = 1;

    while (codigo_existe) {

        // Gera um código aleatório
        codigo[0] = 'A' + rand() % 26; // Letra maiúscula aleatória

        for (int i = 1; i < 4; i++)
            codigo[i] = '0' + rand() % 10; // Número aleatório de 0 a 9

        // Caractere nulo para indicar o fim da string
        codigo[4] = '\0';

        // Verifica se o código já existe
        codigo_existe = 0;

        for (int i = 0; i < nParagens; i++) {
            if (!strcmp(paragens[i].codigo, codigo)) {
                codigo_existe = 1;
                break;
            }
        }
    }

    // Devolve uma cópia do código
    return strdup(codigo);
}

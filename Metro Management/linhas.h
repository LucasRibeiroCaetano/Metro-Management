// Trabalho Pratico de Programacao 2022/2023
//
// Realizado por: Lucas Caetano a2020132564

//Tamanho maximo
#define MAX 50

#include "paragens.h"

//Linha
typedef struct linha {
    char nome[MAX];
    Paragem* paragens;
    int nParagens;
    struct linha* prox;
} Linha;

// Gestao de Linhas
int contaLinhas(const char* fileName);
bool linhaExiste(Linha* head, const char* nome);
Linha* criarLinha(const char* nome, int n);
Linha* adicionarLinha(Linha* head, const char* nome, int n);
Linha* encontrarLinha(Linha* head, const char* nome);
void imprimirLinhas(Linha* head);
void mostraSequencia(Linha* linha);
void removeParagemLinha(Linha* head, const char* nomeParagem);
void removeParagem(Linha* linha, const char* nome);
void freeLista(Linha* head);
void imprimirParagensLinha(Linha* linha);
bool paragemExiste(Linha* linha, const char* nome);
int indexParagem(Linha* linha, Paragem* paragens, int nParagens, const char* nome);

// Ficheiro Binario
void save(Linha* head, Paragem* paragens, int nParagens);
Linha* load(int* nParagens, Paragem** paragens);

// Calculo de Percursos
void calcPercursos(Linha* head, char* origem, char* destino);
void imprimeRota(Linha* linha, char* origem, char* destino);

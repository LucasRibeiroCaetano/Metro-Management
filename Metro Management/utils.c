// Trabalho Pratico de Programacao 2022/2023
//
// Realizado por: Lucas Caetano a2020132564

#include "utils.h"


int menu() {

    int num;

    printf("\n==| Menu de Gestao |==\n\n");
    printf("Operacoes de Paragens:\n  (1): Registar Paragens\n  (2): Eliminar Paragens\n  (3): Visualizar Paragens\n\nOperacoes de Linhas:\n  (4): Adicionar Linhas\n  (5): Atualizar Linha\n  (6): Visualizar Linhas\n\nOutras Operacoes:\n  (7): Calculo de Percursos\n  (8): Sair\n\n");

    do {
        printf("======================\nEscolha uma Opcao: ");

        if (scanf_s("%d", &num) != 1) {
            printf("Entrada invalida. Tente novamente...\n");

            // Limpa o buffer de entrada
            while (getchar() != '\n');
        }

            //Trata se de um numero -> verificar se esta entre 1 e 7
        else if (num < 1 || num > 8) {
            printf("Opcao invalida. Tente novamente...\n");

            // Limpa o buffer de entrada
            while (getchar() != '\n');
        }
    } while (num < 1 || num > 8);

    return num;
}

int lerOpcao() {
    int opcao;

    printf("\nEscolha uma opcao, 1 ou 2: ");

    while(scanf("%d", &opcao) != 1 || (opcao != 1 && opcao != 2)){
        printf("Opcao Invalida. Tente Novamente: ");
        while(getchar() != '\n');
    }

    return opcao;
}

char* removeEspaco(char* str){
    char* end;

    // Remover espaços extras no início da string
    while (isspace((unsigned char)*str))
        str++;

    // Caso a string esteja vazia após a remoção dos espaços
    if (*str == '\0')
        return str;

    // Remover espaços extras no final da string
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
        end--;

    // Adicionar o caractere nulo de terminação após o último caractere válido
    *(end + 1) = '\0';

    return str;
}

bool fileExists(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file) {
        fclose(file);
        return true;
    }
    return false;
}

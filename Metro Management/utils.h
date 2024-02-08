// Trabalho Pratico de Programacao 2022/2023
//
// Realizado por: Lucas Caetano a2020132564

#define BUFFER_SIZE 4096

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <signal.h>

int menu();
char* removeEspaco(char* str);
int lerOpcao();
bool fileExists(const char* filename);

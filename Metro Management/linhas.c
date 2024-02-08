// Trabalho Pratico de Programacao 2022/2023
//
// Realizado por: Lucas Caetano a2020132564

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err34-c"
#pragma ide diagnostic ignored "bugprone-suspicious-realloc-usage"
#pragma ide diagnostic ignored "cert-msc50-cpp"
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"
#include "utils.h"
#include "linhas.h"

// Imprime as paragens de uma linha
void imprimirParagensLinha(Linha* linha) {

    printf("\n\n============================================");
    printf("\nLinha: %s\n", linha->nome);
    printf("\nNumero de paragens: %d\n\n", linha->nParagens);

    for (int i = 0; i < linha->nParagens; i++)
        printf("Paragem %d: %s # %s\n", i + 1, linha->paragens[i].nome, linha->paragens[i].codigo);

    mostraSequencia(linha);
    printf("============================================");
}

// Contar o numero de paragens no ficheiro de texto (equivalente a contar as linhas menos a primeira)
int contaLinhas(const char* fileName){

    FILE* arquivo = fopen(fileName, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");

        // Retorna um valor negativo para indicar erro
        return -1;
    }

    char linha[MAX];
    int contador = 0;

    // Ignora a primeira linha
    if (fgets(linha, sizeof(linha), arquivo) == NULL) {
        fclose(arquivo);

        // Retorna -1 se o arquivo estiver vazio
        return -1;
    }

    // Conta as linhas após a primeira
    for (; fgets(linha, sizeof(linha), arquivo) != NULL; contador++) {}

    fclose(arquivo);

    return contador;
}

// Verifica se uma linha existe na lista ligada
bool linhaExiste(Linha* head, const char* nome) {
    Linha* atual = head;

    // Nao existem linhas no sistema
    if(atual == NULL)
        return false;

    while (atual != NULL) {

        // A linha existe na lista
        if (strcmp(atual->nome, nome) == 0)
            return true;

        atual = atual->prox;
    }

    // A linha não existe na lista
    return false;
}

Linha* criarLinha(const char* nome, int n) {

    Linha* novaLinha = (Linha*)malloc(sizeof(Linha) * n);
    novaLinha->paragens = malloc(sizeof(Paragem));
    novaLinha->nParagens = 0;

    strcpy(novaLinha->nome, nome);

    return novaLinha;
}

// Utiliza a funcao criarLinha para criar e adicionar uma linha à lista ligada, devolve a head da lista
Linha* adicionarLinha(Linha* head, const char* nome, int n) {
    Linha* novaLinha = criarLinha(nome, n);

    // A lista está vazia -> a nova linha vai ser a head
    if (head == NULL){
        novaLinha->prox = NULL;
        return novaLinha;
    }


    Linha* atual = head;

    // Chegar até ao fim da lista
    while (atual->prox != NULL)
        atual = atual->prox;

    // Adicionar a nova linha ao fim
    atual->prox = novaLinha;
    novaLinha->prox = NULL;
    return head;
}

Linha* encontrarLinha(Linha* head, const char* nome) {
    Linha* atual = head;
    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            return atual; // Retorna o ponteiro para a linha encontrada
        }
        atual = atual->prox;
    }
    return NULL; // Retorna NULL se a linha não for encontrada
}

// Percorre todas as linhas, se uma linha tiver essa paragem e apagada a paragem do array de paragens dessa linha
void removeParagemLinha(Linha* head, const char* nomeParagem) {
    Linha* atual = head;

    // Para todas as paragens
    while (atual != NULL) {

        // Se a paragem existir nesta linha
        if (atual->paragens != NULL && paragemExiste(atual, nomeParagem)) {
            int index = -1;

            // Se a paragem for encontrada o seu indice e colocado na variavel index
            for (int i = 0; i < atual->nParagens; i++) {
                if (strcmp(atual->paragens[i].nome, nomeParagem) == 0) {
                    index = i;
                    break;
                }
            }

            // Se o índice for válido, remover a paragem
            if (index != -1) {
                // Deslocar as paragens à direita do índice para a esquerda
                for (int i = index; i < atual->nParagens - 1; i++) {
                    strcpy(atual->paragens[i].nome, atual->paragens[i + 1].nome);
                    strcpy(atual->paragens[i].codigo, atual->paragens[i + 1].codigo);
                }

                // Redimensionar o array de paragens
                atual->paragens = (Paragem*)realloc(atual->paragens, (atual->nParagens - 1) * sizeof(Paragem));
                atual->nParagens--;
            }
        }

        // Se a paragem nao existir nesta linha passamos para a proxima linha
        atual = atual->prox;
    }
}

// Remove uma paragem de uma linha
void removeParagem(Linha* linha, const char* nome){

    Linha* atual = linha;

    // Se a paragem existir nesta linha
    if (atual->paragens != NULL && paragemExiste(atual, nome)) {
        int index = -1;

        // Se a paragem for encontrada o seu indice e colocado na variavel index
        for (int i = 0; i < atual->nParagens; i++) {
            if (strcmp(atual->paragens[i].nome, nome) == 0) {

                printf("\nEncontrei a paragem %s com o indice: %d", atual->paragens[i].nome, i);
                index = i;
                break;
            }
        }

        // Se o índice for válido, remover a paragem
        if (index != -1) {
            // Deslocar as paragens à direita do índice para a esquerda
            for (int i = index; i < atual->nParagens - 1; i++) {

                printf("\nA copiar %s para %s", atual->paragens[i + 1].nome, atual->paragens[i].nome);
                strcpy(atual->paragens[i].nome, atual->paragens[i + 1].nome);
                strcpy(atual->paragens[i].codigo, atual->paragens[i + 1].codigo);
            }

            // Redimensionar o array de paragens
            atual->paragens = (Paragem*)realloc(atual->paragens, (atual->nParagens - 1) * sizeof(Paragem));
            atual->nParagens--;
        }
    }
}

// Imprime a informacao sobre as linhas
void imprimirLinhas(Linha* head) {
    Linha* atual = head;
    while (atual != NULL) {
        if (atual->nParagens == 0) {
            printf("\n\n============================================");
            printf("\n%s: Sem paragens.\n", atual->nome);
            printf("============================================\n\n");
            atual = atual->prox;
            continue;
        }
        imprimirParagensLinha(atual);
        atual = atual->prox;
    }
}

// Mostra a sequencia de paragens de uma linha
void mostraSequencia(Linha* linha){

    if(linha == NULL){
        printf("\nLinha Vazia...\n");
        return;
    }

    printf("\nSequencia:\n");

    // Ida
    printf(" - Ida:   ");
    for (int i = 0; i < linha->nParagens; i++) {
        printf("%s", linha->paragens[i].nome);
        if (i < linha->nParagens - 1) {
            printf(" -> ");
        }
    }
    printf("\n");

    // Volta
    printf(" - Volta: ");
    for (int i = linha->nParagens - 1; i >= 0; i--) {
        printf("%s", linha->paragens[i].nome);
        if (i > 0) {
            printf(" -> ");
        }
    }
    printf("\n");
}

// Liberta a memoria de todas as linhas
void freeLista(Linha* head) {
    Linha* atual = head;

    while (atual != NULL) {
        Linha* proximo = atual->prox;

        // Libera o array de paragens da linha atual
        free(atual->paragens);

        // Libera a linha atual
        free(atual);

        atual = proximo;
    }
}

// Verificar se uma paragem existe numa linha
bool paragemExiste(Linha* linha, const char* nome) {
    if (linha == NULL || linha->paragens == NULL)
        return false;

    for (int i = 0; i < linha->nParagens; i++)
        if (strcmp(linha->paragens[i].nome, nome) == 0)
            return true; // Paragem encontrada

    // Paragem não encontrada
    return false;
}

// Devolve o index de uma determinada paragem
int indexParagem(Linha* linha, Paragem* paragens, int nParagens, const char* nome) {

    // Opcao para devolver o indice da paragem no sistema
    if(linha == NULL){
        for (int i = 0; i < nParagens; i++) {
            if (strcmp(paragens[i].nome, nome) == 0) {

                // retorna o índice da paragem encontrada
                return i;
            }
        }

        // Paragem nao encontrada
        return -1;
    }

        // Devolver o indice da paragem na linha
    else{
        for (int i = 0; i < linha->nParagens; i++) {
            if (strcmp(linha->paragens[i].nome, nome) == 0) {

                // retorna o índice da paragem encontrada
                return i;
            }
        }

        // Paragem nao encontrada
        return -1;
    }
}


//-------------------------------| Ficheiro Binario |---------------------------------------

void save(Linha* head, Paragem* paragens, int nParagens) {
    FILE* f = fopen("save", "wb");

    if (f == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return;
    }

    // Escrever o número de paragens no arquivo
    fwrite(&nParagens, sizeof(int), 1, f);

    // Escrever as informações de cada paragem no arquivo
    for (int i = 0; i < nParagens; i++) {
        Paragem* paragem = &(paragens[i]);
        fwrite(paragem->nome, sizeof(char), MAX, f);
        fwrite(paragem->codigo, sizeof(char), MAX, f);
    }

    Linha* atual = head;

    while (atual != NULL) {
        // Escrever o nome da linha no arquivo
        fwrite(atual->nome, sizeof(char), MAX, f);

        // Escrever o número de paragens da linha no arquivo
        fwrite(&(atual->nParagens), sizeof(int), 1, f);

        // Escrever a informacao de cada paragem da linha
        for (int i = 0; i < atual->nParagens; i++) {
            fwrite(atual->paragens[i].nome, sizeof(char), MAX, f);
            fwrite(atual->paragens[i].codigo, sizeof(char), MAX, f);
        }

        atual = atual->prox;
    }

    fclose(f);
}

Linha* load(int* nParagens, Paragem** paragens) {

    FILE* f = fopen("save", "rb");

    if (f == NULL) {
        printf("Erro ao abrir o arquivo\n");
        exit(EXIT_FAILURE);
    }

    // Ler o numero de paragens
    fread(nParagens, sizeof(int), 1, f);

    *paragens = malloc((*nParagens) * sizeof(Paragem));

    // Ler as informações de cada paragem
    for (int i = 0; i < (*nParagens); i++) {
        fread((*paragens)[i].nome, sizeof(char), MAX, f);
        fread((*paragens)[i].codigo, sizeof(char), MAX, f);
    }

    Linha* head = NULL;
    Linha* atual = NULL;

    for(;;) {
        Linha* linha = malloc(sizeof(Linha));

        if (fread(linha->nome, sizeof(char), MAX, f) != MAX ||
            fread(&(linha->nParagens), sizeof(int), 1, f) != 1) {
            free(linha);
            break;
        }

        linha->paragens = malloc(linha->nParagens * sizeof(Paragem));

        for (int i = 0; i < linha->nParagens; i++) {
            fread(linha->paragens[i].nome, sizeof(char), MAX, f);
            fread(linha->paragens[i].codigo, sizeof(char), MAX, f);
        }

        linha->prox = NULL;

        if (head == NULL) {
            head = linha;
            atual = linha;
        } else {
            atual->prox = linha;
            atual = linha;
        }
    }

    fclose(f);

    return head;
}



//-------------------------------| Calculo de Percursos |---------------------------------------

void calcPercursos(Linha* head, char* origem, char* destino){

    if(head == NULL){
        printf("\nLista Vazia...\n");
        exit(EXIT_FAILURE);
    }

    Linha* atual = head;
    int flag = false;

    printf("\n\n=================================================");
    printf("\n==| Calculo de Percursos Sem Mudanca de Linha |==");

    // ? Sem mudanca de linha
    while (atual != NULL) {

        // Verificar se ambas as paragens existem na linha
        if (paragemExiste(atual, origem) && paragemExiste(atual, destino)) {
            flag = true;
            imprimeRota(atual, origem, destino);
        }

        atual = atual->prox;
    }

    // Nao ha percursos numa unica linha
    if(!flag){
        printf("\n\nSem percursos disponiveis...\n");
    }

    // ? Com mudanca de linha

    // Linha Inicial
    atual = head;

    // Linha onde efetuamos o transbordo
    Linha* it = head;
    flag = false;

    printf("\n=================================================");
    printf("\n==| Calculo de Percursos Com Mudanca de Linha |==\n");

    // Para todas as linhas
    while(atual != NULL){

        // A linha tem a PO
        if(paragemExiste(atual, origem)){

            for(int i = (indexParagem(atual, NULL, 0, origem) + 1); i < atual->nParagens; i++){

                // Para as linhas possiveis para transbordo
                while(it != NULL){

                    // Saltar a linha inicial
                    if(!strcmp(it->nome, atual->nome)){
                        it = it->prox;
                        continue;
                    }

                    // Esta linha tem uma das paragens para efetuar mudanca de linha
                    if(paragemExiste(it, atual->paragens[i].nome)){

                        // ? i vai ser o índice da paragem de transbordo
                        // Se tiver a paragem destino, e uma linha valida para fazer mudanca de linha
                        if(paragemExiste(it, destino)){

                            flag = true;

                            printf("\n\n - Linha Inicial: %s", atual->nome);
                            printf("\n - Origem: %s", origem);
                            printf("\n - Destino: %s", destino);

                            printf("\n - Percurso: ");

                            // Origem -> Transbordo
                            for(int j = indexParagem(atual, NULL, 0, origem); j <= i; j++)
                                printf("%s -> ", atual->paragens[j].nome);

                            printf("Mudanca de Linha -> ");

                            // Transbordo -> Destino
                            for (int j = indexParagem(it, NULL, 0, atual->paragens[i].nome) + 1; j < indexParagem(it, NULL, 0, destino); j++)
                                printf("%s -> ", it->paragens[j].nome);

                            printf("%s", it->paragens[indexParagem(it, NULL, 0, destino)].nome);
                        }
                    }

                    it = it->prox;
                }
            }
        }

        atual = atual->prox;
    }

    // Nao ha percursos com mudanca de linha
    if(!flag)
        printf("\nSem percursos disponiveis...\n");

    printf("\n\n=================================================\n\n");
}

// Imprime rota sem mudanca de linha
void imprimeRota(Linha* linha, char* origem, char* destino){

    if(linha == NULL){
        printf("Linha vazia.");
        return;
    }

    int j = 0, k = 0;

    printf("\n\n - Linha: %s", linha->nome);
    printf("\n - Origem: %s", origem);
    printf("\n - Destino: %s", destino);

    for(int i = 0; i < linha->nParagens; i++){

        // Se for a paragem de origem registar o indice
        if(!strcmp(linha->paragens[i].nome, origem))
            j = i;

        // Se for a paragem de destino registar o indice
        if(!strcmp(linha->paragens[i].nome, destino))
            k = i;
    }

    // Imprime a rota entre a estacao origem e a estacao destino
    printf("\n - Percurso: ");
    for(; j <= k; j++){

        // Se estivermos na ultima paragem
        if(j == k)
            printf("%s", linha->paragens[j].nome);
        else
            printf("%s -> ", linha->paragens[j].nome);
    }

    putchar('\n');
}




#pragma clang diagnostic pop
// Trabalho Pratico de Programacao 2022/2023
//
// Realizado por: Lucas Caetano a2020132564

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err34-c"
#pragma ide diagnostic ignored "bugprone-suspicious-realloc-usage"

#include "utils.h"
#include "linhas.h"

int main() {

    int num, nParagens = 0;

    // Array dinamico de estruturas que guarda todas as paragens (e criado com tamanho para uma paragem)
    Paragem* paragens = (Paragem*)malloc(sizeof(Paragem));

    // Início da lista ligada
    Linha* head = NULL;

    if (paragens == NULL) {
        printf("[Inicializa Paragens]: Erro ao alocar memoria para o array das paragens.\n");
        return 1;
    }

    printf("==| Trabalho Pratico Programacao 2022/2023 - Metro Mondego |==\n\n");

    // Se existir um save guardado
    if(fileExists("save")){
        printf("Existe uma save guardada. Deseja carregar os dados (1) - Sim | (2) - Nao? ");
        int q = lerOpcao();

        // Carrega as configuracoes
        if(q == 1)
            head = load(&nParagens, &paragens);
    }

    while(1) {

        num = menu();

        // Registar Paragem
        if (num == 1) {

            int q1, k;
            char nome[MAX];

            printf("Quantas paragens deseja adicionar ao sistema? ");
            while(getchar() != '\n');
            while (scanf("%d", &q1) != 1 || q1 < 0) {
                printf("Por favor introduza um numero... Tente Novamente: ");
                while (getchar() != '\n');
            }

            // Realocar memoria para todas as paragens
            paragens = (Paragem*)realloc(paragens, (sizeof(Paragem) * (nParagens + q1)));

            if (paragens == NULL) {
                printf("\n[Registar Paragens]: Erro ao realocar memoria para o array paragens.");
                return 1;
            }

            putchar('\n');

            k = 0;

            for (int i = nParagens; i < nParagens + q1; i++) {

                printf("[Paragem %d]: Insira o nome da paragem que deseja adicionar ao sistema: ", ++k);
                while (getchar() != '\n');
                while (scanf("%[^\n]", nome) != 1 || atoi(nome) != 0 || (validParagem(paragens, nParagens + q1, nome, NULL) == true)) {
                    printf("Nome invalido. Tente Novamente: ");
                    while (getchar() != '\n');
                }
                strcpy(paragens[i].nome, nome);

                // Gera codigo
                strcpy(paragens[i].codigo, geraCodigo(paragens, nParagens));
            }

            nParagens += q1;
        }

        // Eliminar Paragem
        else if (num == 2) {

            char q2[MAX];

            printf("Insira o nome da paragem que deseja eliminar: ");
            while(getchar() != '\n');
            while (scanf("%[^\n]", q2) != 1 || atoi(q2) != 0) {

                printf("Nome invalido. Tente Novamente: ");
                while (getchar() != '\n');
            }

            // Eliminar a paragem do sistema
            for (int i = 0; i < nParagens; i++) {


                if (!strcmp(paragens[i].nome, q2))
                    for (; i < nParagens; i++)
                        paragens[i] = paragens[i + 1];
            }
            nParagens--;

            // Se houver linhas com esta paragem, a paragem e removida do seu array paragens
            removeParagemLinha(head, q2);
        }

        // Visualizar Paragem
        else if (num == 3)
            imprimirParagens(paragens, nParagens);

        // Adicionar Linha
        else if (num == 4) {

            int opcao;
            char fileName[MAX];
            FILE *f;

            printf("\nPode adicionar linhas de duas formas: (1) Manual, (2) Ler de um ficheiro de texto.\n");
            opcao = lerOpcao();

            // Manual
            if(opcao == 1){

                char nome[MAX];
                int n, res2, op;
                Linha* tmp;

                printf("\nQual o nome da linha que deseja criar? ");
                while(getchar() != '\n');
                while(scanf("%[^\n]", nome) != 1 || atoi(nome) != 0 || linhaExiste(head, nome) == true){
                    printf("Escolhe um nome valido: ");
                    while(getchar() != '\n');
                }

                if(nParagens == 0){

                    printf("Nao existem paragens. Deseja criar a linha sem paragens (1) - Sim | (2) - Nao? ");
                    op = lerOpcao();

                    // Nao criar a linha e voltar para o menu inicial
                    if(op == 2)
                        continue;

                        // Criar a linha sem paragens e voltar para o menu inicial
                    else{
                        head = adicionarLinha(head, nome, 1);
                        continue;
                    }
                }

                printf("Existem %d paragens. Quantas quer adicionar a linha? ", nParagens);
                while(getchar() != '\n');
                while(scanf("%d", &n) != 1 || n < 0 || n > nParagens){

                    printf("Numero de paragens invalido. Tenta novamente: ");
                    while(getchar() != '\n');

                }

                if(n == 0){
                    head = adicionarLinha(head, nome, 1);
                    continue;
                }

                head = adicionarLinha(head, nome, n);

                tmp = encontrarLinha(head, nome);

                tmp->nParagens = n;

                // Realocamos memoria para o numero de paragens que queremos adicionar
                tmp->paragens = (Paragem*)realloc(tmp->paragens, sizeof(Paragem) * n);

                imprimirParagens(paragens, nParagens);

                printf("\nEscolha os codigos das paragens que quer adicionar.\n");

                for(int i = 0; i < n; i++){

                    printf("[Paragem %d] Numero: ", i + 1);
                    while(scanf("%d", &res2) != 1 || res2 <= 0 || res2 > nParagens || (paragemExiste(tmp, paragens[res2-1].nome) == true)){
                        printf("\nInsira um numero valido: ");
                        while(getchar() != '\n');
                    }

                    res2--;

                    strcpy(tmp->paragens[i].nome, paragens[res2].nome);
                    strcpy(tmp->paragens[i].codigo, paragens[res2].codigo);
                }

            } // if Manual

                // Ficheiro
            else{

                Linha* atual;
                int nLinhas;
                char buffer1[BUFFER_SIZE];

                printf("\nInsira o nome do ficheiro que quer ler: ");

                while (getchar() != '\n');

                fgets(fileName, MAX, stdin);
                fileName[strcspn(fileName, "\n")] = '\0';
                if ((f = fopen(fileName, "r")) == NULL) {
                    perror("\n[Adicionar Linha (f)]: Erro ao abrir o ficheiro.\nInformacao Adicional: ");
                    fclose(f);
                    free(paragens);
                    return 1;
                }

                // Ler o nome da Linha
                char linhaNome[MAX];
                if (fgets(linhaNome, MAX, f) == NULL) {
                    printf("\n[Adicionar Linha (f)]: Erro ao ler o nome da Linha do ficheiro.\n");
                    fclose(f);
                    free(paragens);
                    return 1;
                }

                // Remover a quebra de linha do nome da linha
                linhaNome[strcspn(linhaNome, "\n")] = '\0';

                if(linhaExiste(head, linhaNome) == true){
                    printf("\nA linha ja existe... Regressando ao menu principal.\n");
                    continue;
                }

                nLinhas = contaLinhas(fileName);

                head = adicionarLinha(head, linhaNome, nLinhas);

                atual = head;

                // Encontrar o node da nova linha
                while (atual != NULL) {
                    if (!strcmp(atual->nome, linhaNome))
                        break;

                    atual = atual->prox;
                }



                atual->nParagens = nLinhas;
                atual->paragens = (Paragem*)realloc(atual->paragens, sizeof(Paragem) * atual->nParagens);

                int     flag = 0,           // 1 - Adicionar as paragens que estao no ficheiro de texto ao sistema | 2 - Nao adicionar
                parEmpty;           // 1 - Nao havia paragens no sistema | 2 - Havia paragens no sistema

                // Opcao de adicionar diretamente as paragens que estao no ficheiro de texto se
                // nao houver no sistema (uma questao de conveniencia para nao estar a adicionar
                // sempre todas as paragens manualmente)
                if(nParagens == 0){

                    int d;
                    printf("\nNao existem paragens no sistema. Deseja adicionar as que estao no ficheiro de texto (1) - Sim | (2) - Nao? ");
                    d = lerOpcao();

                    if(d == 2){
                        printf("\nAs paragens que estao no ficheiro nao existem. A terminar o programa...\n\n");
                        free(paragens);
                        return 1;
                    }

                        // Adicionar as paragens que estao no ficheiro de texto ao sistema
                    else{
                        flag = 1;
                        parEmpty = 1;
                        paragens = (Paragem*)realloc(paragens, sizeof(Paragem) * nLinhas);
                    }
                }

                    // Existem paragens
                else{
                    int d;

                    parEmpty = 0;

                    printf("Quer adicionar as paragens do ficheiro ao sistema (1) - Sim | (2) - Nao? ");
                    d = lerOpcao();

                    if(d == 1){
                        flag = 1;
                        paragens = realloc(paragens, sizeof(Paragem) * (nParagens + nLinhas));
                    }
                }

                // Variaveis para o while
                int i = 0, j = nParagens;
                char nome[MAX];
                char codigo[MAX];

                // Para todas as linhas do ficheiro
                while (fgets(buffer1, BUFFER_SIZE, f) != NULL) {

                    // Le todos os caracteres antes do primeiro # para a primeira string e todos os caracteres apos o # para a segunda string
                    if (sscanf_s(buffer1, " %[^#]#%s", nome, sizeof(nome), codigo, sizeof(codigo)) != 2) {
                        printf("\n[Adicionar Linha (f)]: Erro ao ler uma paragem do ficheiro.\n");
                        fclose(f);
                        free(paragens);
                        return 1;
                    }

                    strcpy(nome, removeEspaco(nome));

                    // Adicionar as paragens do ficheiro para o sistema
                    if(flag) {

                        // Nao havia paragens comecamos do inicio
                        if(parEmpty){

                            nParagens++;
                            strcpy(paragens[i].nome, nome);
                            strcpy(paragens[i].codigo, codigo);
                        }

                            // Havia paragens entao comecamos da ultima
                        else{

                            nParagens++;
                            strcpy(paragens[j].nome, nome);
                            strcpy(paragens[j].codigo, codigo);

                        }
                    }

                    strcpy(atual->paragens[i].nome, nome);
                    strcpy(atual->paragens[i].codigo, codigo);

                    i++;
                    j++;
                }


            } // else Ficheiro
        } // fim opcao 4

        // Atualizar Linha
        else if (num == 5) {
            char nome[MAX];
            int op;
            Linha* tmp;

            printf("Qual linha deseja atualizar? ");
            while(getchar() != '\n');
            while(scanf("%[^\n]", nome) != 1 || linhaExiste(head, nome) == false){
                printf("A linha que inseriu nao e valida ou nao existe. Linha: %s. Tente novamente: ", nome);
                while(getchar() != '\n');
            }

            tmp = encontrarLinha(head, nome);

            printf("\n(1) Para atualizar a sequencia de paragens. (2) Para adicionar paragens a linha. (3) Para remover paragens da linha.\n\nEscolha uma opcao: ");
            while(getchar() != '\n');
            while(scanf("%d", &op) != 1 || (op != 1 && op != 2 && op != 3)){
                printf("Insira uma opcao valida: ");
                while(getchar() != '\n');
            }

            // Atualizar a sequencia de paragens
            if(op == 1){

                if(tmp->nParagens == 0){
                    printf("Esta linha nao tem paragens. Regressando ao menu principal.");
                    continue;
                }

                char qn[MAX];

                // Mostrar a sequencia atual
                mostraSequencia(tmp);

                putchar('\n');

                printf("\nQual quer que seja a nova sequencia?\n");
                int index, n;

                // Par
                if(tmp->nParagens % 2 == 0)
                    n = tmp->nParagens * 2;

                // Impar
                else
                    n = (tmp->nParagens * 2) - 1;

                // Para todas as paragens, verificar se existem
                for(int i = 0; i < n; i++){
                    printf("\n[Paragem %d]: ", i + 1);
                    while(getchar() != '\n');
                    while(scanf("%[^\n]", qn) != 1 || validParagem(paragens, nParagens, qn, NULL) == false){
                        printf("Insira uma paragem valida. Tente novamente: ");
                        while(getchar() != '\n');
                    }

                    index = indexParagem(NULL, paragens, nParagens, qn);

                    strcpy(tmp->paragens[i].nome, paragens[index].nome);
                    strcpy(tmp->paragens[i].codigo, paragens[index].codigo);
                }
            }

                // Adicionar paragens a linha
            else if(op == 2){

                int n, q52;

                imprimirParagens(paragens, nParagens);

                printf("\nDeseja adicionar quantas paragens a linha: ");
                while(getchar() != '\n');
                while(scanf("%d", &q52) != 1 || q52 < 0){

                    printf("Insira um numero valido: ");
                    while(getchar() != '\n');
                }

                // O array paragens esta vazio
                if(tmp->paragens == NULL){
                    tmp->paragens = (Paragem*)malloc(sizeof(Paragem) * q52);
                }
                else{
                    tmp->paragens = (Paragem*)realloc(tmp->paragens, (sizeof(Paragem) * (tmp->nParagens + q52)));
                }


                printf("\nEscolha os codigos das paragens que quer adicionar: \n");

                int j = 0, k = tmp->nParagens;
                tmp->nParagens += q52;

                // Para cada paragem
                for(int i = 0; i < q52; i++){

                    printf("[Paragem %d] Numero: ", ++j);
                    while(scanf("%d", &n) != 1 || n <= 0 || n > nParagens || (paragemExiste(tmp, paragens[n-1].nome) == true)){
                        printf("\nInsira um numero valido: ");
                        while(getchar() != '\n');
                    }

                    strcpy(tmp->paragens[k].nome, paragens[n - 1].nome);
                    strcpy(tmp->paragens[k].codigo, paragens[n - 1].codigo);

                    imprimirParagensLinha(tmp);

                    k++;
                }

                tmp->nParagens += q52;
            }

            // Remover paragens da linha
            else {

                int n, q53;

                printf("Quantas paragens quer remover da linha? ");

                printf("\nnParagens: %d\n", tmp->nParagens);
                while(scanf("%d", &q53) != 1 || q53 < 1 || q53 > tmp->nParagens){
                    printf("\nInsira um numero valido: ");
                    while(getchar() != '\n');
                }

                // Remover todas as paragens que existem
                if(q53 == tmp->nParagens){
                    free(tmp->paragens);
                    tmp->paragens = NULL;
                }

                for(int i = 0; i < q53; i++){
                    imprimirParagensLinha(tmp);
                    printf("\n\nEscolha o numero da paragem que quer remover.\n");
                    printf("Numero: ");
                    while(scanf("%d", &n) != 1 || n < 1 || n > tmp->nParagens || (paragemExiste(tmp, paragens[n-1].nome) == false)){
                        printf("\nInsira um numero valido: ");
                        while(getchar() != '\n');
                    }

                    removeParagem(tmp, tmp->paragens[n - 1].nome);
                }
            }
        }

        // Visualizar Linha
        else if (num == 6) {

            int res;

            printf("\n(1) Para visualizar uma linha especifica. (2) Para visualizar todas as linhas. (3) Para visualizar todas as linhas com uma determinada paragem.\nEscolha uma opcao: ");
            while(getchar() != '\n');
            while(scanf("%d", &res) != 1 || (res != 1 && res != 2 && res != 3)){
                printf("\nEscolha um numero 1, 2 ou 3.");
                while(getchar() != '\n');
            }

            // Visualizar linha especifica
            if(res == 1){

                Linha* atual = head;
                char q6[MAX];
                int j;

                printf("\nQue linha gostaria de consultar? ");
                while(getchar() != '\n');
                while(scanf("%[^\n]", q6) != 1 || linhaExiste(head, q6) == false){
                    printf("Linha invalida... Tente novamente: ");
                    while(getchar() != '\n');
                }

                while (atual != NULL) {

                    if (!strcmp(atual->nome, q6)){

                        printf("\n%s:\n", q6);

                        for(int i = 0; i < atual->nParagens; i++){
                            j = i;
                            printf("\n[Paragem %d]: %s #%s", ++j, atual->paragens[i].nome, atual->paragens[i].codigo);
                        }

                        putchar('\n');
                        break;
                    }
                    atual = atual->prox;
                }
            }

            // Visualizar todas as linhas
            else if(res == 2){
                imprimirLinhas(head);
                printf("\n\n");
            }

            // Visualizar todas as linhas com uma paragem especifica
            else if (res == 3){

                char q63[MAX];
                Linha* atual = head;

                printf("\nQual a paragem que deseja verificar? ");
                while (getchar() != '\n');
                while(scanf("%[^\n]", q63) != 1 || validParagem(paragens, nParagens, q63, NULL) == false){
                    printf("A paragem nao existe. Insira uma paragem valida: ");
                    while(getchar() != '\n');
                }

                printf("\nLista de linhas que incluem a paragem %s:\n", q63);

                while (atual != NULL) {

                    for(int i = 0; i < atual->nParagens; i++)
                        if(!strcmp(atual->paragens[i].nome, q63))
                            printf("\n - %s", atual->nome);

                    atual = atual->prox;
                }

                printf("\n\n");
            }
        }

        // Calculo de Percursos
        else if(num == 7){
            char q71[MAX], q72[MAX];

            imprimirParagens(paragens, nParagens);
            printf("\nParagem Origem: ");
            while (getchar() != '\n');
            while(scanf("%[^\n]", q71) != 1 || validParagem(paragens, nParagens, q71, NULL) == false){
                printf("A paragem nao existe. Insira uma paragem valida: ");
                while(getchar() != '\n');
            }
            printf("\nParagem Destino: ");
            while (getchar() != '\n');
            while(scanf("%[^\n]", q72) != 1 || validParagem(paragens, nParagens, q72, NULL) == false || !strcmp(q71, q72)){
                printf("A paragem nao existe. Insira uma paragem valida: ");
                while(getchar() != '\n');
            }

            calcPercursos(head, q71, q72);
        }

        // Sair
        else if (num == 8) {

            printf("\nA terminar o programa...\n\n");

            save(head, paragens, nParagens);
            free(paragens);
            freeLista(head);
            return 0;
        }

    }
}
#pragma clang diagnostic pop
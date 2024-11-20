
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "screen.h"
#include "keyboard.h"
#include "timer.h"

#define NUM_LINHAS 3
#define NUM_COLUNAS 13

struct ranking{

    char nome[51];
    char sobrenome[51];

    int tijolosQuebrados;
    int tempo;

    struct ranking *proximo;

};


struct ball{

    int x;
    int y;

    int dirX;
    int dirY;

    int preX;
    int preY;

    char simbolo;

};

struct bar{

    int y; // y fixo

    int x;
    int preX;

    int velocidade;

    int largura;
    int altura;

};

struct brick{

    int x;
    int y;

    int estado; // 1 - ativo, 0 - quebrado

    char simbolo;

    int largura;
    int altura;

    int espacamento;

};

void inserirRanking(struct ranking **head, char *nome, char *sobrenome, int tijolosQuebrados, float tempo) {

    struct ranking *novo = (struct ranking *)malloc(sizeof(struct ranking));

    strcpy(novo->nome, nome);
    strcpy(novo->sobrenome, sobrenome);
    novo->tijolosQuebrados = tijolosQuebrados;
    novo->tempo = tempo;
    novo->proximo = NULL;

    struct ranking *atual = *head;
    struct ranking *anterior = NULL;

    while (atual != NULL) {

        if (atual->tijolosQuebrados > tijolosQuebrados) { // prioriza tijolos

            anterior = atual;
            atual = atual->proximo;

        } else if (atual->tijolosQuebrados == tijolosQuebrados && atual->tempo < tempo) { // tempo como criterio de desempate

            anterior = atual;
            atual = atual->proximo;

        } else {

            break;

        }
    }

    if (anterior == NULL) {
        novo->proximo = *head; // se nao existir anterior
        *head = novo;
    } else {
        anterior->proximo = novo; 
        novo->proximo = atual;
    }
}

struct ranking *arquivoParaLista(char *arquivo) {

    FILE *fptr = fopen(arquivo, "r");

    if (fptr == NULL) {
        return NULL;
    }

    struct ranking *head = NULL;
    struct ranking *atual = NULL;

    char nome[50];
    char sobrenome[50];
    int tijolosQuebrados;
    float tempo;

    while (fscanf(fptr, "%s %s %d %f", nome, sobrenome, &tijolosQuebrados, &tempo) != EOF) {

        struct ranking *novo = (struct ranking *)malloc(sizeof(struct ranking));

        strcpy(novo->nome, nome);
        strcpy(novo->sobrenome, sobrenome);
        novo->tijolosQuebrados = tijolosQuebrados;
        novo->tempo = tempo;

        novo->proximo = NULL;

        if (head == NULL) {
            head = novo;
            atual = novo;
        } else {
            atual->proximo = novo;
            atual = novo;
        }
    }

    fclose(fptr);
    return head;
}

void salvarRanking(struct ranking *head, char *arquivo) {

    FILE *fptr = fopen(arquivo, "w");

    if (fptr == NULL) {
        return;
    }

    struct ranking *atual = head;

    while (atual != NULL) {
        fprintf(fptr, "%s %s %d %d\n", atual->nome, atual->sobrenome, atual->tijolosQuebrados, atual->tempo);
        atual = atual->proximo;
    }

    fclose(fptr);
}

void freeLista(struct ranking *head) {

    struct ranking *temp;

    while (head != NULL) {
        temp = head;
        head = head->proximo;
        free(temp);
    }
    
}

void displayRanking(struct ranking *head) {

    struct ranking *atual = head;
    int posicao = 1;

    printf("\n                -*-*- PLACAR -*-*-\n\n\n");

    while (atual != NULL && posicao <= 20) { // 10 primeiros

        printf("%d. %s %s - TIJOLOS QUEBRADOS: %d TEMPO: %d\n", posicao, atual->nome, atual->sobrenome, atual->tijolosQuebrados, atual->tempo);
        
        atual = atual->proximo;
        posicao++;

    }
}


void startBall(struct ball *bola){

    bola->x = (MAXX/2);
    bola->y = (MAXY/2); // consertar posicao inicial;

    bola->dirX = 1;
    bola->dirY = 1;

    bola->simbolo = 'o';

}

void startBar(struct bar *barra){

    barra->largura = 10;
    barra->altura = 2;
    barra->velocidade = 2;

    barra->x = (MAXX/2) - (barra->largura/2);
    barra->y = (MAXY-6);

    barra->preX = barra->x;

}

void startBricks(struct brick tijolos[NUM_LINHAS][NUM_COLUNAS]){
    for (int i = 0; i < NUM_LINHAS; i++){
        for (int j =0; j < NUM_COLUNAS; j++){

            tijolos[i][j].largura = 5;
            tijolos[i][j].altura = 2;
            tijolos[i][j].espacamento = 1;

            tijolos[i][j].estado = 1;

            tijolos[i][j].simbolo = '@';

            tijolos[i][j].x = (j * (tijolos[i][j].largura + tijolos[i][j].espacamento) + MINX + 1);
            tijolos[i][j].y = (i * (tijolos[i][j].altura + tijolos[i][j].espacamento)+ MINY + 1);
        }
    }
}

void updateBall(struct ball *bola, struct bar *barra, int *gameOver){

    bola->preX = bola->x;
    bola->preY = bola->y;

    bola->x += bola->dirX;
    bola->y += bola->dirY;

    if (bola->x <= (MINX + 1) || bola->x >= (MAXX - 1)){ //velocidade?
        bola->dirX = -bola->dirX;
    }

    if (bola->y <= (MINY + 1) || bola->y >= (MAXY - 1)){
        bola->dirY = -bola->dirY;
    }

    // bater com barra:

    if (bola->y == (barra->y -1)){
        if (bola->x >= barra->x && bola->x <= (barra->x + barra->largura - 1)){
            bola->dirY = -bola->dirY;
        }
    }

    if (bola->y >= (MAXY - 2)) {
        *gameOver = 1;
    }


}

void updateBar(struct bar *barra, int ch){

        if (ch == 'a' && (barra->x > (MINX+1))){ //se digitar a e estiver menoor que limite
            barra->x -= barra->velocidade;
        }
        if (ch == 'd' && (barra->x < ((MAXX - barra->largura)-1))){
            barra->x += barra->velocidade;
        }

}
//antes struct ranking *jogador
void updateBricks(struct brick tijolos[NUM_LINHAS][NUM_COLUNAS], struct ball *bola, int *tijolosQuebrados) {

    for (int i = 0; i < NUM_LINHAS; i++) {
        for (int j = 0; j < NUM_COLUNAS; j++) {

            if (tijolos[i][j].estado == 0) { 
                continue;
            }
            
            if ((bola->x >= tijolos[i][j].x && bola->x < (tijolos[i][j].x + tijolos[i][j].largura)) && (bola->y >= tijolos[i][j].y && bola->y < (tijolos[i][j].y + tijolos[i][j].altura))) { // verifica se o x e o y da bola correspondem ao do tijolo
                
                if (bola->preY < tijolos[i][j].y || bola->preY >= (tijolos[i][j].y + tijolos[i][j].altura)) { // checa se a colisao corresponde ao eixo vertical (ou seja, por baixo ou para cima) 

                    bola->dirY = -bola->dirY; //bola batento na vertical

                } else { // se nao for isso, a colisao aconteceu de lado

                    bola->dirX = -bola->dirX; // batendo na horizontal

                }

                tijolos[i][j].estado = 0; 
                //jogador->tijolosQuebrados++;
                (*tijolosQuebrados)++;
            }
        }
    }
}

void printBall(struct ball *bola){

    screenSetColor(CYAN, DARKGRAY);

    screenGotoxy(bola->preX, bola->preY);
    printf(" ");

    screenGotoxy(bola->x, bola->y);
    printf("%c", bola->simbolo);
    
}

void printBar(struct bar *barra){

    screenSetColor(CYAN, WHITE);

    for(int i = 0; i < (barra->largura); i++){
        screenGotoxy((barra->preX + i), barra->y);
        printf(" ");
    } // apagando antiga

    barra->preX = barra->x;

    for(int j = 0; j < barra->largura; j++){
        screenGotoxy((barra->x + j), barra->y);
        printf("―");
    }
    
}

void printBricks(struct brick tijolos[NUM_LINHAS][NUM_COLUNAS]) {

    for (int i = 0; i < NUM_LINHAS; i++) {
        for (int j = 0; j < NUM_COLUNAS; j++) {

            if (tijolos[i][j].estado == 0) {
                for (int h = 0; h < tijolos[i][j].altura; h++) {
                    screenGotoxy(tijolos[i][j].x, tijolos[i][j].y + h);
                    for (int w = 0; w < tijolos[i][j].largura; w++) {
                        printf(" ");
                    }
                }
            }

            if (tijolos[i][j].estado == 1) { // CASO ESTIVER ATIVO!

                for (int h = 0; h < tijolos[i][j].altura; h++) {

                    screenGotoxy(tijolos[i][j].x, tijolos[i][j].y + h); // para a altura do bloco (vai pro x e y e soma h (0, 1, 2) calculando p lugar certo)

                    for (int w = 0; w < tijolos[i][j].largura; w++) {
                        printf("%c", tijolos[i][j].simbolo); // printa um após o outro na largura
                    }

                }
            } 
        }
    }
}

void printKey(){ // adaptar para score/tempo

    screenSetColor(YELLOW, DARKGRAY);
    screenGotoxy(12, 22);
    printf("DIGITE A PARA MOVER À ESQUERDA E D PARA MOVER À DIREITA");

    screenSetColor(GREEN, DARKGRAY);
    screenGotoxy(33, 25);
    printf("BOA SORTE!");

}

int main() {

    static int ch = 0;
    int gameOver = 0;
    int tijolosQuebrados = 0;
    int startGame = 0;
    int tempo = 0;

    screenInit(1);
    keyboardInit();
    timerInit(50);

    struct ball bola;
    startBall(&bola);
    printBall(&bola);

    struct bar barra;
    startBar(&barra);
    printBar(&barra);

    struct brick tijolos[NUM_LINHAS][NUM_COLUNAS];
    startBricks(tijolos);
    printBricks(tijolos);

    struct ranking *head = arquivoParaLista("ranking.txt");

    printKey();

    screenUpdate();

    while(1){

        while (ch != 27 && !gameOver) {

            if (keyhit()) {
                ch = readch();

                if (ch == 'a' || ch == 'd') {
                    startGame = 1;
                }

                updateBar(&barra, ch);
                printBar(&barra);
                screenUpdate();
            }

            if (startGame == 1) {
                if (timerTimeOver()) {
                    tempo++;

                    updateBall(&bola, &barra, &gameOver);
                    updateBricks(tijolos, &bola, &tijolosQuebrados);

                    printBall(&bola);
                    printBar(&barra);
                    printBricks(tijolos);

                    screenUpdate();
                }
            }
        }

        if (gameOver){
            screenClear();

            screenSetColor(RED, DARKGRAY);
            screenGotoxy((MAXX/2 - 5), (MAXY/2 - 3));
            printf("<------> GAME OVER <------>");

            screenSetColor(YELLOW, DARKGRAY);
            screenGotoxy((MAXX/2 - 6), (MAXY/2 - 1));
            printf("Tijolos quebrados: %d (%d)", tijolosQuebrados, tempo);

            
            struct ranking player = {0};
            char nome[51] = {0};
            char sobrenome[51] = {0};

            screenSetColor(GREEN, DARKGRAY);
            screenGotoxy((MAXX/2 - 6), (MAXY/2 + 1));
            printf("Digite seu nome: ");
            screenShowCursor();
            
            while(keyhit()){
                readch();
            }

            screenSetColor(WHITE, DARKGRAY);
            screenGotoxy((MAXX/2 - 6), (MAXY/2 + 2));
            screenSetColor(WHITE, DARKGRAY);
            scanf("%50s", nome);

            screenGotoxy((MAXX/2 - 6), (MAXY/2 + 3));
            printf("Digite seu sobrenome: ");
            screenSetColor(WHITE, DARKGRAY);
            scanf("%50s", sobrenome);

            screenHideCursor();

            strcpy(player.nome, nome);
            strcpy(player.sobrenome, sobrenome);
            player.tijolosQuebrados = tijolosQuebrados;
            player.tempo = tempo;
            
            inserirRanking(&head, player.nome, player.sobrenome, player.tijolosQuebrados, player.tempo);
            salvarRanking(head, "ranking.txt");

            // Mostrar ranking
            screenClear();
            displayRanking(head);

            screenSetColor(YELLOW, DARKGRAY);
            screenGotoxy((MAXX/2 - 23), (MAXY/2 + 10));
            printf("OBRIGADO POR JOGAR!");
            screenUpdate();

            while(1) {
                if (keyhit()) {
                    ch = readch();
                    if (ch == 13) break; // ENTER
                    if (ch == 27) {
                        freeLista(head);
                        keyboardDestroy();
                        screenDestroy();
                        timerDestroy();
                        return 0;
                    }
                }
            }
        }

        if (ch == 27) {
            freeLista(head);
            keyboardDestroy();
            screenDestroy();
            timerDestroy();
            break;
        }
    }

    return 0;
}
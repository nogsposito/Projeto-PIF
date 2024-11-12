#include <string.h>

#include "screen.h"
#include "keyboard.h"
#include "timer.h"

int x = 34, y = 12;

struct ball{
    int x;
    int y;
    int direcaoX;
    int direcaoY;
    int velocidade;
    int poder;
};

struct bar{
    int x;
    int y;
    int velocidade;
};

struct brick{
    int estado;
    int x;
    int y;
};

//struct bonus{};

struct player{
    char nome[50];
    int tempoEmMs;
    int tijolosQuebrados;
};

struct ranking{ // lista encadeada
    struct player jogador;
    struct ranking *next;
};

// printagem de elementos:

void printBola(int nextX, int nextY, struct ball bola){

    // int x e y

    screenSetColor(WHITE, DARKGRAY);
    screenGotoxy(x, y);
    printf("𒊹");

}

void printBarra(){
    // printa barra em respectiva localizacao
}

void printBrick(){
    // printa barra em respectiva localizacao
}

void printBonus(){
    // printa bonus em respectiva localizacao
}

// comecando o jogo:

void startGame(){}

void startBricks(){}

// mudando e atualizando o jogo:

void updateBola(){

    // checa colisoes com barra ou tijolos ou paredes
    // update no jogo

}

void updateBarra(){

    // checa colisoes com bola (ou bonus?)
    // update no jogo

}

void updateBrick(){

    // checa colisoes com bola
    // update no jogo

}

//void updateBonus(){

    // checa colisoes com (bola?) ou barra
    // update no jogo
//}

// para manter e organizar os jogadores:

void inserirJogador(struct ranking **head){
   if (*head == NULL){
      (*head) = (struct ranking*)malloc(sizeof(struct ranking));

    }
}

void escreverArquivo(){ // ou usando lista encadeada

      // escreve no arquivo o resultado do jogador

}

// programa principal:

int main(){

    static int ch = 0;

    screenInit(1);
    keyboardInit();
    timerInit(50); // valor temporario

    // jogo

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}

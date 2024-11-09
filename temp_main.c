#include <string.h>

#include "screen.h"
#include "keyboard.h"
#include "timer.h"

int x = 34, y = 12;

struct ball{
  int x;
  int y;
};

struct bar{
  int x;
  int y;
};

struct brick{
  int x;
  int y;
};

struct bonus{};

struct player{
  char nome[20];
  int tempo;
};

struct ranking{ // lista encadeada
  struct player jogador;
  struct ranking *next;
};

void inserirJoador(struct ranking **head){
    if (*head == NULL){
      (*head) = (struct ranking*)malloc(sizeof(struct ranking));
    }
}

void printBola(int nextX, int nextY, struct ball bola){

    screenSetColor(WHITE, DARKGRAY);

    screenGotoxy(x, y);
    bola.x = nextX;
    bola.y = nextY;

    printf("𒊹");
}

void printBarra(){}

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

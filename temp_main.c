#include <string.h>

#include "screen.h"
#include "keyboard.h"
#include "timer.h"

int x = 34, y = 12;

struct ball{
  int x;
  int y;
};

struct bar{};

struct brick{};

struct bonus{};

struct ranking{ // lista encadeada
  char jogador[20];
  int tempo;
  struct ranking *next;
};

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

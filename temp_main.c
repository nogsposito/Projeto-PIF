#include <string.h>

#include "screen.h"
#include "keyboard.h"
#include "timer.h"

struct bola{};

struct barra{};

struct brick{};

struct bonus{};

void printBola(){}

void printBarra(){}

int main(){

    screenInit(1);
    keyboardInit();
    timerInit(50); // valor temporario

    // jogo

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}

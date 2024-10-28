#include <string.h>

#include "screen.h"
#include "keyboard.h"
#include "timer.h"

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
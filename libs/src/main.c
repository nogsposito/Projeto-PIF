/**
 * SÓ PARA SE BASEAR <-> ORIGINAL
 *
 * main.h
 * Created on Aug, 23th 2023
 * Author: Tiago Barros
 * Based on "From C to C++ course - 2002"
 */

#include <string.h>

#include "screen.h"
#include "keyboard.h"
#include "timer.h"

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

    int x;
    int y;

    int preX;
    int preY;

    int largura;
    int altura;

};

void startBall(struct ball *bola){

    bola->x = 34;
    bola->y = 12;

    bola->dirX = 1;
    bola->dirY = 1;

    bola->simbolo = 'o';

}

void startBar(struct bar *barra){

    barra->x = (40);
    barra->y = (10);

    barra->largura = 10;
    barra->altura = 2;

}

void updateBall(struct ball *bola){

    bola->preX = bola->x;
    bola->preY = bola->y;

    bola->x += bola->dirX;
    bola->y += bola->dirY;

    if (bola->x <= (MINX + 1) || bola->x >= (MAXX - 1))
    {
        bola->dirX = -bola->dirX;
    }
    if (bola->y <= (MINY + 1) || bola->y >= (MAXY - 1))
    {
        bola->dirY = -bola->dirY;
    }

}

void printBall(struct ball *bola){

    screenSetColor(CYAN, DARKGRAY);

    screenGotoxy(bola->preX, bola->preY);
    printf(" ");

    screenGotoxy(bola->x, bola->y);
    printf("%c", bola->simbolo);
    
}

void printBar(struct ball *barra){

    screenSetColor(CYAN, WHITE);

    screenGotoxy(barra->preX, barra->preY);
    printf("     ");

    screenGotoxy(barra->x, barra->y);
    printf("――――");
    
}

void printKey(int ch){

    screenSetColor(YELLOW, DARKGRAY);
    screenGotoxy(35, 22);
    printf("Key code :");

    screenGotoxy(34, 23);
    printf("            ");

    screenGotoxy(39, 23);

    printf("%d ", ch);
    while (keyhit())
    {
        printf("%d ", readch());
    }

}

int main(){

    static int ch = 0;

    screenInit(1);
    keyboardInit();
    timerInit(50);

    struct ball bola;
    startBall(&bola);
    printBall(&bola);

    struct bar barra;
    startBar(&barra);
    printBar(&barra);

    int startGame = 0;

    screenUpdate();

    while (ch != 27) // esc
    {

        if (keyhit())
        {
            ch = readch();

            printKey(ch);
            screenUpdate();
        }

        if (timerTimeOver())
        {
            updateBall(&bola);
            printBall(&bola);

            screenUpdate();
        }
        }

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}

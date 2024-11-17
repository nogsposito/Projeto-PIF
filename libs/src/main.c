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

    int y; // y fixo

    int x;
    int preX;

    int velocidade;

    int largura;
    int altura;

};

void startBall(struct ball *bola){

    bola->x = (MAXX/2);
    bola->y = (MAXY/4);

    bola->dirX = 1;
    bola->dirY = 1;

    bola->simbolo = 'o';

}

void startBar(struct bar *barra){

    barra->largura = 10;
    barra->altura = 2;
    barra->velocidade = 2;

    barra->x = (MAXX/2) - (barra->largura/2);
    barra->y = (MAXY-2);

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

    if(bola->y >= MAXY){ // se  bola tiver passado da barra
        *gameOver = 1;
    }

}

void updateBar(struct bar *barra){

    if (keyhit()){

        int ch = readch();

        if (ch == 'a' && (barra->x > (MINX+1))){ //se digitar a e estiver menoor que limite
            barra->x -= barra->velocidade;
        }
        if (ch == 'd' && (barra->x < ((MAXX - barra->largura)-1))){
            barra->x += barra->velocidade;
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
    int gameOver = 0;

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

    while (ch != 27 && !gameOver) // esc ou perde
    {

        if (keyhit())
        {
            ch = readch();

            printKey(ch);
            screenUpdate();
        }

        if (timerTimeOver())
        {
            updateBar(&barra);
            updateBall(&bola, &barra, &gameOver);

            printBall(&bola);
            printBar(&barra);

            screenUpdate();
        }
    }

    if (gameOver){

        screenClear();
        screenGotoxy((MAXX/2 - 5), (MAXY/2));
        printf("GAME OVER");
        screenUpdate();

        while(ch != 27){

            if (keyhit()){

                ch = readch();

                if (ch == 13){

                    gameOver = 0;
                    startBall(&bola);
                    startBar(&barra);
                    screenClear();
                    printBall(&bola);
                    printBar(&barra);  
                    break;              
                }

            }

        }

    }

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}
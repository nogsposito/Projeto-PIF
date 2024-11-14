#include <string.h>

#include "screen.h"
#include "keyboard.h"
#include "timer.h"

#define LARGURA_TELA 40
#define ALTURA_TELA 20
#define NUM_BLOCOS_LINHA 10
#define NUM_BLOCOS_COLUNA 2
#define NUM_BLOCOS (NUM_BLOCOS_LINHA * NUM_BLOCOS_COLUNA)
#define NUM_BLOCOS_DIFICIL 20
#define LARGURA_BLOCO 4
#define ALTURA_BLOCO 1
#define LARGURA_BARRA 6
#define ALTURA_BARRA (ALTURA_TELA - 2) // Posição vertical da barra (linha inferior da tela)


int x = 34, y = 12;

struct ball
{
    int x;
    int y;
    int direcaoX;
    int direcaoY;
    int velocidade;
    int poder;
};

struct bar
{
    int x;
    int y;
    int velocidade;
};

struct brick
{
    int estado;
    int x;
    int y;
};

struct bonus
{
};

struct player
{
    char nome[50];
    int tempoEmMs;
    int tijolosQuebrados;
};

struct ranking
{ // lista encadeada
    struct player jogador;
    struct ranking *next;
};

char tela[ALTURA_TELA][LARGURA_TELA];

// printagem de elementos:

void printBola(int nextX, int nextY, struct ball bola)
{

    // int x e y

    screenSetColor(WHITE, DARKGRAY);
    screenGotoxy(x, y);
    printf("𒊹");
}

void printBarra(struct bar *barra)
{
    barra->x = (LARGURA_TELA - LARGURA_BARRA) / 2; // Centraliza a barra
    barra->y = ALTURA_BARRA;
    barra->velocidade = 1; // Velocidade inicial

    // Desenha a barra na posição inicial
    for (int i = 0; i < LARGURA_BARRA; i++)
    {
        screenGotoxy(barra->x + i, barra->y);
        printf("═"); // Caractere representando a barra
    }
}

// Função para inicializar e exibir os blocos na parede
void printBrick(struct brick bricks[NUM_BLOCOS])
{
    int x_offset = (LARGURA_TELA - (NUM_BLOCOS_LINHA * LARGURA_BLOCO)) / 2; // Centraliza os blocos horizontalmente
    int y_offset = 2; // Define a altura inicial dos blocos na tela
    // offsets ajudam a organizar os blocos visualmente, centralizando-os e controlando seu espaçamento inicial.
    for (int i = 0; i < NUM_BLOCOS_COLUNA; i++)
    {
        for (int j = 0; j < NUM_BLOCOS_LINHA; j++)
        {
            int index = i * NUM_BLOCOS_LINHA + j;
            bricks[index].x = x_offset + j * LARGURA_BLOCO;
            bricks[index].y = y_offset + i * ALTURA_BLOCO;
            bricks[index].estado = 1; // Define o bloco como ativo (não destruído)

            // Desenha o bloco na posição inicial
            for (int k = 0; k < LARGURA_BLOCO; k++)
            {
                screenGotoxy(bricks[index].x + k, bricks[index].y);
                printf("■"); // Caractere representando o bloco
            }
        }
    }
}

void printBonus()
{
    // printa bonus em respectiva localizacao
}

// comecando o jogo:

void startGame() {}

void startBricks() {}

// mudando e atualizando o jogo:

#include <stdio.h>

// Função para atualizar a posição e checar colisões da bola
void updateBola(struct ball *bola, struct bar barra, struct brick bricks[NUM_BLOCOS])
{
    // Atualiza a posição da bola
    int nextX = bola->x + bola->direcaoX;
    int nextY = bola->y + bola->direcaoY;

    // Checa colisão com as paredes
    if (nextX <= 0 || nextX >= LARGURA_TELA - 1)
    {
        bola->direcaoX *= -1; // Inverte direção horizontal
    }
    if (nextY <= 0)
    {
        bola->direcaoY *= -1; // Inverte direção vertical
    }

    // Checa colisão com a barra
    if (nextY == barra.y && nextX >= barra.x && nextX < barra.x + LARGURA_BARRA)
    {
        bola->direcaoY *= -1; // Inverte direção vertical
    }

    // Checa colisão com os tijolos
    for (int i = 0; i < NUM_BLOCOS; i++)
    {
        if (bricks[i].estado == 1) // Bloco ativo
        {
            if (nextX >= bricks[i].x && nextX < bricks[i].x + LARGURA_BLOCO &&
                nextY == bricks[i].y)
            {
                bricks[i].estado = 0; // Desativa o bloco
                bola->direcaoY *= -1; // Inverte direção vertical
                break; // Sai do loop para evitar múltiplas colisões
            }
        }
    }

    // Atualiza a posição da bola
    bola->x += bola->direcaoX;
    bola->y += bola->direcaoY;
}


void updateBarra()
{

    // checa colisoes com bola (ou bonus?)
    // update no jogo
}

void updateBrick()
{

    // checa colisoes com bola
    // update no jogo
}

void updateBonus()
{

    // checa colisoes com (bola?) ou barra
    // update no jogo
}

// para manter e organizar os jogadores:

void inserirJogador(struct ranking **head)
{
    if (*head == NULL)
    {
        (*head) = (struct ranking *)malloc(sizeof(struct ranking));
    }
}

void escreverArquivo()
{ // ou usando lista encadeada

    // escreve no arquivo o resultado do jogador
}


// programa principal:

int main()
{

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
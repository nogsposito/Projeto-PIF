#include <string.h>

#include "screen.h"
#include "keyboard.h"
#include "timer.h"

int playerX;
int playerY;

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
    int largura;
};

struct brick
{
    int ativo;
    int estado;
    int x;
    int y;
};

// struct bonus{};

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

// printagem de elementos:

void printBola(struct ball bola)
{

    // int x e y

    screenSetColor(WHITE, DARKGRAY);
    printf("𒊹");
}

void printBarra()
{
    // printa barra em respectiva localizacao
}

void printBrick()
{
    // printa barra em respectiva localizacao
}

void printBonus()
{
    // printa bonus em respectiva localizacao
}

// comecando o jogo:

void startBar(struct bar barra)
{

    int LARGURA_BARRA = 1;

    barra.x = (SCREEN_WIDTH / 2);
    barra.y = (SCREEN_HEIGHT - (SCREEN_HEIGHT / 4));

    barra.largura = LARGURA_BARRA;
    barra.velocidade = 1;
}

void startBricks(struct brick tijolos[linhas][colunas])
{

    int LARGURA_TIJOLO = 2;
    int ALTURA_TIJOLO = 1;

    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            tijolos[i][j].x = j * (LARGURA_TIJOLO + 1);
            tijolos[i][j].y = i * (ALTURA_TIJOLO + 1);

            tijolos[i][j].ativo = 1;
        }
    }
}

void startBola(struct ball bola)
{

    bola.x = (SCREEN_WIDTH / 2);
    bola.y = (SCREEN_HEIGHT - (SCREEN_HEIGHT / 4));

    bola.direcaoX = 1;
    bola.direcaoY = 1;

    bola.velocidade = 1;
    bola.poder = 1;
}

// mudando e atualizando o jogo:

void updateBola(struct ball bola, int x, int y)
{

    // checa colisoes com barra ou tijolos ou paredes
    // update no jogo
}

void updateBarra(struct bar barra, int ch, int x, int y)
{

    if (ch == 97)
    { // se apertar 'a'
        screenGotoxy((x - 8), y);
    }
    else if (ch == 100)
    { // se apertar 'e'
        screenGotoxy((x + 8), y);
    }

    // checa colisoes com bola (ou bonus?)
    // update no jogo
}

void updateBrick(struct brick tijolo)
{

    // checa colisoes com bola
    // update no jogo
}

// void updateBonus(){

// checa colisoes com (bola?) ou barra
// update no jogo
//}

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
    FILE *placar;
    placar = fopen("ranking.txt", "a");
    // escreve no arquivo o resultado do jogador
    fclose(placar);
}

void startGame()
{
    screenClear();
    printf("=================================\n");
    printf("         BRICK OUT GAME\n");
    printf("=================================\n");
    printf("Pressione qualquer tecla para começar!\n");
    screenUpdate();

    while (!keyhit())
    {
        usleep(50000);
    }
    readch();
    screenClear();
}

int gameOver(int score)
{
    screenClear();
    printf("=================================\n");
    printf("           GAME OVER\n");
    printf("=================================\n");
    printf("Pontuação Final: %d\n", score);
    printf("=================================\n");
    printf("1. Reiniciar o Jogo\n");
    printf("2. Sair\n");
    printf("=================================\n");
    screenUpdate();

    while (1)
    {
        if (keyhit())
        {
            char opcao = readch();
            if (opcao == '1')
            {
                return 1;
            }
            else if (opcao == '2')
            {
                return 0;
            }
        }
        usleep(50000);
    }
}

// void printLogo(){
//     printf(" ____       _      _      ____                 _             _ ");
//     printf("| __ ) _ __(_) ___| | __ | __ ) _ __ ___  __ _| | _____ _ __| |");
//     printf("|  _ \| '__| |/ __| |/ / |  _ \| '__/ _ \/ _` | |/ / _ \ '__| |");
//     printf("| |_) | |  | | (__|   <  | |_) | | |  __/ (_| |   <  __/ |  |_|");
//     printf("|____/|_|  |_|\___|_|\_\ |____/|_|  \___|\__,_|_|\_\___|_|  (_)");
// }

// programa principal:

int main()
{

    static int ch = 0;

    struct ball bola;
    struct bar barra;
    struct brick tijolo;

    screenInit(1);
    keyboardInit();
    timerInit(50); // valor temporario

    startBola(bola);
    startBar(barra);
    startBricks(tijolo);

    printBarra();
    printBola(bola);
    printBrick();

    int jogoAtivo = 1;

    while (jogoAtivo == 1)
    {

        // Update game state (move elements, verify collision, etc)
        if (timerTimeOver() == 1)
        {
            bola.x = bola.x + bola.velocidade;

            if (newX >= (MAXX - strlen("Hello World") - 1) || newX <= MINX + 1)
            {
                incX = -incX
            };
            int newY = y + incY;
            if (newY >= MAXY - 1 || newY <= MINY + 1)
                incY = -incY;

            printKey(ch);
            printHello(newX, newY);

            screenUpdate();
        }

        if (keyhit())
        {
            ch = readch();
            printKey(ch);
            screenUpdate();
        }
    }

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}

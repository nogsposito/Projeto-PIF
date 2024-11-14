#include <string.h>

#include "screen.h"
#include "keyboard.h"
#include "timer.h"

int LARGURA_BARRA = 1;

int LARGURA_TIJOLO = 2;
int ALTURA_TIJOLO = 1;

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
    int largura;
};

struct brick{
    int ativo;
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

void startBarra(struct bar barra){
  barra.x = (SCREEN_WIDTH / 2);
  barra.y = (SCREEN_HEIGHT - (SCREEN_HEIGHT / 4));

  barra.largura = LARGURA_BARRA;
  barra.velocidade = 1;
}

void startBricks(struct brick tijolos[linhas][colunas]){
  for (int i = 0; i < linhas; i++){
    for (int j = 0; j < colunas; j++){
      tijolos[i][j].x = j * (LARGURA_TIJOLO + 1);
      tijolos[i][j].y = i * (ALTURA_TIJOLO + 1);

      tijolos[i][j].ativo = 1;
    }
  }
}

void startBola(struct ball bola){

  bola.x = (SCREEN_WIDTH / 2);
  bola.y = (SCREEN_HEIGHT - (SCREEN_HEIGHT / 4));

  bola.direcaoX = 1;
  bola.direcaoY = 1;

  bola.velocidade = 1;
  bola.poder = 1;

}

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

    struct ball bola;
    struct bar barra;
    struct brick tijolo;

    screenInit(1);
    keyboardInit();
    timerInit(50); // valor temporario

    startBola(bola);

    while(ch){ // mudar
      readch();

    }

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}

#ifndef NAVE_H_INCLUDED
#define NAVE_H_INCLUDED

#include "../../space_shooter.h"

#define NAVE_MOVIMENTO_INICIAL 0

struct Nave {
    int x;
    int y;
    int largura;
    int altura;
    int velocidade;
    int movimentando_esquerda;
    int movimentando_direita;
};
typedef struct Nave Nave;

int nave_criar(Nave **nave, int x, int y, int largura, int altura, int velocidade);
int nave_liberar(Nave **nave);
void nave_desenhar(SDL_Renderer *tela, SDL_Texture *textura, Nave **nave);

#endif
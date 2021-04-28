#ifndef NAVE_H_INCLUDED
#define NAVE_H_INCLUDED

#include "../../space_shooter.h"

#define NAVE_MOVIMENTO_INICIAL 0
#define NAVE_MOVER 1
#define NAVE_PARAR 0

struct Nave {
    int x;
    int y;
    int largura;
    int altura;
    int velocidade;
    int movimentando_cima;
    int movimentando_baixo;
};
typedef struct Nave Nave;

int nave_criar(Nave **nave, int x, int y, int largura, int altura, int velocidade);
int nave_liberar(Nave **nave);
void nave_desenhar(SDL_Renderer *tela, SDL_Texture *textura, Nave **nave);
void nave_movimentar(Nave **nave);
void nave_subir(Nave **nave);
void nave_descer(Nave **nave);
void nave_parar_subida(Nave **nave);
void nave_parar_descida(Nave **nave);

#endif
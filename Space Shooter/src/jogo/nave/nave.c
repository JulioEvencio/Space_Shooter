#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../../space_shooter.h"
#include "nave.h"

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

int nave_criar(Nave **nave, int x, int y, int largura, int altura, int velocidade) {
    *nave = malloc(sizeof **nave);

    if (*nave == NULL) return -1;

    (*nave)->x = x;
    (*nave)->y = y;
    (*nave)->largura = largura;
    (*nave)->altura = altura;
    (*nave)->velocidade = velocidade;
    (*nave)->movimentando_cima = NAVE_PARAR;
    (*nave)->movimentando_baixo = NAVE_PARAR;

    return 0;
}

int nave_liberar(Nave **nave) {
    free(*nave);
}

void nave_desenhar(Nave **nave, SDL_Renderer *tela, SDL_Texture *textura) {
    SDL_Rect retangulo_nave = {(*nave)->x, (*nave)->y, (*nave)->largura, (*nave)->altura};
    SDL_RenderCopy(tela, textura, NULL, &retangulo_nave);
}

void nave_movimentar(Nave **nave) {
    if ((*nave)->movimentando_cima && (*nave)->y > 0) {
        (*nave)->y -= (*nave)->velocidade;
    }

    if ((*nave)->movimentando_baixo && ((*nave)->y + (*nave)->altura) < JANELA_ALTURA) {
        (*nave)->y += (*nave)->velocidade;
    }
}

void nave_subir(Nave **nave) {
    (*nave)->movimentando_cima = NAVE_MOVER;
}

void nave_parar_subida(Nave **nave) {
    (*nave)->movimentando_cima = NAVE_PARAR;
}

void nave_descer(Nave **nave) {
    (*nave)->movimentando_baixo = NAVE_MOVER;
}

void nave_parar_descida(Nave **nave) {
    (*nave)->movimentando_baixo = NAVE_PARAR;
}

void nave_alterar_x(Nave **nave, int x) {
    (*nave)->x = x;
}

void nave_alterar_y(Nave **nave, int y) {
    (*nave)->y = y;
}

int nave_obter_x(Nave **nave) {
    return (*nave)->x;
}

int nave_obter_y(Nave **nave) {
    return (*nave)->y;
}
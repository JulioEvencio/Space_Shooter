#include "stdlib.h"
#include "nave.h"

int nave_criar(Nave **nave, int x, int y, int largura, int altura, int velocidade) {
    *nave = malloc(sizeof **nave);

    if (*nave == NULL) return -1;

    (*nave)->x = x;
    (*nave)->y = y;
    (*nave)->largura = largura;
    (*nave)->altura = altura;
    (*nave)->velocidade = velocidade;
    (*nave)->movimentando_cima = NAVE_MOVIMENTO_INICIAL;
    (*nave)->movimentando_baixo = NAVE_MOVIMENTO_INICIAL;

    return 0;
}

int nave_liberar(Nave **nave) {
    free(*nave);
}

void nave_desenhar(SDL_Renderer *tela, SDL_Texture *textura, Nave **nave) {
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
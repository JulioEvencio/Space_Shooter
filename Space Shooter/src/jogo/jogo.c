#include "jogo.h"

void jogo_tela(SDL_Renderer *tela, SDL_Texture *textura[], Nave **jogador) {
    SDL_Rect fundo = {JOGO_FUNDO_X, JOGO_FUNDO_Y, JOGO_FUNDO_LARGURA, JOGO_FUNDO_ALTURA};
    SDL_RenderCopy(tela, textura[TEXTURA_BACKGROUND], NULL, &fundo);

    nave_desenhar(tela, textura[TEXTURA_SPRITE_PERSONAGEM_1], jogador);
    nave_movimentar(jogador);

    /*  Code */
}
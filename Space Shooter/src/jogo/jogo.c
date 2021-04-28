#include "jogo.h"

void jogo_tela(SDL_Renderer *tela, SDL_Texture *textura[], Personagem **jogador) {
    SDL_Rect fundo = {JOGO_FUNDO_X, JOGO_FUNDO_Y, JOGO_FUNDO_LARGURA, JOGO_FUNDO_ALTURA};
    SDL_RenderCopy(tela, textura[TEXTURA_BACKGROUND], NULL, &fundo);

    personagem_desenhar(tela, jogador);
    personagem_movimentar(jogador);

    /*  Code */
}
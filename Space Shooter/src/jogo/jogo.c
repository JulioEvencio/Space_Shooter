#include "jogo.h"

void jogo_tela(SDL_Renderer *tela, SDL_Texture *textura[]) {
    SDL_Rect fundo = {JOGO_FUNDO_X, JOGO_FUNDO_Y, JOGO_FUNDO_LARGURA, JOGO_FUNDO_ALTURA};
    SDL_RenderCopy(tela, textura[TEXTURA_BACKGROUND], NULL, &fundo);

    SDL_Rect personagem = {50, 50, (32 * 3), (32 * 3)};
    SDL_RenderCopy(tela, textura[TEXTURA_SPRITE_PERSONAGEM_1], NULL, &personagem);

    /*  Code */
}
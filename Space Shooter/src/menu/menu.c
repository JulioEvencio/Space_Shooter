#include "menu.h"

void menu_tela(SDL_Renderer *tela, SDL_Texture *textura[]) {
    SDL_Rect fundo = {MENU_FUNDO_X, MENU_FUNDO_Y, MENU_FUNDO_LARGURA, MENU_FUNDO_ALTURA};
    SDL_RenderCopy(tela, textura[TEXTURA_BACKGROUND], NULL, &fundo);

    SDL_Rect play = {MENU_PLAY_X, MENU_PLAY_Y, MENU_PLAY_LARGURA, MENU_PLAY_ALTURA};
    SDL_RenderCopy(tela, textura[TEXTURA_PLAY], NULL, &play);
}
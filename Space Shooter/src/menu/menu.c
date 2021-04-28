#include "menu.h"

void menu_click(SDL_Event *evento, int *loop);

void menu_tela(SDL_Renderer *tela, SDL_Texture *textura[]) {
    SDL_Rect fundo = {MENU_FUNDO_X, MENU_FUNDO_Y, MENU_FUNDO_LARGURA, MENU_FUNDO_ALTURA};
    SDL_RenderCopy(tela, textura[TEXTURA_BACKGROUND], NULL, &fundo);

    SDL_Rect play = {MENU_PLAY_X, MENU_PLAY_Y, MENU_PLAY_LARGURA, MENU_PLAY_ALTURA};
    SDL_RenderCopy(tela, textura[TEXTURA_PLAY], NULL, &play);
}

void menu_evento(SDL_Event *evento, int *loop) {
    if ((*evento).type == SDL_MOUSEBUTTONDOWN) {
        menu_click(evento, loop);
    }
}

void menu_click(SDL_Event *evento, int *loop) {
    int coluna_mouse = (*evento).motion.x;
    int linha_mouse = (*evento).motion.y;

    if (coluna_mouse > MENU_PLAY_X && coluna_mouse < (MENU_PLAY_X + MENU_PLAY_LARGURA)) {
        if (linha_mouse > MENU_PLAY_Y && linha_mouse < (MENU_PLAY_Y + MENU_PLAY_ALTURA)) {
            *loop = LOOP_JOGO;
        }
    }
}
#include <stdlib.h>
#include "menu.h"

void menu_click_pressionado(SDL_Event *evento, SDL_Texture *textura[], Menu **menu, int *loop);
void menu_click_solto(SDL_Event *evento, int *loop);

int menu_inicializar(Menu **menu, SDL_Texture *textura[]) {
    *menu = malloc(sizeof **menu);

    if (*menu == NULL) return -1;

    (*menu)->play = textura[TEXTURA_PLAY];

    return 0;
}

void menu_liberar(Menu **menu) {
    free(*menu);
}

void menu_tela(SDL_Renderer *tela, SDL_Texture *textura[], Menu **menu) {
    SDL_Rect fundo = {MENU_FUNDO_X, MENU_FUNDO_Y, MENU_FUNDO_LARGURA, MENU_FUNDO_ALTURA};
    SDL_RenderCopy(tela, textura[TEXTURA_BACKGROUND], NULL, &fundo);

    SDL_Rect play = {MENU_PLAY_X, MENU_PLAY_Y, MENU_PLAY_LARGURA, MENU_PLAY_ALTURA};
    SDL_RenderCopy(tela, (*menu)->play, NULL, &play);
}

void menu_evento(SDL_Event *evento, SDL_Texture *textura[], Menu **menu, int *loop) {
    if ((*evento).type == SDL_MOUSEBUTTONDOWN) {
        menu_click_pressionado(evento, textura, menu, loop);
    }

    if ((*evento).type == SDL_MOUSEBUTTONUP) {
        (*menu)->play = textura[TEXTURA_PLAY];
        menu_click_solto(evento, loop);
    }
}

void menu_click_pressionado(SDL_Event *evento, SDL_Texture *textura[], Menu **menu, int *loop) {
    int coluna_mouse = (*evento).motion.x;
    int linha_mouse = (*evento).motion.y;

    if (coluna_mouse > MENU_PLAY_X && coluna_mouse < (MENU_PLAY_X + MENU_PLAY_LARGURA)) {
        if (linha_mouse > MENU_PLAY_Y && linha_mouse < (MENU_PLAY_Y + MENU_PLAY_ALTURA)) {
            (*menu)->play = textura[TEXTURA_PLAY_PRESSIONADO];
        }
    }
}

void menu_click_solto(SDL_Event *evento, int *loop) {
    int coluna_mouse = (*evento).motion.x;
    int linha_mouse = (*evento).motion.y;

    if (coluna_mouse > MENU_PLAY_X && coluna_mouse < (MENU_PLAY_X + MENU_PLAY_LARGURA)) {
        if (linha_mouse > MENU_PLAY_Y && linha_mouse < (MENU_PLAY_Y + MENU_PLAY_ALTURA)) {
            *loop = LOOP_JOGO;
        }
    }
}
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../space_shooter.h"
#include "menu.h"

#define MENU_FUNDO_X 0
#define MENU_FUNDO_Y 0
#define MENU_FUNDO_LARGURA JANELA_LARGURA
#define MENU_FUNDO_ALTURA JANELA_ALTURA

#define MENU_PLAY_X 504
#define MENU_PLAY_Y 150
#define MENU_PLAY_LARGURA 192
#define MENU_PLAY_ALTURA 128
#define MENU_PLAY_SOLTO 0
#define MENU_PLAY_PRESSIONADO 1

struct Menu {
    SDL_Texture *play;
    SDL_Texture *play_solto;
    SDL_Texture *play_pressionado;
    SDL_Texture *fundo;
};

void menu_click_pressionado(Menu **menu, SDL_Event *evento);
void menu_click_solto(SDL_Event *evento, int *loop);

int menu_criar(Menu **menu, SDL_Texture *textura[]) {
    *menu = malloc(sizeof **menu);

    if (*menu == NULL) return -1;

    (*menu)->play = textura[TEXTURA_PLAY];
    (*menu)->play_solto = textura[TEXTURA_PLAY];
    (*menu)->play_pressionado = textura[TEXTURA_PLAY_PRESSIONADO];

    (*menu)->fundo = textura[TEXTURA_BACKGROUND];

    return 0;
}

void menu_liberar(Menu **menu) {
    free(*menu);
}

void menu_tela(Menu **menu, SDL_Renderer *tela) {
    SDL_Rect fundo = {MENU_FUNDO_X, MENU_FUNDO_Y, MENU_FUNDO_LARGURA, MENU_FUNDO_ALTURA};
    SDL_RenderCopy(tela, (*menu)->fundo, NULL, &fundo);

    SDL_Rect play = {MENU_PLAY_X, MENU_PLAY_Y, MENU_PLAY_LARGURA, MENU_PLAY_ALTURA};
    SDL_RenderCopy(tela, (*menu)->play, NULL, &play);
}

void menu_evento(Menu **menu, SDL_Event *evento, int *loop) {
    if (evento->type == SDL_MOUSEBUTTONDOWN) {
        menu_click_pressionado(menu, evento);
    }

    if (evento->type == SDL_MOUSEBUTTONUP) {
        (*menu)->play = (*menu)->play_solto;
        menu_click_solto(evento, loop);
    }
}

void menu_click_pressionado(Menu **menu, SDL_Event *evento) {
    int coluna_mouse = evento->motion.x;
    int linha_mouse = evento->motion.y;

    if (coluna_mouse > MENU_PLAY_X && coluna_mouse < (MENU_PLAY_X + MENU_PLAY_LARGURA)) {
        if (linha_mouse > MENU_PLAY_Y && linha_mouse < (MENU_PLAY_Y + MENU_PLAY_ALTURA)) {
            (*menu)->play = (*menu)->play_pressionado;
        }
    }
}

void menu_click_solto(SDL_Event *evento, int *loop) {
    int coluna_mouse = evento->motion.x;
    int linha_mouse = evento->motion.y;

    if (coluna_mouse > MENU_PLAY_X && coluna_mouse < (MENU_PLAY_X + MENU_PLAY_LARGURA)) {
        if (linha_mouse > MENU_PLAY_Y && linha_mouse < (MENU_PLAY_Y + MENU_PLAY_ALTURA)) {
            *loop = LOOP_JOGO;
        }
    }
}
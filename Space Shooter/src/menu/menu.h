#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "../space_shooter.h"

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
};
typedef struct Menu Menu;

int menu_inicializar(Menu **menu, SDL_Texture *textura[]);
void menu_liberar(Menu **menu);
void menu_tela(SDL_Renderer *tela, SDL_Texture *textura[], Menu **menu);
void menu_evento(SDL_Event *evento, SDL_Texture *textura[], Menu **menu, int *loop);

#endif
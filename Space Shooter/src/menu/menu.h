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

void menu_tela(SDL_Renderer *tela, SDL_Texture *textura[]);

#endif
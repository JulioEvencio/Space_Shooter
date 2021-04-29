#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

typedef struct Menu Menu;

int menu_criar(Menu **menu, SDL_Texture *textura[]);
void menu_liberar(Menu **menu);
void menu_tela(Menu **menu, SDL_Renderer *tela);
void menu_evento(Menu **menu, SDL_Event *evento, int *loop);

#endif
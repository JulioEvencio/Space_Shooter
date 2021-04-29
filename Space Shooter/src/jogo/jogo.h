#ifndef JOGO_H_INCLUDED
#define JOGO_H_INCLUDED

typedef struct Jogo Jogo;

int jogo_inicializar(Jogo **jogo, SDL_Texture *textura[]);
void jogo_liberar(Jogo **jogo);
void jogo_tela(Jogo **jogo, SDL_Renderer *tela);
void jogo_evento(Jogo **jogo, SDL_Event *evento);

#endif
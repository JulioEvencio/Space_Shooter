#ifndef JOGO_H_INCLUDED
#define JOGO_H_INCLUDED

typedef struct Jogo Jogo;

int jogo_criar(Jogo **jogo, SDL_Texture *textura[]);
void jogo_liberar(Jogo **jogo);
void jogo_tela(Jogo **jogo, SDL_Renderer *tela, TTF_Font *fonte, int *loop);
void jogo_evento(Jogo **jogo, SDL_Event *evento);

#endif
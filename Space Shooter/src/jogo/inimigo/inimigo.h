#ifndef INIMIGO_H_INCLUDED
#define INIMIGO_H_INCLUDED

typedef struct Inimigo Inimigo;

int inimigo_criar(Inimigo **inimigo, SDL_Texture *textura[]);
void inimigo_liberar(Inimigo **inimigo);
void inimigo_desenhar(Inimigo **inimigo, SDL_Renderer *tela);
void inimigo_movimentar(Inimigo **inimigo);

#endif
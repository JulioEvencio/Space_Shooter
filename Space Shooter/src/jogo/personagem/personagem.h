#ifndef PERSONAGEM_H_INCLUDED
#define PERSONAGEM_H_INCLUDED

#include "../../space_shooter.h"
#include "../nave/nave.h"

#define PERSONAGEM_X 50
#define PERSONAGEM_Y 50
#define PERSONAGEM_LARGURA 32 * 3
#define PERSONAGEM_ALTURA 32 * 3
#define PERSONAGEM_VELOCIDADE 8
#define PERSONAGEM_VIDA 1

struct Personagem {
    int vida;
    Nave *nave;
    SDL_Texture *textura;
};
typedef struct Personagem Personagem;

int personagem_criar(Personagem **personagem, SDL_Texture *textura);
void personagem_liberar(Personagem **personagem);
void personagem_desenhar(SDL_Renderer *tela, Personagem **personagem);
void personagem_movimentar(Personagem **personagem);
void personagem_subir(Personagem **personagem);
void personagem_descer(Personagem **personagem);
void personagem_parar_subida(Personagem **personagem);
void personagem_parar_descida(Personagem **personagem);

#endif
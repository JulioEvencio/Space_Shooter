#ifndef JOGO_H_INCLUDED
#define JOGO_H_INCLUDED

#include "../space_shooter.h"
#include "personagem/personagem.h"

#define JOGO_FUNDO_X 0
#define JOGO_FUNDO_Y 0
#define JOGO_FUNDO_LARGURA JANELA_LARGURA
#define JOGO_FUNDO_ALTURA JANELA_ALTURA

void jogo_tela(SDL_Renderer *tela, SDL_Texture *textura[], Personagem **jogador);

#endif
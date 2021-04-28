#ifndef SPACE_SHOOTER_INCLUDED
#define SPACE_SHOOTER_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define JANELA_NOME "Space Shooter"
#define JANELA_LARGURA 640
#define JANELA_ALTURA 480
#define JANELA_DELAY 30
#define JANELA_COR 0, 0, 0, 255

#define TEXTURA_QUANTIDADE 2

enum Textura {
    SPRITE_PERSONAGEM_1,
    SPRITE_PERSONAGEM_2
};

static char *textura_arquivo[TEXTURA_QUANTIDADE] = {
    "../imagem/personagem1.png",
    "../imagem/personagem2.png"
};

int carregar_texturas(SDL_Renderer *tela, SDL_Texture *textura[]);
void liberar_texturas(SDL_Texture *textura[]);
void verificar_tecla_pressionada(SDL_Event *evento);
void verificar_tecla_solta(SDL_Event *evento);

#endif
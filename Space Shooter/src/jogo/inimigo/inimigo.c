#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../../space_shooter.h"
#include "../nave/nave.h"
#include "inimigo.h"

#define INIMIGO_X -10
#define INIMIGO_Y 200
#define INIMIGO_LARGURA 32 * 3
#define INIMIGO_ALTURA 32 * 3
#define INIMIGO_VELOCIDADE 3
#define INIMIGO_SPRITE 4
#define INIMIGO_SPRITE_1 0
#define INIMIGO_SPRITE_2 1
#define INIMIGO_SPRITE_3 2
#define INIMIGO_SPRITE_4 3
#define INIMIGO_RESETAR_SPRITE 0

struct Inimigo {
    int controle_sprite;
    Nave *nave;
    SDL_Texture *sprite[INIMIGO_SPRITE];
};

int inimigo_criar(Inimigo **inimigo, SDL_Texture *textura[]) {
    int erro;

    *inimigo = malloc(sizeof **inimigo);

    if (*inimigo == NULL) return -1;

    erro = nave_criar(
        &(*inimigo)->nave,
        INIMIGO_X,
        INIMIGO_Y,
        INIMIGO_LARGURA,
        INIMIGO_ALTURA,
        INIMIGO_VELOCIDADE
    );

    if (erro) {
        free(*inimigo);
        return -1;
    }

    (*inimigo)->controle_sprite = INIMIGO_RESETAR_SPRITE;

    (*inimigo)->sprite[INIMIGO_SPRITE_1] = textura[TEXTURA_INIMIGO_SPRITE_1];
    (*inimigo)->sprite[INIMIGO_SPRITE_2] = textura[TEXTURA_INIMIGO_SPRITE_2];
    (*inimigo)->sprite[INIMIGO_SPRITE_3] = textura[TEXTURA_INIMIGO_SPRITE_3];
    (*inimigo)->sprite[INIMIGO_SPRITE_4] = textura[TEXTURA_INIMIGO_SPRITE_4];

    return 0;
}

void inimigo_liberar(Inimigo **inimigo) {
    nave_liberar(&(*inimigo)->nave);
    free(*inimigo);
}

void inimigo_desenhar(Inimigo **inimigo, SDL_Renderer *tela) {
    static int controlador = 0;
    if (controlador == 24) controlador = 0;
    else controlador++;

    nave_desenhar(&(*inimigo)->nave, tela, (*inimigo)->sprite[(*inimigo)->controle_sprite]);

    if (controlador >= 0 && controlador < 6) {
        (*inimigo)->controle_sprite = INIMIGO_SPRITE_1;
    }

    if (controlador >= 6 && controlador < 12) {
        (*inimigo)->controle_sprite = INIMIGO_SPRITE_2;
    }

    if (controlador >= 12 && controlador < 18) {
        (*inimigo)->controle_sprite = INIMIGO_SPRITE_3;
    }

    if (controlador >= 18 && controlador <= 24) {
        (*inimigo)->controle_sprite = INIMIGO_SPRITE_4;
    }
}

void inimigo_movimentar(Inimigo **inimigo) {
    int x, y;

    x = nave_obter_x(&(*inimigo)->nave) - INIMIGO_VELOCIDADE;
    nave_alterar_x(&(*inimigo)->nave, x);

    if ((x + INIMIGO_LARGURA) < 0) {
        x = JANELA_LARGURA + (rand() % JANELA_LARGURA);
        y = rand() % (JANELA_ALTURA - INIMIGO_ALTURA);

        nave_alterar_x(&(*inimigo)->nave, x);
        nave_alterar_y(&(*inimigo)->nave, y);
    }
}
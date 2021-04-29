#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../../space_shooter.h"
#include "../nave/nave.h"
#include "personagem.h"

#define PERSONAGEM_X 50
#define PERSONAGEM_Y 50
#define PERSONAGEM_LARGURA 32 * 3
#define PERSONAGEM_ALTURA 32 * 3
#define PERSONAGEM_VELOCIDADE 8

struct Personagem {
    Nave *nave;
    SDL_Texture *textura;
};

int personagem_criar(Personagem **personagem, SDL_Texture *textura[]) {
    int erro;

    *personagem = malloc(sizeof **personagem);

    if (*personagem == NULL) return -1;

    erro = nave_criar(
        &(*personagem)->nave,
        PERSONAGEM_X,
        PERSONAGEM_Y,
        PERSONAGEM_LARGURA,
        PERSONAGEM_ALTURA,
        PERSONAGEM_VELOCIDADE
    );

    if (erro) {
        free(*personagem);
        return -1;
    }

    (*personagem)->textura = textura[TEXTURA_SPRITE_PERSONAGEM_1];

    return 0;
}

void personagem_liberar(Personagem **personagem) {
    nave_liberar(&(*personagem)->nave);
    free(*personagem);
}

void personagem_desenhar(Personagem **personagem, SDL_Renderer *tela) {
    nave_desenhar(&(*personagem)->nave, tela, (*personagem)->textura);
}

void personagem_movimentar(Personagem **personagem) {
    nave_movimentar(&(*personagem)->nave);
}

void personagem_subir(Personagem **personagem) {
    nave_subir(&(*personagem)->nave);
}

void personagem_descer(Personagem **personagem) {
    nave_descer(&(*personagem)->nave);
}

void personagem_parar_subida(Personagem **personagem) {
    nave_parar_subida(&(*personagem)->nave);
}

void personagem_parar_descida(Personagem **personagem) {
    nave_parar_descida(&(*personagem)->nave);
}
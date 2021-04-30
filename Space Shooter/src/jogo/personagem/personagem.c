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

#define PERSONAGEM_TIRO_X 50
#define PERSONAGEM_TIRO_Y 50
#define PERSONAGEM_TIRO_LARGURA 11 * 3
#define PERSONAGEM_TIRO_ALTURA 5 * 3
#define PERSONAGEM_TIRO_VELOCIDADE 5
#define PERSONAGEM_TIRO_RECARREGADO 0
#define PERSONAGEM_TIRO_DESCARREGADO 1

struct Tiro {
    int x;
    int y;
    int largura;
    int altura;
    int velocidade;
    int carga;
    SDL_Texture *textura;
};
typedef struct Tiro Tiro;

struct Personagem {
    Nave *nave;
    Tiro tiro;
    SDL_Texture *textura;
};

void personagem_desenhar_tiro(Tiro *tiro, SDL_Renderer *tela);
void personagem_movimentar_tiro(Tiro *tiro);

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

    (*personagem)->tiro.x = PERSONAGEM_TIRO_X;
    (*personagem)->tiro.y = PERSONAGEM_TIRO_Y;
    (*personagem)->tiro.largura = PERSONAGEM_TIRO_LARGURA;
    (*personagem)->tiro.altura = PERSONAGEM_TIRO_ALTURA;
    (*personagem)->tiro.velocidade = PERSONAGEM_TIRO_VELOCIDADE;
    (*personagem)->tiro.carga = PERSONAGEM_TIRO_RECARREGADO;
    (*personagem)->tiro.textura = textura[TEXTURA_TIRO];

    (*personagem)->textura = textura[TEXTURA_SPRITE_PERSONAGEM_1];

    return 0;
}

void personagem_liberar(Personagem **personagem) {
    nave_liberar(&(*personagem)->nave);
    free(*personagem);
}

void personagem_desenhar(Personagem **personagem, SDL_Renderer *tela) {
    if ((*personagem)->tiro.carga == PERSONAGEM_TIRO_DESCARREGADO) {
        personagem_desenhar_tiro(&(*personagem)->tiro, tela);
    }

    nave_desenhar(&(*personagem)->nave, tela, (*personagem)->textura);
}

void personagem_movimentar(Personagem **personagem) {
    nave_movimentar(&(*personagem)->nave);

    if ((*personagem)->tiro.carga == PERSONAGEM_TIRO_DESCARREGADO) {
        personagem_movimentar_tiro(&(*personagem)->tiro);
    }
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

void personagem_atirar(Personagem **personagem) {
    if ((*personagem)->tiro.carga == PERSONAGEM_TIRO_RECARREGADO) {
        (*personagem)->tiro.x = nave_obter_x(&(*personagem)->nave);
        (*personagem)->tiro.y = nave_obter_y(&(*personagem)->nave);
        (*personagem)->tiro.carga = PERSONAGEM_TIRO_DESCARREGADO;
    }
}

void personagem_desenhar_tiro(Tiro *tiro, SDL_Renderer *tela) {
    SDL_Rect retangulo_tiro = {tiro->x, tiro->y, tiro->largura, tiro->altura};
    SDL_RenderCopy(tela, tiro->textura, NULL, &retangulo_tiro);
}

void personagem_movimentar_tiro(Tiro *tiro) {
    tiro->x += tiro->velocidade;

    if (tiro->x > JANELA_LARGURA) {
        tiro->carga = PERSONAGEM_TIRO_RECARREGADO;
    }
}

int personagem_obter_x(Personagem **personagem) {
    return nave_obter_x(&(*personagem)->nave);
}

int personagem_obter_y(Personagem **personagem) {
    return nave_obter_y(&(*personagem)->nave);
}

int personagem_obter_largura(Personagem **personagem) {
    return PERSONAGEM_LARGURA;
}

int personagem_obter_altura(Personagem **personagem) {
    return PERSONAGEM_ALTURA;
}

int personagem_resetar(Personagem **personagem) {
    (*personagem)->tiro.carga = PERSONAGEM_TIRO_RECARREGADO;
    nave_parar_subida(&(*personagem)->nave);
    nave_parar_descida(&(*personagem)->nave);
}
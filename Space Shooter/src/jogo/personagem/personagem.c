#include <stdlib.h>
#include "personagem.h"

struct Tiro {
    int x;
    int y;
    int largura;
    int altura;
    int recarregado;
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

    if ((*personagem)->tiro == NULL) {
        nave_liberar(&(*personagem)->nave);
        free(*personagem);
        return -1;
    }

    (*personagem)->tiro->x = PERSONAGEM_TIRO_X;
    (*personagem)->tiro->y = PERSONAGEM_TIRO_Y;
    (*personagem)->tiro->largura = PERSONAGEM_TIRO_LARGURA;
    (*personagem)->tiro->altura = PERSONAGEM_TIRO_ALTURA;
    (*personagem)->tiro->recarregado = PERSONAGEM_TIRO_RECARREGADO;
    (*personagem)->tiro->textura = textura[TEXTURA_SPRITE_PERSONAGEM_2];

    (*personagem)->textura = textura[TEXTURA_SPRITE_PERSONAGEM_1];
    (*personagem)->vida = PERSONAGEM_VIDA;

    return 0;
}

void personagem_liberar(Personagem **personagem) {
    free((*personagem)->tiro);
    nave_liberar(&(*personagem)->nave);
    free(*personagem);
}

void personagem_desenhar(SDL_Renderer *tela, Personagem **personagem) {
    nave_desenhar(tela, (*personagem)->textura, &(*personagem)->nave);
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

void personagem_atirar(Personagem **personagem) {
    (*personagem)->tiro->x = (*personagem)->nave->x;
    (*personagem)->tiro->y = (*personagem)->nave->y;
    (*personagem)->tiro->recarregado = PERSONAGEM_TIRO_DESCARREGADO;
}

int personagem_mostrar_tiro(Personagem **personagem) {
    return (*personagem)->tiro->recarregado;
}

void personagem_movimentar_tiro(Personagem **personagem) {
    (*personagem)->tiro->x += PERSONAGEM_TIRO_VELOCIDADE;
}

void personagem_desenhar_tiro(SDL_Renderer *tela, Personagem **personagem) {
    SDL_Rect retangulo_tiro = {
        (*personagem)->tiro->x,
        (*personagem)->tiro->y,
        (*personagem)->tiro->largura,
        (*personagem)->tiro->altura
    };
    SDL_RenderCopy(tela, (*personagem)->tiro->textura, NULL, &retangulo_tiro);

    if ((*personagem)->tiro->x > JANELA_LARGURA) {
        (*personagem)->tiro->recarregado = PERSONAGEM_TIRO_RECARREGADO;
    }
}
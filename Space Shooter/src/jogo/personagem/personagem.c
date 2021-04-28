#include <stdlib.h>
#include "personagem.h"

int personagem_criar(Personagem **personagem, SDL_Texture *textura) {
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

    (*personagem)->textura = textura;
    (*personagem)->vida = PERSONAGEM_VIDA;

    return 0;
}

void personagem_liberar(Personagem **personagem) {
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
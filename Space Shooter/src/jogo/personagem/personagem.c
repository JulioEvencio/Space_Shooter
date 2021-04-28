#include <stdlib.h>
#include "personagem.h"

void verificar_tecla_pressionada(SDL_Event *evento, Personagem **personagem);
void verificar_tecla_solta(SDL_Event *evento, Personagem **personagem);

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

void personagem_evento(SDL_Event *evento, Personagem **personagem) {
    if ((*evento).type == SDL_KEYDOWN) {
        verificar_tecla_pressionada(evento, personagem);
    }

    if ((*evento).type == SDL_KEYUP) {
        verificar_tecla_solta(evento, personagem);
    }
}

void verificar_tecla_pressionada(SDL_Event *evento, Personagem **personagem) {
    switch ((*evento).key.keysym.sym) {
        case SDLK_UP:
            personagem_subir(personagem);
            break;

        case SDLK_DOWN:
            personagem_descer(personagem);
            break;

        case SDLK_SPACE:
            puts("tecla espaco pressionada");
            break;
    }
}

void verificar_tecla_solta(SDL_Event *evento, Personagem **personagem) {
    switch ((*evento).key.keysym.sym) {
        case SDLK_UP:
            personagem_parar_subida(personagem);
            break;

        case SDLK_DOWN:
            personagem_parar_descida(personagem);
            break;

        case SDLK_SPACE:
            puts("tecla espaco solta");
            break;
    }
}
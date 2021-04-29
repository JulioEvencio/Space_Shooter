#include <stdlib.h>
#include "jogo.h"

void jogo_verificar_tecla_pressionada(SDL_Event *evento, Jogo **jogo);
void jogo_verificar_tecla_solta(SDL_Event *evento, Jogo **jogo);

int jogo_inicializar(Jogo **jogo, SDL_Texture *textura[]) {
    *jogo = malloc(sizeof **jogo);

    if (*jogo == NULL) return -1;

    if (personagem_criar(&(*jogo)->jogador, textura)) {
        free(*jogo);
        return -1;
    }

    return 0;
}

void jogo_liberar(Jogo **jogo) {
    personagem_liberar(&(*jogo)->jogador);
    free(*jogo);
}

void jogo_tela(SDL_Renderer *tela, SDL_Texture *textura[], Jogo **jogo) {
    SDL_Rect fundo = {JOGO_FUNDO_X, JOGO_FUNDO_Y, JOGO_FUNDO_LARGURA, JOGO_FUNDO_ALTURA};
    SDL_RenderCopy(tela, textura[TEXTURA_BACKGROUND], NULL, &fundo);

    personagem_desenhar(tela, &(*jogo)->jogador);
    personagem_movimentar(&(*jogo)->jogador);

    if (!personagem_mostrar_tiro(&(*jogo)->jogador)) {
        personagem_desenhar_tiro(tela, &(*jogo)->jogador);
        personagem_movimentar_tiro(&(*jogo)->jogador);
    }

    /*  Code */
}

void jogo_evento(SDL_Event *evento, Jogo **jogo) {
    if ((*evento).type == SDL_KEYDOWN) {
        jogo_verificar_tecla_pressionada(evento, jogo);
    }

    if ((*evento).type == SDL_KEYUP) {
        jogo_verificar_tecla_solta(evento, jogo);
    }
}

void jogo_verificar_tecla_pressionada(SDL_Event *evento, Jogo **jogo) {
    switch ((*evento).key.keysym.sym) {
        case SDLK_UP:
            personagem_subir(&(*jogo)->jogador);
            break;

        case SDLK_DOWN:
            personagem_descer(&(*jogo)->jogador);
            break;

        case SDLK_SPACE:
            if (personagem_mostrar_tiro(&(*jogo)->jogador)) {
                personagem_atirar(&(*jogo)->jogador);
            }
            break;
    }
}

void jogo_verificar_tecla_solta(SDL_Event *evento, Jogo **jogo) {
    switch ((*evento).key.keysym.sym) {
        case SDLK_UP:
            personagem_parar_subida(&(*jogo)->jogador);
            break;

        case SDLK_DOWN:
            personagem_parar_descida(&(*jogo)->jogador);
            break;

        case SDLK_SPACE:
            /* puts("tecla espaco solta"); */
            break;
    }
}
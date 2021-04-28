#include "jogo.h"

void verificar_tecla_pressionada(SDL_Event *evento, Personagem **personagem);
void verificar_tecla_solta(SDL_Event *evento, Personagem **personagem);

void jogo_tela(SDL_Renderer *tela, SDL_Texture *textura[], Personagem **jogador) {
    SDL_Rect fundo = {JOGO_FUNDO_X, JOGO_FUNDO_Y, JOGO_FUNDO_LARGURA, JOGO_FUNDO_ALTURA};
    SDL_RenderCopy(tela, textura[TEXTURA_BACKGROUND], NULL, &fundo);

    personagem_desenhar(tela, jogador);
    personagem_movimentar(jogador);

    /*  Code */
}

void jogo_evento(SDL_Event *evento, Personagem **personagem) {
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
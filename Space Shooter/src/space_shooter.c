#include <stdio.h>
#include "space_shooter.h"

int carregar_texturas(SDL_Renderer *tela, SDL_Texture *textura[]) {
    SDL_Surface *imagem = NULL;

    for (int i = 0; i < TEXTURA_QUANTIDADE; i++) {
        imagem = IMG_Load(textura_arquivo[i]);
        if (imagem == NULL) return -1;
        textura[i] = SDL_CreateTextureFromSurface(tela, imagem);
        SDL_FreeSurface(imagem);
    }

    return 0;
}

void liberar_texturas(SDL_Texture *textura[]) {
    for (int i = 0; i < TEXTURA_QUANTIDADE; i++) {
        SDL_DestroyTexture(textura[i]);
    }
}

void verificar_tecla_pressionada(SDL_Event *evento, Nave **jogador) {
    switch ((*evento).key.keysym.sym) {
        case SDLK_UP:
            nave_subir(jogador);
            break;

        case SDLK_DOWN:
            nave_descer(jogador);
            break;

        case SDLK_SPACE:
            puts("tecla espaco pressionada");
            break;
    }
}

void verificar_tecla_solta(SDL_Event *evento, Nave **jogador) {
    switch ((*evento).key.keysym.sym) {
        case SDLK_UP:
            nave_parar_subida(jogador);
            break;

        case SDLK_DOWN:
            nave_parar_descida(jogador);
            break;

        case SDLK_SPACE:
            puts("tecla espaco solta");
            break;
    }
}
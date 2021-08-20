#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../../janela/janela.h"
#include "fundo.h"

enum Enum_Fundo {
    FUNDO_1,
    FUNDO_2,
    FUNDO_3,
    FUNDO_4,
    FUNDO_5,
    FUNDO_6,
    FUNDO_QUANTIDADE = 6,

    FUNDO_RESET_DIREITA = JANELA_LARGURA,
    FUNDO_RESET_ESQUERDA = -JANELA_LARGURA,
    FUNDO_RESET_Y = -JANELA_ALTURA
};

struct Movimento {
    int direita;
    int esquerda;
    int velocidade;
};
typedef struct Movimento Movimento;

struct Fundo {
    Movimento movimento;
    SDL_Rect fundo[FUNDO_QUANTIDADE];
    SDL_Event *evento;
    SDL_Renderer *tela;
    SDL_Texture *textura;
};

int fundo_criar(Fundo **fundo, SDL_Renderer *tela, SDL_Event *evento) {
    *fundo = malloc(sizeof **fundo);

    if (*fundo == NULL) return FUNDO_SEM_MEMORIA;

    SDL_Surface *imagem = IMG_Load("../sprites/Topview Sci-Fi Patreon Collection/fundo/fundo.png");

    if (imagem == NULL) {
        free(*fundo);
        return FUNDO_ERRO_AO_CARREGAR_IMAGEM;
    }

    (*fundo)->textura = SDL_CreateTextureFromSurface(tela, imagem);
    SDL_FreeSurface(imagem);

    for (int i = 0; i < FUNDO_QUANTIDADE; i++) {
        (*fundo)->fundo[i].w = JANELA_LARGURA;
        (*fundo)->fundo[i].h = JANELA_ALTURA;

        if (((i + 1) % 2) != 0) (*fundo)->fundo[i].y = 0;
        else (*fundo)->fundo[i].y = FUNDO_RESET_Y;
    }

    (*fundo)->tela = tela;
    (*fundo)->evento = evento;
    (*fundo)->movimento.velocidade = 2;

    (*fundo)->fundo[FUNDO_1].x = FUNDO_RESET_ESQUERDA;
    (*fundo)->fundo[FUNDO_2].x = FUNDO_RESET_ESQUERDA;

    (*fundo)->fundo[FUNDO_3].x = 0;
    (*fundo)->fundo[FUNDO_4].x = 0;

    (*fundo)->fundo[FUNDO_5].x = FUNDO_RESET_DIREITA;
    (*fundo)->fundo[FUNDO_6].x = FUNDO_RESET_DIREITA;

    fundo_resetar_movimento(fundo);

    return FUNDO_SUCESSO;
}

void fundo_liberar(Fundo **fundo) {
    SDL_DestroyTexture((*fundo)->textura);
    free(*fundo);
}

void fundo_logica(Fundo **fundo) {
    for (int i = 0; i < FUNDO_QUANTIDADE; i++) {
        SDL_RenderCopy((*fundo)->tela, (*fundo)->textura, NULL, &(*fundo)->fundo[i]);

        (*fundo)->fundo[i].y += (*fundo)->movimento.velocidade;

        if ((*fundo)->fundo[i].y == JANELA_ALTURA) (*fundo)->fundo[i].y = FUNDO_RESET_Y;

        if ((*fundo)->movimento.direita) (*fundo)->fundo[i].x -= (*fundo)->movimento.velocidade;

        if ((*fundo)->movimento.esquerda) (*fundo)->fundo[i].x += (*fundo)->movimento.velocidade;

        if ((*fundo)->fundo[i].x + (*fundo)->fundo[i].w == FUNDO_RESET_ESQUERDA) {
            (*fundo)->fundo[i].x = FUNDO_RESET_DIREITA;
        }

        if ((*fundo)->fundo[i].x == FUNDO_RESET_DIREITA + (*fundo)->fundo[i].w) {
            (*fundo)->fundo[i].x = FUNDO_RESET_ESQUERDA;
        }
    }
}

void fundo_evento(Fundo **fundo) {
    if ((*fundo)->evento->type == SDL_KEYDOWN) {
        if ((*fundo)->evento->key.keysym.sym == SDLK_RIGHT) (*fundo)->movimento.direita = 1;

        if ((*fundo)->evento->key.keysym.sym == SDLK_LEFT) (*fundo)->movimento.esquerda = 1;
    }

    if ((*fundo)->evento->type == SDL_KEYUP) {
        if ((*fundo)->evento->key.keysym.sym == SDLK_RIGHT) (*fundo)->movimento.direita = 0;

        if ((*fundo)->evento->key.keysym.sym == SDLK_LEFT) (*fundo)->movimento.esquerda = 0;
    }
}

void fundo_resetar_movimento(Fundo **fundo) {
    (*fundo)->movimento.direita = 0;
    (*fundo)->movimento.esquerda = 0;
}
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "../../../janela/janela.h"
#include "tiro.h"

enum Enum_Tiro_Textura {
    TIRO_TEXTURA_1,
    TIRO_TEXTURA_2,
    TIRO_TEXTURA_QUANTIDADE = 2
};

struct Movimento {
    int direita;
    int esquerda;
    int invalido;
    int velocidade_x;
    int velocidade_y;
};
typedef struct Movimento Movimento;

struct Tiro {
    Movimento movimento;
    int sprite[TIRO_QUANTIDADE];
    SDL_Rect tiro[TIRO_QUANTIDADE];
    SDL_Event *evento;
    SDL_Renderer *tela;
    Mix_Chunk *audio;
    SDL_Texture *textura[TIRO_TEXTURA_QUANTIDADE];
};

int tiro_criar(Tiro **tiro, SDL_Renderer *tela, SDL_Event *evento) {
    *tiro = malloc(sizeof **tiro);

    if (*tiro == NULL) return TIRO_SEM_MEMORIA;

    const char *tiro_arquivo[TIRO_TEXTURA_QUANTIDADE] = {
        "sprites/Topview Sci-Fi Patreon Collection/tiro/tiro_0.png",
        "sprites/Topview Sci-Fi Patreon Collection/tiro/tiro_1.png"
    };

    for (int i = 0; i < TIRO_TEXTURA_QUANTIDADE; i++) {
        SDL_Surface *imagem = IMG_Load(tiro_arquivo[i]);

        if (imagem == NULL) {
            while (i > 0) SDL_DestroyTexture((*tiro)->textura[--i]);

            free(*tiro);

            return TIRO_ERRO_AO_CARREGAR_IMAGEM;
        }

        (*tiro)->textura[i] = SDL_CreateTextureFromSurface(tela, imagem);
        SDL_FreeSurface(imagem);
    }

    (*tiro)->audio = Mix_LoadWAV("sounds/laser/339169__debsound__arcade-laser-014.wav");

    if ((*tiro)->audio == NULL) {
        for (int i = 0; i < TIRO_TEXTURA_QUANTIDADE; i++) {
            SDL_DestroyTexture((*tiro)->textura[i]);
        }

        free(*tiro);

        return TIRO_ERRO_AO_CARREGAR_AUDIO;
    }

    (*tiro)->evento = evento;
    (*tiro)->tela = tela;
    (*tiro)->movimento.velocidade_x = 2;
    (*tiro)->movimento.velocidade_y = 10;
    (*tiro)->movimento.invalido = -999;

    tiro_resetar(tiro);

    return TIRO_SUCESSO;
}

void tiro_liberar(Tiro **tiro) {
    Mix_FreeChunk((*tiro)->audio);

    for (int i = 0; i < TIRO_TEXTURA_QUANTIDADE; i++) {
        SDL_DestroyTexture((*tiro)->textura[i]);
    }

    free(*tiro);
}

void tiro_logica(Tiro **tiro) {
    for (int i = 0; i < TIRO_QUANTIDADE; i++) {
        if ((*tiro)->tiro[i].x != (*tiro)->movimento.invalido) {
            SDL_RenderCopy((*tiro)->tela, (*tiro)->textura[(*tiro)->sprite[i]++], NULL, &(*tiro)->tiro[i]);

            (*tiro)->tiro[i].y -= (*tiro)->movimento.velocidade_y;

            if ((*tiro)->sprite[i] == TIRO_TEXTURA_QUANTIDADE) (*tiro)->sprite[i] = TIRO_TEXTURA_1;

            if ((*tiro)->tiro[i].y + (*tiro)->tiro[i].h < 0) (*tiro)->tiro[i].y = (*tiro)->movimento.invalido;

            if ((*tiro)->movimento.direita) (*tiro)->tiro[i].x -= (*tiro)->movimento.velocidade_x;
            if ((*tiro)->movimento.esquerda) (*tiro)->tiro[i].x += (*tiro)->movimento.velocidade_x;
        }
    }
}

void tiro_evento(Tiro **tiro) {
    if ((*tiro)->evento->type == SDL_KEYDOWN) {
        if ((*tiro)->evento->key.keysym.sym == SDLK_RIGHT) (*tiro)->movimento.direita = 1;

        if ((*tiro)->evento->key.keysym.sym == SDLK_LEFT) (*tiro)->movimento.esquerda = 1;
    }

    if ((*tiro)->evento->type == SDL_KEYUP) {
        if ((*tiro)->evento->key.keysym.sym == SDLK_RIGHT) (*tiro)->movimento.direita = 0;

        if ((*tiro)->evento->key.keysym.sym == SDLK_LEFT) (*tiro)->movimento.esquerda = 0;
    }
}

void tiro_atirar(Tiro **tiro, int x, int y) {
    for (int i = 0; i < TIRO_QUANTIDADE; i++) {
        if ((*tiro)->tiro[i].y == (*tiro)->movimento.invalido) {
            Mix_PlayChannel(-1, (*tiro)->audio, 0);

            (*tiro)->tiro[i].x = x;
            (*tiro)->tiro[i].y = y;
            break;
        }
    }
}

SDL_Rect *tiro_obter(Tiro **tiro) {
    return (*tiro)->tiro;
}

void tiro_colisao(Tiro **tiro, int i) {
    (*tiro)->tiro[i].y = (*tiro)->movimento.invalido;
}

void tiro_resetar(Tiro **tiro) {
    (*tiro)->movimento.direita = 0;
    (*tiro)->movimento.esquerda = 0;

    for (int i = 0; i < TIRO_QUANTIDADE; i++) {
        (*tiro)->sprite[i] = TIRO_TEXTURA_1;

        (*tiro)->tiro[i].x = (*tiro)->movimento.invalido;
        (*tiro)->tiro[i].y = (*tiro)->movimento.invalido;
        (*tiro)->tiro[i].w = 16;
        (*tiro)->tiro[i].h = 16;
    }
}
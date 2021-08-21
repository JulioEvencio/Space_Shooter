#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../../janela/janela.h"
#include "meteoro.h"

#define METEORO_GERAR_X rand() % (JANELA_LARGURA - (*meteoro)->meteoro[i].w)
#define METEORO_GERAR_Y (rand() % JANELA_ALTURA) - JANELA_ALTURA

enum Enum_Meteoro_Textura {
    METEORO_TEXTURA_1,
    METEORO_TEXTURA_EXPLOSAO_1,
    METEORO_TEXTURA_EXPLOSAO_2,
    METEORO_TEXTURA_EXPLOSAO_3,
    METEORO_TEXTURA_EXPLOSAO_4,
    METEORO_TEXTURA_EXPLOSAO_5,
    METEORO_TEXTURA_EXPLOSAO_6,
    METEORO_TEXTURA_EXPLOSAO_7,
    METEORO_TEXTURA_QUANTIDADE = 8
};

struct Movimento {
    int direita;
    int esquerda;
    int velocidade_x;
    int velocidade_y;
};
typedef struct Movimento Movimento;

struct Sprites {
    int explodiu;
    int sprites;
};
typedef struct Sprites Sprites;

struct Meteoro {
    Movimento movimento;
    Sprites sprites[METEORO_QUANTIDADE];
    SDL_Rect meteoro[METEORO_QUANTIDADE];
    SDL_Event *evento;
    SDL_Renderer *tela;
    SDL_Texture *textura[METEORO_TEXTURA_QUANTIDADE];
};

int meteoro_criar(Meteoro **meteoro, SDL_Renderer *tela, SDL_Event *evento) {
    *meteoro = malloc(sizeof **meteoro);

    if (*meteoro == NULL) return METEORO_SEM_MEMORIA;

    const char *meteoro_arquivo[METEORO_TEXTURA_QUANTIDADE] = {
        "sprites/Topview Sci-Fi Patreon Collection/meteoro/meteoro_0.png",
        "sprites/Topview Sci-Fi Patreon Collection/explosao/explosao_1.png",
        "sprites/Topview Sci-Fi Patreon Collection/explosao/explosao_2.png",
        "sprites/Topview Sci-Fi Patreon Collection/explosao/explosao_3.png",
        "sprites/Topview Sci-Fi Patreon Collection/explosao/explosao_4.png",
        "sprites/Topview Sci-Fi Patreon Collection/explosao/explosao_5.png",
        "sprites/Topview Sci-Fi Patreon Collection/explosao/explosao_6.png",
        "sprites/Topview Sci-Fi Patreon Collection/explosao/explosao_7.png"
    };

    for (int i = 0; i < METEORO_TEXTURA_QUANTIDADE; i++) {
        SDL_Surface *imagem = IMG_Load(meteoro_arquivo[i]);

        if (imagem == NULL) {
            while (i > 0) SDL_DestroyTexture((*meteoro)->textura[--i]);

            free(*meteoro);

            return METEORO_ERRO_AO_CARREGAR_IMAGEM;
        }

        (*meteoro)->textura[i] = SDL_CreateTextureFromSurface(tela, imagem);
        SDL_FreeSurface(imagem);
    }

    (*meteoro)->evento = evento;
    (*meteoro)->tela = tela;
    (*meteoro)->movimento.velocidade_x = 2;
    (*meteoro)->movimento.velocidade_y = 6;

    meteoro_resetar(meteoro);

    return METEORO_SUCESSO;
}

void meteoro_liberar(Meteoro **meteoro) {
    for (int i = 0; i < METEORO_TEXTURA_QUANTIDADE; i++) {
        SDL_DestroyTexture((*meteoro)->textura[i]);
    }

    free(*meteoro);
}

void meteoro_logica(Meteoro **meteoro) {
    for (int i = 0; i < METEORO_QUANTIDADE; i++) {
        if ((*meteoro)->movimento.direita) (*meteoro)->meteoro[i].x -= (*meteoro)->movimento.velocidade_x;
        if ((*meteoro)->movimento.esquerda) (*meteoro)->meteoro[i].x += (*meteoro)->movimento.velocidade_x;

        if ((*meteoro)->sprites[i].explodiu) {
            (*meteoro)->meteoro[i].y += 100;

            SDL_RenderCopy((*meteoro)->tela, (*meteoro)->textura[(*meteoro)->sprites[i].sprites++], NULL, &(*meteoro)->meteoro[i]);

            if ((*meteoro)->sprites[i].sprites == METEORO_TEXTURA_QUANTIDADE) {
                (*meteoro)->sprites[i].explodiu = 0;
                (*meteoro)->sprites[i].sprites = METEORO_TEXTURA_1;
                (*meteoro)->meteoro[i].w = 34;
                (*meteoro)->meteoro[i].h = 32;
                (*meteoro)->meteoro[i].x = METEORO_GERAR_X;
                (*meteoro)->meteoro[i].y = METEORO_GERAR_Y;
            } else {
                (*meteoro)->meteoro[i].y -= 100;
            }
        } else {
            SDL_RenderCopy((*meteoro)->tela, (*meteoro)->textura[(*meteoro)->sprites[i].sprites], NULL, &(*meteoro)->meteoro[i]);

            (*meteoro)->meteoro[i].y += (*meteoro)->movimento.velocidade_y;

            if ((*meteoro)->meteoro[i].y > JANELA_ALTURA) {
                (*meteoro)->meteoro[i].x = METEORO_GERAR_X;
                (*meteoro)->meteoro[i].y = METEORO_GERAR_Y;
            }
        }
    }
}

void meteoro_evento(Meteoro **meteoro) {
    if ((*meteoro)->evento->type == SDL_KEYDOWN) {
        if ((*meteoro)->evento->key.keysym.sym == SDLK_RIGHT) (*meteoro)->movimento.direita = 1;

        if ((*meteoro)->evento->key.keysym.sym == SDLK_LEFT) (*meteoro)->movimento.esquerda = 1;
    }

    if ((*meteoro)->evento->type == SDL_KEYUP) {
        if ((*meteoro)->evento->key.keysym.sym == SDLK_RIGHT) (*meteoro)->movimento.direita = 0;

        if ((*meteoro)->evento->key.keysym.sym == SDLK_LEFT) (*meteoro)->movimento.esquerda = 0;
    }
}

SDL_Rect *meteoro_obter(Meteoro **meteoro) {
    return (*meteoro)->meteoro;
}

void meteoro_colisao(Meteoro **meteoro, int i) {
    (*meteoro)->sprites[i].explodiu = 1;
    (*meteoro)->meteoro[i].y -= 100;
    (*meteoro)->meteoro[i].w = 80;
    (*meteoro)->meteoro[i].h = 80;
}

void meteoro_resetar(Meteoro **meteoro) {
    (*meteoro)->movimento.direita = 0;
    (*meteoro)->movimento.esquerda = 0;

    for (int i = 0; i < METEORO_QUANTIDADE; i++) {
        (*meteoro)->meteoro[i].x = METEORO_GERAR_X;
        (*meteoro)->meteoro[i].y = METEORO_GERAR_Y;
        (*meteoro)->meteoro[i].w = 34;
        (*meteoro)->meteoro[i].h = 32;
        (*meteoro)->sprites[i].explodiu = 0;
        (*meteoro)->sprites[i].sprites = METEORO_TEXTURA_1;
    }
}
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include "../../janela/janela.h"
#include "tiro/tiro.h"
#include "player.h"

enum Enum_Player_Textura {
    PLAYER_TEXTURA_1,
    PLAYER_TEXTURA_2,
    PLAYER_TEXTURA_EXPLOSAO_1,
    PLAYER_TEXTURA_EXPLOSAO_2,
    PLAYER_TEXTURA_EXPLOSAO_3,
    PLAYER_TEXTURA_EXPLOSAO_4,
    PLAYER_TEXTURA_EXPLOSAO_5,
    PLAYER_TEXTURA_EXPLOSAO_6,
    PLAYER_TEXTURA_EXPLOSAO_7,
    PLAYER_TEXTURA_QUANTIDADE = 9
};

struct Movimento {
    int cima;
    int baixo;
    int direita;
    int esquerda;
    int velocidade;
};
typedef struct Movimento Movimento;

struct Player {
    int explodiu;
    int sprite;
    SDL_Rect player;
    Movimento movimento;
    Tiro *tiro;
    SDL_Event *evento;
    SDL_Renderer *tela;
    SDL_Texture *textura[PLAYER_TEXTURA_QUANTIDADE];
};

int player_criar(Player **player, SDL_Renderer *tela, SDL_Event *evento) {
    *player = malloc(sizeof **player);

    if (*player == NULL) return PLAYER_SEM_MEMORIA;

    const char *player_arquivo[PLAYER_TEXTURA_QUANTIDADE] = {
        "sprites/Topview Sci-Fi Patreon Collection/player/player_0.png",
        "sprites/Topview Sci-Fi Patreon Collection/player/player_1.png",
        "sprites/Topview Sci-Fi Patreon Collection/explosao/explosao_1.png",
        "sprites/Topview Sci-Fi Patreon Collection/explosao/explosao_2.png",
        "sprites/Topview Sci-Fi Patreon Collection/explosao/explosao_3.png",
        "sprites/Topview Sci-Fi Patreon Collection/explosao/explosao_4.png",
        "sprites/Topview Sci-Fi Patreon Collection/explosao/explosao_5.png",
        "sprites/Topview Sci-Fi Patreon Collection/explosao/explosao_6.png",
        "sprites/Topview Sci-Fi Patreon Collection/explosao/explosao_7.png"
    };

    for (int i = 0; i < PLAYER_TEXTURA_QUANTIDADE; i++) {
        SDL_Surface *imagem = IMG_Load(player_arquivo[i]);

        if (imagem == NULL) {
            while (i > 0) SDL_DestroyTexture((*player)->textura[--i]);

            free(*player);

            return PLAYER_ERRO_AO_CARREGAR_IMAGEM;
        }

        (*player)->textura[i] = SDL_CreateTextureFromSurface(tela, imagem);
        SDL_FreeSurface(imagem);
    }

    if (tiro_criar(&(*player)->tiro, tela, evento)) {
        for (int i = 0; i < PLAYER_TEXTURA_QUANTIDADE; i++) {
            SDL_DestroyTexture((*player)->textura[i]);
        }

        free(*player);

        return PLAYER_ERRO_AO_CARREGAR_TIRO;
    }

    (*player)->tela = tela;
    (*player)->evento = evento;
    (*player)->movimento.velocidade = 4;

    player_resetar(player);

    return PLAYER_SUCESSO;
}

void player_liberar(Player **player) {
    tiro_liberar(&(*player)->tiro);

    for (int i = 0; i < PLAYER_TEXTURA_QUANTIDADE; i++) {
        SDL_DestroyTexture((*player)->textura[i]);
    }

    free(*player);
}

int player_logica(Player **player) {
    tiro_logica(&(*player)->tiro);

    SDL_RenderCopy((*player)->tela, (*player)->textura[(*player)->sprite++], NULL, &(*player)->player);

    if ((*player)->explodiu) {
        if ((*player)->sprite == PLAYER_TEXTURA_QUANTIDADE) return PLAYER_GAME_OVER;
    } else {
        if ((*player)->sprite == PLAYER_TEXTURA_EXPLOSAO_1) (*player)->sprite = PLAYER_TEXTURA_1;

        if ((*player)->movimento.cima && (*player)->player.y > 0) (*player)->player.y -= (*player)->movimento.velocidade;

        if ((*player)->movimento.baixo && (*player)->player.y + (*player)->player.h < JANELA_ALTURA) (*player)->player.y += (*player)->movimento.velocidade;

        if ((*player)->movimento.direita && (*player)->player.x + (*player)->player.w < JANELA_LARGURA) (*player)->player.x += (*player)->movimento.velocidade;

        if ((*player)->movimento.esquerda && (*player)->player.x > 0) (*player)->player.x -= (*player)->movimento.velocidade;
    }

    return PLAYER_CONTINUE;
}

void player_evento(Player **player) {
    tiro_evento(&(*player)->tiro);

    if ((*player)->evento->type == SDL_KEYDOWN) {
        if ((*player)->evento->key.keysym.sym == SDLK_UP) (*player)->movimento.cima = 1;

        if ((*player)->evento->key.keysym.sym == SDLK_DOWN) (*player)->movimento.baixo = 1;

        if ((*player)->evento->key.keysym.sym == SDLK_RIGHT) (*player)->movimento.direita = 1;

        if ((*player)->evento->key.keysym.sym == SDLK_LEFT) (*player)->movimento.esquerda = 1;

        if ((*player)->evento->key.keysym.sym == SDLK_SPACE) {
            /* Calculando onde eh o meio do player. O 8 eh metade da largura do tiro */
            /* int x = (*player)->player.x + ((*player)->player.w / 2) - 8; */

            tiro_atirar(&(*player)->tiro, (*player)->player.x + 20, (*player)->player.y);
            tiro_atirar(&(*player)->tiro, (*player)->player.x + 60, (*player)->player.y);
        }
    }

    if ((*player)->evento->type == SDL_KEYUP) {
        if ((*player)->evento->key.keysym.sym == SDLK_UP) (*player)->movimento.cima = 0;

        if ((*player)->evento->key.keysym.sym == SDLK_DOWN) (*player)->movimento.baixo = 0;

        if ((*player)->evento->key.keysym.sym == SDLK_RIGHT) (*player)->movimento.direita = 0;

        if ((*player)->evento->key.keysym.sym == SDLK_LEFT) (*player)->movimento.esquerda = 0;
    }
}

SDL_Rect player_obter(Player **player) {
    return (*player)->player;
}

void player_colisao(Player **player) {
    (*player)->explodiu = 1;
    (*player)->player.w = 160;
    (*player)->player.h = 160;
}

SDL_Rect *player_obter_tiro(Player **player) {
    return tiro_obter(&(*player)->tiro);
}

void player_colisao_tiro(Player **player, int i) {
    tiro_colisao(&(*player)->tiro, i);
}

void player_resetar(Player **player) {
    tiro_resetar(&(*player)->tiro);

    (*player)->explodiu = 0;
    (*player)->sprite = PLAYER_TEXTURA_1;

    (*player)->player.w = 84;
    (*player)->player.h = 88;
    (*player)->player.x = JANELA_LARGURA / 2 - (*player)->player.w / 2;
    (*player)->player.y = JANELA_ALTURA - (*player)->player.h;

    (*player)->movimento.cima = 0;
    (*player)->movimento.baixo = 0;
    (*player)->movimento.direita = 0;
    (*player)->movimento.esquerda = 0;
}
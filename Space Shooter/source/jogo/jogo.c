#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../janela/janela.h"
#include "fundo/fundo.h"
#include "meteoro/meteoro.h"
#include "player/player.h"
#include "jogo.h"

struct Jogo {
    Fundo *fundo;
    Meteoro *meteoro;
    Player *player;
};

void jogo_colisao(Jogo **jogo);
void jogo_resetar(Jogo **jogo);

int jogo_criar(Jogo **jogo, SDL_Renderer *tela, SDL_Event *evento) {
    *jogo = malloc(sizeof **jogo);

    if (*jogo == NULL) return JOGO_SEM_MEMORIA;

    if (fundo_criar(&(*jogo)->fundo, tela, evento)) {
        free(*jogo);
        return JOGO_ERRO_AO_CARREGAR_FUNDO;
    }

    if (meteoro_criar(&(*jogo)->meteoro, tela, evento)) {
        fundo_liberar(&(*jogo)->fundo);
        free(*jogo);
        return JOGO_ERRO_AO_CARREGAR_METEORO;
    }

    if (player_criar(&(*jogo)->player, tela, evento)) {
        meteoro_liberar(&(*jogo)->meteoro);
        fundo_liberar(&(*jogo)->fundo);
        free(*jogo);
        return JOGO_ERRO_AO_CARREGAR_PLAYER;
    }

    return JOGO_SUCESSO;
}

void jogo_liberar(Jogo **jogo) {
    player_liberar(&(*jogo)->player);
    meteoro_liberar(&(*jogo)->meteoro);
    fundo_liberar(&(*jogo)->fundo);
    free(*jogo);
}

int jogo_logica(Jogo **jogo) {
    fundo_logica(&(*jogo)->fundo);

    meteoro_logica(&(*jogo)->meteoro);

    if (player_logica(&(*jogo)->player)) {
        if (SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Game Over", "You died!", NULL))
            SDL_Log("%s", SDL_GetError());

        jogo_resetar(jogo);

        return JANELA_MENU;
    }

    jogo_colisao(jogo);

    return JANELA_JOGO;
}

void jogo_evento(Jogo **jogo) {
    fundo_evento(&(*jogo)->fundo);

    meteoro_evento(&(*jogo)->meteoro);

    player_evento(&(*jogo)->player);
}

void jogo_colisao(Jogo **jogo) {
    SDL_Rect player = player_obter(&(*jogo)->player);
    SDL_Rect *tiro = player_obter_tiro(&(*jogo)->player);
    SDL_Rect *meteoro = meteoro_obter(&(*jogo)->meteoro);

    /* 5 eh o numero de meteoros */
    for (int i = 0; i < 5; i++) {
        /* Meteoro vs Tiro */
        /* 6 eh o numero de tiros */
        for (int j = 0; j < 6; j++) {
            if (
                tiro[j].x < meteoro[i].x + meteoro[i].w &&
                tiro[j].x + tiro[j].w > meteoro[i].x &&
                tiro[j].y < meteoro[i].y + meteoro[i].h &&
                tiro[j].y + tiro[j].h > meteoro[i].y
            ) {
                meteoro_colisao(&(*jogo)->meteoro, i);
                player_colisao_tiro(&(*jogo)->player, j);
                break;
            }
        }

        /* Meteoro vs Player */
        if (
            player.x < meteoro[i].x + meteoro[i].w &&
            player.x + player.w > meteoro[i].x &&
            player.y < meteoro[i].y + meteoro[i].h &&
            player.y + player.h > meteoro[i].y
        ) {
            player_colisao(&(*jogo)->player);
            meteoro_colisao(&(*jogo)->meteoro, i);
        }
    }
}

void jogo_resetar(Jogo **jogo) {
    fundo_resetar_movimento(&(*jogo)->fundo);

    meteoro_resetar(&(*jogo)->meteoro);

    player_resetar(&(*jogo)->player);
}
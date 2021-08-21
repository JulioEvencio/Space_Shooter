#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../janela/janela.h"
#include "menu.h"

enum Enum_Menu_Textura {
    MENU_TEXTURA_PLAY,
    MENU_TEXTURA_PLAY_PRESSIONADO,
    MENU_TEXTURA_FUNDO,
    MENU_TEXTURA_QUANTIDADE = 3
};

struct Menu {
    int jogar;
    int sprite;
    SDL_Rect fundo;
    SDL_Rect play;
    SDL_Event *evento;
    SDL_Renderer *tela;
    SDL_Texture *textura[MENU_TEXTURA_QUANTIDADE];
};

int menu_criar(Menu **menu, SDL_Renderer *tela, SDL_Event *evento) {
    *menu = malloc(sizeof **menu);

    if (*menu == NULL) return MENU_SEM_MEMORIA;

    const char *menu_arquivo[MENU_TEXTURA_QUANTIDADE] = {
        "sprites/Talosaurus - Open Game Art/menu/play.png",
        "sprites/Talosaurus - Open Game Art/menu/play_pressionado.png",
        "sprites/Topview Sci-Fi Patreon Collection/fundo/fundo.png"
    };

    for (int i = 0; i < MENU_TEXTURA_QUANTIDADE; i++) {
        SDL_Surface *imagem = IMG_Load(menu_arquivo[i]);

        if (imagem == NULL) {
            while (i > 0) SDL_DestroyTexture((*menu)->textura[--i]);

            free(*menu);

            return MENU_ERRO_AO_CARREGAR_IMAGEM;
        }

        (*menu)->textura[i] = SDL_CreateTextureFromSurface(tela, imagem);
        SDL_FreeSurface(imagem);
    }

    (*menu)->jogar = 0;
    (*menu)->evento = evento;
    (*menu)->tela = tela;
    (*menu)->sprite = MENU_TEXTURA_PLAY;

    (*menu)->fundo.x = 0;
    (*menu)->fundo.y = 0;
    (*menu)->fundo.w = JANELA_LARGURA;
    (*menu)->fundo.h = JANELA_ALTURA;

    (*menu)->play.w = 96;
    (*menu)->play.h = 64;
    (*menu)->play.x = JANELA_LARGURA / 2 - (*menu)->play.w / 2;
    (*menu)->play.y = JANELA_ALTURA / 2 - (*menu)->play.h / 2;

    return MENU_SUCESSO;
}

void menu_liberar(Menu **menu) {
    for (int i = 0; i < MENU_TEXTURA_QUANTIDADE; i++) {
        SDL_DestroyTexture((*menu)->textura[i]);
    }

    free(*menu);
}

int menu_logica(Menu **menu) {
    SDL_RenderCopy((*menu)->tela, (*menu)->textura[MENU_TEXTURA_FUNDO], NULL, &(*menu)->fundo);

    SDL_RenderCopy((*menu)->tela, (*menu)->textura[(*menu)->sprite], NULL, &(*menu)->play);

    if ((*menu)->jogar) {
        (*menu)->jogar = 0;
        return JANELA_JOGO;
    }

    return JANELA_MENU;
}

void menu_evento(Menu **menu) {
    if ((*menu)->evento->type == SDL_MOUSEBUTTONDOWN) {
        if (
            (*menu)->evento->motion.x > (*menu)->play.x &&
            (*menu)->evento->motion.x < ((*menu)->play.x + (*menu)->play.w) &&
            (*menu)->evento->motion.y > (*menu)->play.y &&
            (*menu)->evento->motion.y < ((*menu)->play.y + (*menu)->play.h)
        )
        {
            (*menu)->sprite = MENU_TEXTURA_PLAY_PRESSIONADO;
        }
    }

    if ((*menu)->evento->type == SDL_MOUSEBUTTONUP) {
        (*menu)->sprite = MENU_TEXTURA_PLAY;

        if (
            (*menu)->evento->motion.x > (*menu)->play.x &&
            (*menu)->evento->motion.x < ((*menu)->play.x + (*menu)->play.w) &&
            (*menu)->evento->motion.y > (*menu)->play.y &&
            (*menu)->evento->motion.y < ((*menu)->play.y + (*menu)->play.h)
        )
        {
            (*menu)->jogar = 1;
        }
    }
}
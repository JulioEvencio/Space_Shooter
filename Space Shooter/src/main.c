#include <stdio.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "space_shooter.h"
#include "menu/menu.h"
#include "jogo/jogo.h"

int main(int argc, char *args[]) {
    int loop = LOOP_MENU;

    Menu *menu = NULL;
    Jogo *jogo = NULL;

    SDL_Window *janela = NULL;
    SDL_Renderer *tela = NULL;
    TTF_Font *fonte = NULL;
    SDL_Texture *textura[TEXTURA_QUANTIDADE];
    SDL_Event evento;

    srand(time(NULL));

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        puts("Erro ao inicializar SDL 2!");
        return 1;
    }

    if (IMG_Init(IMG_INIT_PNG) < 0) {
        puts("Erro ao inicializar SDL image!");
        SDL_Quit();
        return 2;
    }

    if (TTF_Init() < 0) {
        puts("Erro ao inicializar ttf!");
        IMG_Quit();
        SDL_Quit();
        return 3;
    }

    janela = SDL_CreateWindow(
        JANELA_NOME,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        JANELA_LARGURA,
        JANELA_ALTURA,
        SDL_WINDOW_SHOWN
    );

    if (janela == NULL) {
        puts("Erro ao criar janela!");
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return 4;
    }

    tela = SDL_CreateRenderer(
        janela,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (tela == NULL) {
        puts("Erro ao criar tela renderizada!");
        SDL_DestroyWindow(janela);
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return 5;
    }

    fonte = TTF_OpenFont(FONTE_ARQUIVO, FONTE_TAMANHO);

    if (fonte == NULL) {
        puts("Erro ao abrir fonte!");
        SDL_DestroyRenderer(tela);
        SDL_DestroyWindow(janela);
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return 6;
    }

    if (carregar_texturas(tela, textura)) {
        puts("Erro ao carregar texturas!");
        TTF_CloseFont(fonte);
        SDL_DestroyRenderer(tela);
        SDL_DestroyWindow(janela);
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return 7;
    }

    if (menu_criar(&menu, textura)) {
        puts("Erro ao inicializar menu!");
        liberar_texturas(textura);
        TTF_CloseFont(fonte);
        SDL_DestroyRenderer(tela);
        SDL_DestroyWindow(janela);
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return 8;
    }

    if (jogo_criar(&jogo, textura)) {
        puts("Erro ao inicializar o menu!");
        menu_liberar(&menu);
        liberar_texturas(textura);
        TTF_CloseFont(fonte);
        SDL_DestroyRenderer(tela);
        SDL_DestroyWindow(janela);
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return 9;
    }

    while (loop) {
        while (SDL_PollEvent(&evento) != 0) {
            if (evento.type == SDL_QUIT) {
                loop = LOOP_SAIR;
            }

            if (loop == LOOP_MENU) {
                menu_evento(&menu, &evento, &loop);
            }

            if (loop == LOOP_JOGO) {
                jogo_evento(&jogo, &evento);
            }
        }

        SDL_SetRenderDrawColor(tela, JANELA_COR);
        SDL_RenderClear(tela);

        switch (loop) {
            case LOOP_MENU:
                menu_tela(&menu, tela);
            break;

            case LOOP_JOGO:
                jogo_tela(&jogo, tela, fonte, &loop);
            break;
        }

        SDL_RenderPresent(tela);

        SDL_Delay(JANELA_DELAY);
    }

    jogo_liberar(&jogo);
    menu_liberar(&menu);
    liberar_texturas(textura);
    TTF_CloseFont(fonte);
    SDL_DestroyRenderer(tela);
    SDL_DestroyWindow(janela);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}
#include <stdio.h>
#include "space_shooter.h"
#include "menu/menu.h"
#include "jogo/jogo.h"

int main(int argc, char *args[]) {
    int loop = LOOP_MENU;

    Jogo *jogo = NULL;

    SDL_Window *janela = NULL;
    SDL_Renderer *tela = NULL;
    SDL_Texture *textura[TEXTURA_QUANTIDADE];
    SDL_Event evento;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        puts("Erro ao inicializar SDL 2!");
        return 1;
    }

    if (IMG_Init(IMG_INIT_PNG) < 0) {
        puts("Erro ao inicializar SDL image!");
        SDL_Quit();
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
        IMG_Quit();
        SDL_Quit();
        return 2;
    }

    tela = SDL_CreateRenderer(
        janela,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (tela == NULL) {
        puts("Erro ao criar tela renderizada!");
        SDL_DestroyWindow(janela);
        IMG_Quit();
        SDL_Quit();
        return 3;
    }

    if (carregar_texturas(tela, textura)) {
        puts("Erro ao carregar texturas!");
        SDL_DestroyRenderer(tela);
        SDL_DestroyWindow(janela);
        IMG_Quit();
        SDL_Quit();
        return 4;
    }

    if (jogo_inicializar(&jogo, textura)) {
        puts("Erro ao inicializar o jogo!");
        liberar_texturas(textura);
        SDL_DestroyRenderer(tela);
        SDL_DestroyWindow(janela);
        IMG_Quit();
        SDL_Quit();
    }

    while (loop) {
        while (SDL_PollEvent(&evento) != 0) {
            if (evento.type == SDL_QUIT) {
                loop = LOOP_SAIR;
            }

            if (loop == LOOP_JOGO) {
                jogo_evento(&evento, &jogo);
            }

            if (loop == LOOP_MENU) {
                menu_evento(&evento, &loop);
            }
        }

        SDL_SetRenderDrawColor(tela, JANELA_COR);
        SDL_RenderClear(tela);

        switch (loop) {
            case LOOP_MENU:
                menu_tela(tela, textura);
            break;

            case LOOP_JOGO:
                jogo_tela(tela, textura, &jogo);
            break;
        }

        SDL_RenderPresent(tela);

        SDL_Delay(JANELA_DELAY);
    }

    jogo_liberar(&jogo);
    liberar_texturas(textura);
    SDL_DestroyRenderer(tela);
    SDL_DestroyWindow(janela);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
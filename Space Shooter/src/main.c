#include <stdio.h>
#include "space_shooter.h"

int main(int argc, char *args[]) {
    int loop = 1;

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

    while (loop) {
        while (SDL_PollEvent(&evento) != 0) {
            if (evento.type == SDL_QUIT) {
                loop = 0;
            }

            /*  Code */
        }

        SDL_SetRenderDrawColor(tela, JANELA_COR);
        SDL_RenderClear(tela);

        /*  Code */

        SDL_RenderPresent(tela);

        SDL_Delay(JANELA_DELAY);
    }

    liberar_texturas(textura);
    SDL_DestroyRenderer(tela);
    SDL_DestroyWindow(janela);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
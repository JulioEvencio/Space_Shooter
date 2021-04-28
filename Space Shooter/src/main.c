#include <stdio.h>
#include "space_shooter.h"
#include "menu/menu.h"
#include "jogo/jogo.h"
#include "jogo/nave/nave.h"

int main(int argc, char *args[]) {
    int loop = LOOP_MENU;

    Nave *nave = NULL;

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

    if (nave_criar(&nave, 50, 50, (32 * 3), (32 * 3), 1)) {
        puts("Erro ao criar nave!");
        nave_liberar(&nave);
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

            if (evento.type == SDL_KEYDOWN && loop == LOOP_JOGO) {
                verificar_tecla_pressionada(&evento, &nave);
            }

            if (evento.type == SDL_KEYUP && loop == LOOP_JOGO) {
                verificar_tecla_solta(&evento, &nave);
            }

            if (evento.type == SDL_MOUSEBUTTONDOWN && loop == LOOP_MENU) {
                menu_click(tela, &evento, &loop);
            }
        }

        SDL_SetRenderDrawColor(tela, JANELA_COR);
        SDL_RenderClear(tela);

        switch (loop) {
            case LOOP_MENU:
                menu_tela(tela, textura);
            break;

            case LOOP_JOGO:
                jogo_tela(tela, textura, &nave);
            break;
        }

        SDL_RenderPresent(tela);

        SDL_Delay(JANELA_DELAY);
    }

    nave_liberar(&nave);
    liberar_texturas(textura);
    SDL_DestroyRenderer(tela);
    SDL_DestroyWindow(janela);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
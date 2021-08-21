#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "janela/janela.h"
#include "menu/menu.h"
#include "jogo/jogo.h"

int main(int argc, char *argv[]) {
    int loop = JANELA_MENU;

    Menu *menu;
    Jogo *jogo;

    SDL_Event evento;
    SDL_Window *janela;
    SDL_Renderer *tela;

    srand(time(NULL));

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        if (SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erro!", "Erro ao iniciar SDL!", NULL) < 0)
            SDL_Log("%s", SDL_GetError());
        return 1;
    }

    if (IMG_Init(IMG_INIT_PNG) < 0) {
        if (SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erro!", "Erro ao iniciar IMG!", NULL) < 0)
            SDL_Log("%s", SDL_GetError());
        SDL_Quit();
        return 2;
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
        if (SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erro!", "Erro ao criar janela!", NULL) < 0)
            SDL_Log("%s", SDL_GetError());
        IMG_Quit();
        SDL_Quit();
        return 3;
    }

    {
        SDL_Surface *icone = IMG_Load("sprites/Topview Sci-Fi Patreon Collection/player/player_0.png");

        if (icone != NULL) {
            SDL_SetWindowIcon(janela, icone);
            SDL_FreeSurface(icone);
        }
    }

    tela = SDL_CreateRenderer(
        janela,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (tela == NULL) {
        if (SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erro!", "Erro ao renderizar tela!", NULL) < 0)
            SDL_Log("%s", SDL_GetError());
        SDL_DestroyWindow(janela);
        IMG_Quit();
        SDL_Quit();
        return 4;
    }

    if (menu_criar(&menu, tela, &evento)) {
        if (SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erro!", "Erro ao inicializar menu!", NULL) < 0)
            SDL_Log("%s", SDL_GetError());
        SDL_DestroyRenderer(tela);
        SDL_DestroyWindow(janela);
        IMG_Quit();
        SDL_Quit();
        return 5;
    }

    if (jogo_criar(&jogo, janela, tela, &evento)) {
        if (SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erro!", "Erro ao inicializar jogo!", NULL) < 0)
            SDL_Log("%s", SDL_GetError());
        menu_liberar(&menu);
        SDL_DestroyRenderer(tela);
        SDL_DestroyWindow(janela);
        IMG_Quit();
        SDL_Quit();
        return 6;
    }

    while (loop) {
        while (SDL_PollEvent(&evento) != 0) {
            if (evento.type == SDL_QUIT) loop = JANELA_SAIR;

            switch (loop) {
                case JANELA_JOGO:
                    jogo_evento(&jogo);
                    break;

                case JANELA_MENU:
                    menu_evento(&menu);
                    break;
            }
        }

        switch (loop) {
            case JANELA_JOGO:
                loop = jogo_logica(&jogo);
                break;

            case JANELA_MENU:
                loop = menu_logica(&menu);
                break;
        }

        SDL_RenderPresent(tela);
        SDL_Delay(JANELA_DELAY);
    }

    jogo_liberar(&jogo);
    menu_liberar(&menu);
    SDL_DestroyRenderer(tela);
    SDL_DestroyWindow(janela);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
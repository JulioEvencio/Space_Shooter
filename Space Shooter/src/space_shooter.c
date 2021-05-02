#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "space_shooter.h"

int carregar_texturas(SDL_Renderer *tela, SDL_Texture *textura[]) {
    SDL_Surface *imagem = NULL;

    for (int i = 0; i < TEXTURA_QUANTIDADE; i++) {
        imagem = IMG_Load(textura_arquivo[i]);
        if (imagem == NULL) return -1;
        textura[i] = SDL_CreateTextureFromSurface(tela, imagem);
        SDL_FreeSurface(imagem);
    }

    return 0;
}

void liberar_texturas(SDL_Texture *textura[]) {
    for (int i = 0; i < TEXTURA_QUANTIDADE; i++) {
        SDL_DestroyTexture(textura[i]);
    }
}

void exibir_texto(SDL_Renderer *tela, TTF_Font *fonte, char *mensagem, int x, int y, int largura, int altura, int r, int g, int b) {
    SDL_Surface *texto = NULL;
    SDL_Texture *texto_textura = NULL;
    SDL_Color fonte_cor = {r, g, b};

    texto = TTF_RenderText_Solid(fonte, mensagem, fonte_cor);

    if (texto == NULL) return;

    texto_textura = SDL_CreateTextureFromSurface(tela, texto);

    if (texto_textura == NULL) {
        SDL_FreeSurface(texto);
        texto = NULL;
        return;
    }

    SDL_Rect desenho = {x, y, largura, altura};

    SDL_RenderCopy(tela, texto_textura, NULL, &desenho);
    SDL_FreeSurface(texto);
    SDL_DestroyTexture(texto_textura);

    return;
}

int verificar_colisao(int x1, int y1, int l1, int a1, int x2, int y2, int l2, int a2) {
    if ((y1 + a1) < y2) return 0;
    if (y1 > (y2 + a2)) return 0;
    if ((x1 + l1) < x2) return 0;
    if (x1 > (x2 + l2)) return 0;

    return 1;
}
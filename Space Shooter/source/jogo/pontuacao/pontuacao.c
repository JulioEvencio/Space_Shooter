#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include "../../janela/janela.h"
#include "pontuacao.h"

enum Enum_Pontuacao {
    PONTUACAO_DIGITO_1,
    PONTUACAO_DIGITO_2,
    PONTUACAO_DIGITO_3,
    PONTUACAO_DIGITO_4,
    PONTUACAO_DIGITO_5,
    PONTUACAO_DIGITOS = 5,
    PONTUACAO_MAXIMA = 99999
};

enum Enum_Pontuacao_Textura {
    PONTUACAO_TEXTURA_QUANTIDADE = 10
};

struct Pontos {
    int unidade;
    int dezena;
    int centena;
    int unidade_de_milhar;
    int dezena_de_milhar;
};
typedef struct Pontos Pontos;

struct Pontuacao {
    Pontos pontos;
    SDL_Rect numero[PONTUACAO_DIGITOS];
    SDL_Renderer *tela;
    SDL_Texture *textura[PONTUACAO_TEXTURA_QUANTIDADE];
};

int pontuacao_criar(Pontuacao **pontuacao, SDL_Renderer *tela) {
    *pontuacao = malloc(sizeof **pontuacao);

    if (*pontuacao == NULL) return PONTUACAO_SEM_MEMORIA;

    const char *pontuacao_arquivo[PONTUACAO_TEXTURA_QUANTIDADE] = {
        "sprites/Boxy-Bold-Font/numeros/zero.png",
        "sprites/Boxy-Bold-Font/numeros/um.png",
        "sprites/Boxy-Bold-Font/numeros/dois.png",
        "sprites/Boxy-Bold-Font/numeros/tres.png",
        "sprites/Boxy-Bold-Font/numeros/quatro.png",
        "sprites/Boxy-Bold-Font/numeros/cinco.png",
        "sprites/Boxy-Bold-Font/numeros/seis.png",
        "sprites/Boxy-Bold-Font/numeros/sete.png",
        "sprites/Boxy-Bold-Font/numeros/oito.png",
        "sprites/Boxy-Bold-Font/numeros/nove.png"
    };

    for (int i = 0; i < PONTUACAO_TEXTURA_QUANTIDADE; i++) {
        SDL_Surface *imagem = IMG_Load(pontuacao_arquivo[i]);

        if (imagem == NULL) {
            while (i > 0) SDL_DestroyTexture((*pontuacao)->textura[--i]);

            free(*pontuacao);

            return PONTUACAO_ERRO_AO_CARREGAR_IMAGEM;
        }

        (*pontuacao)->textura[i] = SDL_CreateTextureFromSurface(tela, imagem);
        SDL_FreeSurface(imagem);
    }

    (*pontuacao)->tela = tela;

    for (int i = 0; i < PONTUACAO_DIGITOS; i++) {
        (*pontuacao)->numero[i].w = 30;
        (*pontuacao)->numero[i].h = 33;
        (*pontuacao)->numero[i].x = (*pontuacao)->numero[i].w * i;
        (*pontuacao)->numero[i].y = 0;
    }

    pontuacao_resetar(pontuacao);

    return PONTUACAO_SUCESSO;
}

void pontuacao_liberar(Pontuacao **pontuacao) {
    for (int i = 0; i < PONTUACAO_TEXTURA_QUANTIDADE; i++) {
        SDL_DestroyTexture((*pontuacao)->textura[i]);
    }

    free(*pontuacao);
}

void pontuacao_logica(Pontuacao **pontuacao) {
    SDL_RenderCopy((*pontuacao)->tela, (*pontuacao)->textura[(*pontuacao)->pontos.unidade], NULL, &(*pontuacao)->numero[PONTUACAO_DIGITO_5]);
    SDL_RenderCopy((*pontuacao)->tela, (*pontuacao)->textura[(*pontuacao)->pontos.dezena], NULL, &(*pontuacao)->numero[PONTUACAO_DIGITO_4]);
    SDL_RenderCopy((*pontuacao)->tela, (*pontuacao)->textura[(*pontuacao)->pontos.centena], NULL, &(*pontuacao)->numero[PONTUACAO_DIGITO_3]);
    SDL_RenderCopy((*pontuacao)->tela, (*pontuacao)->textura[(*pontuacao)->pontos.unidade_de_milhar], NULL, &(*pontuacao)->numero[PONTUACAO_DIGITO_2]);
    SDL_RenderCopy((*pontuacao)->tela, (*pontuacao)->textura[(*pontuacao)->pontos.dezena_de_milhar], NULL, &(*pontuacao)->numero[PONTUACAO_DIGITO_1]);
}

void pontuacao_incrementar(Pontuacao **pontuacao) {
    if ((*pontuacao)->pontos.unidade != 9) (*pontuacao)->pontos.unidade++;
    else {
        (*pontuacao)->pontos.unidade = 0;

        if ((*pontuacao)->pontos.dezena != 9) (*pontuacao)->pontos.dezena++;
        else {
            (*pontuacao)->pontos.dezena = 0;

            if ((*pontuacao)->pontos.centena != 9) (*pontuacao)->pontos.centena++;
            else {
                (*pontuacao)->pontos.centena = 0;

                if ((*pontuacao)->pontos.unidade_de_milhar != 9) (*pontuacao)->pontos.unidade_de_milhar++;
                else {
                    (*pontuacao)->pontos.unidade_de_milhar = 0;

                    if ((*pontuacao)->pontos.dezena_de_milhar != 9) (*pontuacao)->pontos.dezena_de_milhar++;
                    else pontuacao_resetar(pontuacao);
                }
            }
        }
    }
}

void pontuacao_resetar(Pontuacao **pontuacao) {
    (*pontuacao)->pontos.unidade = 0;
    (*pontuacao)->pontos.dezena = 0;
    (*pontuacao)->pontos.centena = 0;
    (*pontuacao)->pontos.unidade_de_milhar = 0;
    (*pontuacao)->pontos.dezena_de_milhar = 0;
}
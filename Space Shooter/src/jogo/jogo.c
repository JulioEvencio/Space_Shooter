#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../space_shooter.h"
#include "personagem/personagem.h"
#include "inimigo/inimigo.h"
#include "jogo.h"

#define JOGO_PONTUACAO_TAMANHO 10
#define JOGO_PONTUACAO_MAX 999999999
#define JOGO_PONTUACAO_INICIAL 0
#define JOGO_FUNDO_X 0
#define JOGO_FUNDO_Y 0
#define JOGO_FUNDO_LARGURA JANELA_LARGURA
#define JOGO_FUNDO_ALTURA JANELA_ALTURA
#define JOGO_INIMIGO_QUANTIDADE 3

#define TEXTO_X 0
#define TEXTO_Y 0
#define TEXTO_LARGURA 100
#define TEXTO_ALTURA 30
#define TEXTO_COR 255,0,0

struct Jogo {
    int pontuacao;
    char pontuacao_texto[JOGO_PONTUACAO_TAMANHO];
    Personagem *personagem;
    Inimigo *inimigo[JOGO_INIMIGO_QUANTIDADE];
    SDL_Texture *fundo;
};

void jogo_verificar_tecla_pressionada(Jogo **jogo, SDL_Event *evento);
void jogo_verificar_tecla_solta(Jogo **jogo, SDL_Event *evento);

int jogo_criar(Jogo **jogo, SDL_Texture *textura[]) {
    *jogo = malloc(sizeof **jogo);

    if (*jogo == NULL) return -1;

    if (personagem_criar(&(*jogo)->personagem, textura)) {
        free(*jogo);
        return -1;
    }

    for (int i = 0; i < JOGO_INIMIGO_QUANTIDADE; i++) {
        if (inimigo_criar(&(*jogo)->inimigo[i], textura)) {
            personagem_liberar(&(*jogo)->personagem);
            free(*jogo);
            return -1;
        }
    }

    (*jogo)->pontuacao = JOGO_PONTUACAO_INICIAL;
    (*jogo)->pontuacao = 999999998;
    (*jogo)->fundo = textura[TEXTURA_BACKGROUND];

    return 0;
}

void jogo_liberar(Jogo **jogo) {
    for (int i = 0; i < JOGO_INIMIGO_QUANTIDADE; i++) {
        inimigo_liberar(&(*jogo)->inimigo[i]);
    }
    personagem_liberar(&(*jogo)->personagem);
    free(*jogo);
}

void jogo_tela(Jogo **jogo, SDL_Renderer *tela, TTF_Font *fonte, int *loop) {
    int x1, y1, l1, a1;
    int x2, y2, l2, a2;

    SDL_Rect fundo = {JOGO_FUNDO_X, JOGO_FUNDO_Y, JOGO_FUNDO_LARGURA, JOGO_FUNDO_ALTURA};
    SDL_RenderCopy(tela, (*jogo)->fundo, NULL, &fundo);

    personagem_desenhar(&(*jogo)->personagem, tela);
    personagem_movimentar(&(*jogo)->personagem);

    for (int i = 0; i < JOGO_INIMIGO_QUANTIDADE; i++) {
        sprintf((*jogo)->pontuacao_texto, "%9d", (*jogo)->pontuacao);
        exibir_texto(tela, fonte, (*jogo)->pontuacao_texto, TEXTO_X, TEXTO_Y, TEXTO_LARGURA, TEXTO_ALTURA, TEXTO_COR);

        inimigo_desenhar(&(*jogo)->inimigo[i], tela);
        inimigo_movimentar(&(*jogo)->inimigo[i]);

        /* Personagem com inimigo */
        x1 = personagem_obter_x(&(*jogo)->personagem);
        y1 = personagem_obter_y(&(*jogo)->personagem);
        l1 = personagem_obter_largura(&(*jogo)->personagem);
        a1 = personagem_obter_altura(&(*jogo)->personagem);

        x2 = inimigo_obter_x(&(*jogo)->inimigo[i]);
        y2 = inimigo_obter_y(&(*jogo)->inimigo[i]);
        l2 = inimigo_obter_largura(&(*jogo)->inimigo[i]);
        a2 = inimigo_obter_altura(&(*jogo)->inimigo[i]);

        if (verificar_colisao(x1, y1, l1, a1, x2, y2, l2, a2)) {
            *loop = LOOP_MENU;
            (*jogo)->pontuacao = JOGO_PONTUACAO_INICIAL;
            personagem_resetar(&(*jogo)->personagem);
            for (int i = 0; i < JOGO_INIMIGO_QUANTIDADE; i++) {
                inimigo_resetar(&(*jogo)->inimigo[i]);
            }
        }

        /* Tiro com inimigo */
        x1 = personagem_obter_tiro_x(&(*jogo)->personagem);
        y1 = personagem_obter_tiro_y(&(*jogo)->personagem);
        l1 = personagem_obter_tiro_largura(&(*jogo)->personagem);
        a1 = personagem_obter_tiro_altura(&(*jogo)->personagem);

        if (verificar_colisao(x1, y1, l1, a1, x2, y2, l2, a2)) {
            inimigo_resetar(&(*jogo)->inimigo[i]);
            personagem_resetar_tiro(&(*jogo)->personagem);

            (*jogo)->pontuacao++;

            if ((*jogo)->pontuacao > JOGO_PONTUACAO_MAX) {
                (*jogo)->pontuacao = JOGO_PONTUACAO_INICIAL;
            }
        }
    }
}

void jogo_evento(Jogo **jogo, SDL_Event *evento) {
    if ((*evento).type == SDL_KEYDOWN) {
        jogo_verificar_tecla_pressionada(jogo, evento);
    }

    if ((*evento).type == SDL_KEYUP) {
        jogo_verificar_tecla_solta(jogo, evento);
    }
}

void jogo_verificar_tecla_pressionada(Jogo **jogo, SDL_Event *evento) {
    switch ((*evento).key.keysym.sym) {
        case SDLK_UP:
            personagem_subir(&(*jogo)->personagem);
            break;

        case SDLK_DOWN:
            personagem_descer(&(*jogo)->personagem);
            break;

        case SDLK_SPACE:
            personagem_atirar(&(*jogo)->personagem);
            break;
    }
}

void jogo_verificar_tecla_solta(Jogo **jogo, SDL_Event *evento) {
    switch ((*evento).key.keysym.sym) {
        case SDLK_UP:
            personagem_parar_subida(&(*jogo)->personagem);
            break;

        case SDLK_DOWN:
            personagem_parar_descida(&(*jogo)->personagem);
            break;

        case SDLK_SPACE:
            /*  Code */
            break;
    }
}
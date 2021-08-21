#ifndef JOGO_H_INCLUDED
#define JOGO_H_INCLUDED

enum Enum_Jogo_Erro {
    JOGO_SUCESSO,
    JOGO_SEM_MEMORIA,
    JOGO_ERRO_AO_CARREGAR_IMAGEM,
    JOGO_ERRO_AO_CARREGAR_FUNDO,
    JOGO_ERRO_AO_CARREGAR_METEORO,
    JOGO_ERRO_AO_CARREGAR_PLAYER,
    JOGO_ERRO_AO_CARREGAR_PONTUACAO
};

typedef struct Jogo Jogo;

int jogo_criar(Jogo **jogo, SDL_Window *janela, SDL_Renderer *tela, SDL_Event *evento);
void jogo_liberar(Jogo **jogo);

int jogo_logica(Jogo **jogo);
void jogo_evento(Jogo **jogo);

#endif
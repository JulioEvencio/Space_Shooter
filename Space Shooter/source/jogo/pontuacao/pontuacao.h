#ifndef PONTUACAO_H_INCLUDED
#define PONTUACAO_H_INCLUDED

enum Enum_Pontuacao_Erro {
    PONTUACAO_SUCESSO,
    PONTUACAO_SEM_MEMORIA,
    PONTUACAO_ERRO_AO_CARREGAR_IMAGEM
};

typedef struct Pontuacao Pontuacao;

int pontuacao_criar(Pontuacao **pontuacao, SDL_Renderer *tela);
void pontuacao_liberar(Pontuacao **pontuacao);

void pontuacao_logica(Pontuacao **pontuacao);

void pontuacao_incrementar(Pontuacao **pontuacao);
void pontuacao_resetar(Pontuacao **pontuacao);

#endif
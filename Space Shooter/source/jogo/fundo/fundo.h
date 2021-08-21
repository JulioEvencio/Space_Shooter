#ifndef FUNDO_H_INCLUDED
#define FUNDO_H_INCLUDED

enum Enum_Fundo_Erro {
    FUNDO_SUCESSO,
    FUNDO_SEM_MEMORIA,
    FUNDO_ERRO_AO_CARREGAR_IMAGEM
};

typedef struct Fundo Fundo;

int fundo_criar(Fundo **fundo, SDL_Renderer *tela, SDL_Event *evento);
void fundo_liberar(Fundo **fundo);

void fundo_logica(Fundo **fundo);
void fundo_evento(Fundo **fundo);

void fundo_resetar(Fundo **fundo);

#endif
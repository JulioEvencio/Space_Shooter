#ifndef METEORO_H_INCLUDED
#define METEORO_H_INCLDUED

enum Enum_Meteoro {
    METEORO_QUANTIDADE = 5
};

enum Enum_Meteoro_Erro {
    METEORO_SUCESSO,
    METEORO_SEM_MEMORIA,
    METEORO_ERRO_AO_CARREGAR_IMAGEM
};

typedef struct Meteoro Meteoro;

int meteoro_criar(Meteoro **meteoro, SDL_Renderer *tela, SDL_Event *evento);
void meteoro_liberar(Meteoro **meteoro);

void meteoro_logica(Meteoro **meteoro);
void meteoro_evento(Meteoro **meteoro);

SDL_Rect *meteoro_obter(Meteoro **meteoro);
void meteoro_colisao(Meteoro **meteoro, int i);

void meteoro_resetar(Meteoro **meteoro);

#endif
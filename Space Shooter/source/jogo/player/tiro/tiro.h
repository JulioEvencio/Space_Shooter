#ifndef TIRO_H_INCLUDED
#define TIRO_H_INCLUDED

enum Enum_Tiro {
    TIRO_QUANTIDADE = 6
};

enum Enum_Tiro_Erro {
    TIRO_SUCESSO,
    TIRO_SEM_MEMORIA,
    TIRO_ERRO_AO_CARREGAR_IMAGEM,
    TIRO_ERRO_AO_CARREGAR_AUDIO
};

typedef struct Tiro Tiro;

int tiro_criar(Tiro **tiro, SDL_Renderer *tela, SDL_Event *evento);
void tiro_liberar(Tiro **tiro);

void tiro_logica(Tiro **tiro);
void tiro_evento(Tiro **tiro);

void tiro_atirar(Tiro **tiro, int x, int y);
SDL_Rect *tiro_obter(Tiro **tiro);
void tiro_colisao(Tiro **tiro, int i);

void tiro_resetar(Tiro **tiro);

#endif
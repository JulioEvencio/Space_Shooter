#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

enum Enum_Player {
    PLAYER_CONTINUE,
    PLAYER_GAME_OVER,
    PLAYER_TIRO_QUANTIDADE = 6
};

enum Enum_Player_Erro {
    PLAYER_SUCESSO,
    PLAYER_SEM_MEMORIA,
    PLAYER_ERRO_AO_CARREGAR_IMAGEM,
    PLAYER_ERRO_AO_CARREGAR_TIRO
};

typedef struct Player Player;

int player_criar(Player **player, SDL_Renderer *tela, SDL_Event *evento);
void player_liberar(Player **player);

int player_logica(Player **player);
void player_evento(Player **player);

SDL_Rect player_obter(Player **player);
void player_colisao(Player **player);

SDL_Rect *player_obter_tiro(Player **player);
void player_colisao_tiro(Player **player, int i);

void player_resetar(Player **player);

#endif
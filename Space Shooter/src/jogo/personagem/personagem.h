#ifndef PERSONAGEM_H_INCLUDED
#define PERSONAGEM_H_INCLUDED

typedef struct Personagem Personagem;

int personagem_criar(Personagem **personagem, SDL_Texture *textura[]);
void personagem_liberar(Personagem **personagem);

void personagem_desenhar(Personagem **personagem, SDL_Renderer *tela);
void personagem_movimentar(Personagem **personagem);

void personagem_subir(Personagem **personagem);
void personagem_descer(Personagem **personagem);
void personagem_parar_subida(Personagem **personagem);
void personagem_parar_descida(Personagem **personagem);

int personagem_obter_x(Personagem **personagem);
int personagem_obter_y(Personagem **personagem);
int personagem_obter_largura(Personagem **personagem);
int personagem_obter_altura(Personagem **personagem);
int personagem_resetar(Personagem **personagem);

void personagem_atirar(Personagem **personagem);

int personagem_obter_tiro_x(Personagem **personagem);
int personagem_obter_tiro_y(Personagem **personagem);
int personagem_obter_tiro_largura(Personagem **personagem);
int personagem_obter_tiro_altura(Personagem **personagem);
int personagem_resetar_tiro(Personagem **personagem);

#endif
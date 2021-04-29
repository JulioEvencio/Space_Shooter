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

#endif
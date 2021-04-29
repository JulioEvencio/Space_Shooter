#ifndef NAVE_H_INCLUDED
#define NAVE_H_INCLUDED

typedef struct Nave Nave;

int nave_criar(Nave **nave, int x, int y, int largura, int altura, int velocidade);
int nave_liberar(Nave **nave);
void nave_desenhar(Nave **nave, SDL_Renderer *tela, SDL_Texture *textura);
void nave_movimentar(Nave **nave);
void nave_subir(Nave **nave);
void nave_descer(Nave **nave);
void nave_parar_subida(Nave **nave);
void nave_parar_descida(Nave **nave);
int nave_obter_x(Nave **nave);
int nave_obter_y(Nave **nave);

#endif
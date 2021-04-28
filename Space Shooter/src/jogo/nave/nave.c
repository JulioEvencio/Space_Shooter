#include "stdlib.h"
#include "nave.h"

int nave_criar(Nave **nave, int x, int y, int largura, int altura, int velocidade) {
    *nave = malloc(sizeof **nave);

    if (*nave == NULL) return -1;

    (*nave)->x = x;
    (*nave)->y = y;
    (*nave)->largura = largura;
    (*nave)->altura = altura;
    (*nave)->velocidade = velocidade;
    (*nave)->movimentando_esquerda = NAVE_MOVIMENTO_INICIAL;
    (*nave)->movimentando_direita = NAVE_MOVIMENTO_INICIAL;

    return 0;
}

int nave_liberar(Nave **nave) {
    free(*nave);
}
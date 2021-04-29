#ifndef SPACE_SHOOTER_INCLUDED
#define SPACE_SHOOTER_INCLUDED

#define JANELA_NOME "Space Shooter"
#define JANELA_LARGURA 1200
#define JANELA_ALTURA 500
#define JANELA_DELAY 30
#define JANELA_COR 0, 0, 0, 255

#define TEXTURA_QUANTIDADE 5

enum Textura {
    TEXTURA_SPRITE_PERSONAGEM_1,
    TEXTURA_SPRITE_PERSONAGEM_2,
    TEXTURA_BACKGROUND,
    TEXTURA_PLAY,
    TEXTURA_PLAY_PRESSIONADO,
};

static char *textura_arquivo[TEXTURA_QUANTIDADE] = {
    "../imagem/personagem1.png",
    "../imagem/personagem2.png",
    "../imagem/space.png",
    "../imagem/play.png",
    "../imagem/play_pressionado.png"
};

enum Loop {
    LOOP_SAIR,
    LOOP_MENU,
    LOOP_JOGO
};

int carregar_texturas(SDL_Renderer *tela, SDL_Texture *textura[]);
void liberar_texturas(SDL_Texture *textura[]);

#endif
#ifndef SPACE_SHOOTER_INCLUDED
#define SPACE_SHOOTER_INCLUDED

#define JANELA_NOME "Space Shooter"
#define JANELA_LARGURA 1200
#define JANELA_ALTURA 500
#define JANELA_DELAY 30
#define JANELA_COR 0, 0, 0, 255

#define TEXTURA_QUANTIDADE 10

enum Textura {
    TEXTURA_SPRITE_PERSONAGEM_1,
    TEXTURA_SPRITE_PERSONAGEM_2,
    TEXTURA_BACKGROUND,
    TEXTURA_PLAY,
    TEXTURA_PLAY_PRESSIONADO,
    TEXTURA_TIRO,
    TEXTURA_INIMIGO_SPRITE_1,
    TEXTURA_INIMIGO_SPRITE_2,
    TEXTURA_INIMIGO_SPRITE_3,
    TEXTURA_INIMIGO_SPRITE_4
};

static char *textura_arquivo[TEXTURA_QUANTIDADE] = {
    "../imagem/personagem1.png",
    "../imagem/personagem2.png",
    "../imagem/space.png",
    "../imagem/play.png",
    "../imagem/play_pressionado.png",
    "../imagem/tiro.png",
    "../imagem/inimigo_sprite_1.png",
    "../imagem/inimigo_sprite_2.png",
    "../imagem/inimigo_sprite_3.png",
    "../imagem/inimigo_sprite_4.png"
};

enum Loop {
    LOOP_SAIR,
    LOOP_MENU,
    LOOP_JOGO
};

int carregar_texturas(SDL_Renderer *tela, SDL_Texture *textura[]);
void liberar_texturas(SDL_Texture *textura[]);

#endif
#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

enum Enum_Menu_Erro {
    MENU_SUCESSO,
    MENU_SEM_MEMORIA,
    MENU_ERRO_AO_CARREGAR_IMAGEM,
    MENU_ERRO_AO_CARREGAR_MUSICA
};

typedef struct Menu Menu;

int menu_criar(Menu **menu, SDL_Renderer *tela, SDL_Event *evento);
void menu_liberar(Menu **menu);

int menu_logica(Menu **menu);
void menu_evento(Menu **menu);

#endif
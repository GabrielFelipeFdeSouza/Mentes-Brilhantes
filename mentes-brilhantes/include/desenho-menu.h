#ifndef DESENHO_MENU_H
#define DESENHO_MENU_H

#include "raylib.h"
#include "structs-gerais.h"

// Declaração da função
void desenhoMenu(RenderTexture2D *target, Botao botoes[], int quantidade_botoes, BotaoNulo *botao, Texture2D *img_btn_som, Texture2D *fundo);

#endif

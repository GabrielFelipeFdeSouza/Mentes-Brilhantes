#ifndef DESENHO_GAME_BOT_H
#define DESENHO_GAME_BOT_H

#include "raylib.h"
#include "structs-gerais.h"

void desenhaJogoSingleplayer(RenderTexture2D *target, Botao *botoes, Texture2D *fundo, RadioButton *botoes_radio, int *sub_menu, long int contador_tempo[2], Texture2D *img_carta, Carta *carta, Texture2D *frente_carta, int quantidades_cartas[3], int vezJogar, Texture2D *img_carta_bot, Carta *carta_bot, Texture2D *fundo_carta, int *btn_clicado);
void incluir_menu1(RadioButton *botoes_radio);
void incluir_menu2(long int contador_tempo[2]);
void incluir_menu3(long int contador_tempo[2], int quantidades_cartas[3]);
void incluir_menu6();
void incluir_menu7();

#endif //DESENHO_GAME_BOT_H
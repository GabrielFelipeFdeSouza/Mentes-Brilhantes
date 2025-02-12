#ifndef DESENHO_CREDITOS_H
#define DESENHO_CREDITOS_H

#include "raylib.h"
#include "structs-gerais.h"

void desenhaCreditos(RenderTexture2D *target, Botao *botao, Texture2D *fundo, long int *contador_tempo, char texto[][512], int posicoes_desenho_txt[], int tamanho_texto, Carta *cartas_fundo, Texture2D *imagens_fundo, int posicoes_desenho_cartas[], Texture2D *frente_carta);
#endif //DESENHO_CREDITOS_H
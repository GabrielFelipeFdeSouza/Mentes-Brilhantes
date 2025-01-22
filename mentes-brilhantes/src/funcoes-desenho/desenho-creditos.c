// FUNÇÕES DE DESENHO PARA A TELA DE CRÉDITOS

#include "main.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include "structs-gerais.h"
#include <string.h>
#include "desenho-creditos.h"
#include "desenho-geral.h"
#include "funcoes-controle-geral.h"
#include "cores.h"

extern Vector2 posicao_mouse; // Chamada da variavel global posicao_mouse

void desenhaCreditos(RenderTexture2D *target, Botao botao, Texture2D fundo, int *contador_tempo, char texto[][512], int posicoes_desenho_txt[], int tamanho_texto, Carta *cartas_fundo, Texture2D *imagens_fundo, int posicoes_desenho_cartas[], Texture2D frente_carta)
{

    Color cor;

    static int contador_velocidade = 50; // Persistência entre frames

    if(contador_velocidade > 45){
    cor = (Color){GetRandomValue(10, 255), GetRandomValue(10, 255), GetRandomValue(10, 255), 205};
    contador_velocidade = 0;
    }

    (void)contador_tempo;

    BeginTextureMode(*target); // Tudo que for desenhado dessa função até EndTextureMode será automaticamente escalado
    ClearBackground(RAYWHITE); // Fundo da tela

    DrawTexture(fundo, 0, 0, WHITE);

    for (int u = 0; u < 3; u++)
    {
        desenhaCarta(15 + (333 * u), posicoes_desenho_cartas[u], frente_carta, cartas_fundo[u], imagens_fundo[u]);
    }

    for (int t = 0; t < tamanho_texto; t++)
    {
        if (t == 0)
        {
            DrawRectangle(260, posicoes_desenho_txt[t], MeasureText(texto[t], 40) - 107, 44, cor);
            DrawText(TextFormat("%s", texto[t]), 146, posicoes_desenho_txt[t] + 4, 40, BLACK);
        }
        else
        {
            if (MeasureText(texto[t], 28) >= 10)
            {
                DrawRectangle(140, posicoes_desenho_txt[t], MeasureText(texto[t], 28) + 10, 30, NOSSO_CREME_FRACO);
            }
            DrawText(TextFormat("%s", texto[t]), 148, posicoes_desenho_txt[t] + 1, 28, BLACK);
        }
    }

    desenharBotaoTxt(botao);
    EndTextureMode();

    desenhoRedimensionado(target); // Chama a função que desenha redimensionadamente

    contador_velocidade++;

    return;
}

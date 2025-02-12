/*
-->DESENHO MENU<--
Arquivo responsavél por abrigar a função que desesenha a tela do menu.
*/

//---------------------------------
// INCLUDES
//---------------------------------

#include "main.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include "structs-gerais.h"
#include <string.h>
#include "desenho-menu.h"
#include "desenho-geral.h"
#include "funcoes-controle-geral.h"
#include "cores.h"

//---------------------------------
// DESENHO LINUX E WINDOWS
//---------------------------------

void desenhoMenu(RenderTexture2D *target, Botao botoes[], int quantidade_botoes, BotaoNulo *botao, Texture2D *img_btn_som, Texture2D *fundo)
{
    BeginTextureMode(*target); // Tudo que for desenhado dessa função até EndTextureMode será automaticamente escalado
    ClearBackground(RAYWHITE); // limpando o fundo da tela

    DrawTexture(*fundo, 0, 0, WHITE); // Desenhando o fundo

    for (int t = 0; t < quantidade_botoes; t++)
    {
        desenharBotaoTxt(&botoes[t]);
    } // Desenha todos os botões

    // DrawText(TextFormat("Posição do mouse: (%.2f,%.2f) - FPS: %d", posicao_mouse.x, posicao_mouse.y, GetFPS()), 1, 1, 20, RED);
    desenharBotaoNulo(botao);                   // Desenha os botões nulos, nesse caso o da imagem de som
    DrawTexture(*img_btn_som, 916, 525, WHITE); // Desenha a textura do botão de som

    resaltaBotoes(); // Chama a função que resalta os botões

    EndTextureMode(); // Fim do desenho

    desenhoRedimensionado(target); // Chama a função que desenha redimensionadamente

    return;
}
// FUNÇÕES DE DESENHO PARA A TELA DE EM JOGO BOT

#include "main.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include "structs-gerais.h"
#include <string.h>
#include "funcoes-emjogo-bot.h"
#include "desenho-game-bot.h"
#include "funcoes-controle-geral.h"
#include "desenho-geral.h"
#include "cores.h"
#include <math.h>
#include <stdbool.h>

void desenhaJogoSingleplayer(RenderTexture2D *target, Botao *botoes, Texture2D fundo, RadioButton *botoes_radio, int sub_menu, long int contador_tempo[2], Texture2D img_carta, Carta carta, Texture2D frente_carta, int quantidades_cartas[2], int vezJogar, Texture2D img_carta_bot, Carta carta_bot, Texture2D fundo_carta, int btn_clicado)
{
    BeginTextureMode(*target);       // Tudo que for desenhado dessa função até EndTextureMode será automaticamente escalado
    ClearBackground(BLUE);           // Fundo da tela
    DrawTexture(fundo, 0, 0, WHITE); // Desenha o fundo

    for (int y = 0; y < 1; y++)
    {
        if (CheckCollisionPointRec(posicao_mouse, botoes[0].colisao))
        {
            break;
        }
        if (y == 1 - 1)
        {
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
    } // For que arruma o tipo de cursor nos botoes normais

    if (sub_menu == 2)
    {
        DrawTextureEx(fundo_carta, (Vector2){708, 23}, 0.0f, 1.75f, WHITE);
        DrawTextureEx(fundo_carta, (Vector2){23, 138}, 0.0f, 1.75f, WHITE);
        desenhaCarta(15, 130, &frente_carta, &carta, img_carta); // Chama a função para desenhar a carta na posição x,y
    } // Se estiver no submenu 2 (JOGO), desenha as cartas

    if (sub_menu == 2 && contador_tempo[3] < 210)
    {
        desenhaCarta(700, 15, &frente_carta, &carta_bot, img_carta_bot); // Chama a função para desenhar a carta na posição x,y
    } // Se estiver no submenu 2 (JOGO) e estiver na faixa de transição, desenha a carta do bot
    else if (sub_menu == 2)
    {
        DrawTextureEx(fundo_carta, (Vector2){700, 15}, 0.0f, 1.75f, WHITE);
    }

    switch (sub_menu)
    {
    case 0:
        incluir_menu1(botoes_radio);
        break;

    case 1:
        incluir_menu2(contador_tempo);
        break;

    case 2:
        incluir_menu3(contador_tempo, quantidades_cartas);
        break;

    case 5:
        incluir_menu6();
        break;

    case 6:
        incluir_menu7();
        break;

    default:
        break;
    }

    desenharBotaoTxt(botoes[0], 1);
    // DrawText(TextFormat("Posição do mouse: (%.2f,%.2f) - FPS: %d", posicao_mouse.x, posicao_mouse.y, GetFPS()), 1, 1, 20, RED);

    if (sub_menu == 0)
    {
        desenharBotaoTxt(botoes[1], 1);
    }

    if (sub_menu == 2 && vezJogar == 1 && contador_tempo[2] < 150)
    {
        contador_tempo[2]++;
        DrawText(TextFormat("VEZ DO JOGADOR JOGAR!"), 320, 300, 29, WHITE);
    }

    if (sub_menu == 2 && vezJogar == 0 && contador_tempo[2] < 150)
    {
        contador_tempo[2]++;
        DrawText(TextFormat("VEZ DO BOT JOGAR!"), 335, 300, 30, WHITE);
    }

    switch (btn_clicado)
    {
    case 0:
        DrawRectangleLinesEx((Rectangle){36, 374, 244, 35}, 3, RED);
        DrawRectangleLinesEx((Rectangle){721, 259, 244, 35}, 3, RED);
        break;

    case 1:
        DrawRectangleLinesEx((Rectangle){36, 419, 244, 35}, 3, RED);
        DrawRectangleLinesEx((Rectangle){721, 304, 244, 35}, 3, RED);
        break;

    case 2:
        DrawRectangleLinesEx((Rectangle){36, 464, 244, 35}, 3, RED);
        DrawRectangleLinesEx((Rectangle){721, 349, 244, 35}, 3, RED);
        break;

    case 3:
        DrawRectangleLinesEx((Rectangle){36, 509, 244, 35}, 3, RED);
        DrawRectangleLinesEx((Rectangle){721, 394, 244, 35}, 3, RED);
        break;

    default:
        break;
    }

    // DrawRectangle(x + 21, y + 244 + t * 45, 244, 35, NOSSO_BEGE);

    EndTextureMode();
    desenhoRedimensionado(target); // Chama a função que desenha redimensionadamente
    return;
}

void incluir_menu1(RadioButton *botoes_radio)
{
    DrawText(TextFormat("JOGO COM BOT:"), 358, 3, 37, WHITE);
    DrawText(TextFormat("JOGO COM BOT:"), 360, 5, 37, BLACK);
    DrawText(TextFormat("ESCOLHA A DIFICULDADE:"), 30, 100, 27, WHITE);
    desenhaRadioButton(botoes_radio, 3, 1);
    resaltaRadioButton(botoes_radio, 3, 1);
    checaRadioButton(botoes_radio, 3, 1);
    return;
}

void incluir_menu2(long int contador_tempo[2])
{
    DrawText(TextFormat("JOGO COMEÇANDO EM %d...", (contador_tempo[0] / 60) + 1), 180, 275, 50, WHITE);
    return;
}

void incluir_menu3(long int contador_tempo[2], int quantidades_cartas[2])
{
    DrawText(TextFormat("%02d:%02d", (contador_tempo[1] / 3600), (contador_tempo[1] / 60 % 60)), 15, 8, 30, WHITE);
    DrawRectangleLinesEx((Rectangle){3, 4, 99, 36}, 4, WHITE);

    DrawText(TextFormat("JOGADOR"), 310, 510, 33, NOSSO_AZUL);
    DrawRectangleLinesEx((Rectangle){320, 540, 125, 55}, 4, NOSSO_AMARELO);
    DrawText(TextFormat("%d", quantidades_cartas[1]), 358, 548, 45, NOSSO_AMARELO);

    DrawText(TextFormat("BOT"), 586, 40, 33, NOSSO_AZUL);
    DrawRectangleLinesEx((Rectangle){562, 75, 125, 55}, 4, NOSSO_AMARELO);
    DrawText(TextFormat("%d", quantidades_cartas[0]), 600, 83, 45, NOSSO_AMARELO);

    return;
}

void incluir_menu6()
{
    DrawText(TextFormat("JOGADOR GANHOU!"), 185, 267, 60, WHITE);
    return;
}

void incluir_menu7()
{
    DrawText(TextFormat("BOT GANHOU!"), 230, 267, 60, WHITE);
    return;
}
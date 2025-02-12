// FUNÇÕES DE DESENHO PARA A TELA DE EM JOGO MULTIPLAYER

// FUNÇÕES DE DESENHO PARA A TELA DE EM JOGO BOT

#include "main.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include "structs-gerais.h"
#include <string.h>
#include "funcoes-emjogo-multiplayer.h"
#include "desenho-game-multiplayer.h"
#include "funcoes-controle-geral.h"
#include "desenho-geral.h"
#include "cores.h"
#include <math.h>
#include <stdbool.h>

void desenhaJogoMultiplayer(RenderTexture2D *target, Botao *botoes, Texture2D fundo, int sub_menu, int conexao_server, TextBox *caixa_texto, int *erros, int id_sala, int *contador_tempo, int quantidades_cartas[3], Texture2D fundo_carta, Texture2D frente_carta, Carta carta1, Carta carta2, Texture2D *img_carta, Texture2D *img_carta_player2, int btn_clicado, char *nome_player1, char *nome_player2, int vez_jogar, int tipo_jogo)
{
    BeginTextureMode(*target);       // Tudo que for desenhado dessa função até EndTextureMode será automaticamente escalado
    ClearBackground(BLUE);           // Fundo da tela
    DrawTexture(fundo, 0, 0, WHITE); // Desenha o fundo

    if (sub_menu == 2)
    {
        DrawTextureEx(fundo_carta, (Vector2){708, 23}, 0.0f, 1.75f, WHITE);
        DrawTextureEx(fundo_carta, (Vector2){23, 138}, 0.0f, 1.75f, WHITE);
        desenhaCarta(15, 130, &frente_carta, &carta1, img_carta); // Chama a função para desenhar a carta na posição x,y
    } // Se estiver no submenu 2 (JOGO), desenha as cartas

    if (sub_menu == 2 && contador_tempo[3] < 211)
    {
        desenhaCarta(700, 15, &frente_carta, &carta2, img_carta_player2); // Chama a função para desenhar a carta na posição x,y
    } // Se estiver no submenu 2 (JOGO) e estiver na faixa de transição, desenha a carta do bot
    else if (sub_menu == 2)
    {
        DrawTextureEx(fundo_carta, (Vector2){700, 15}, 0.0f, 1.75f, WHITE);
    }

    switch (sub_menu)
    {
    case 0:
        incluir_menu11(conexao_server);
        break;

    case 1:
        DrawText(TextFormat("ID DA SALA: %d", id_sala), 22, 8, 27, WHITE);
        DrawText(TextFormat("       SALA CRIADA!\n\n\n AGUARDANDO JOGADOR 2!"), 213, 245, 40, WHITE);
        break;

    case 2:
        incluir_menu13(contador_tempo, quantidades_cartas, nome_player1, nome_player2, vez_jogar, tipo_jogo);
        break;

    case 3:
        DrawText(TextFormat("TODOS OS PLAYERS CONECTADOS!"), 45, 230, 50, WHITE);
        DrawText(TextFormat("JOGO COMEÇANDO EM %d...", (contador_tempo[6] / 60) + 1), 180, 295, 50, WHITE);
        break;

    case 5:
        DrawText(TextFormat("JOGADOR %s, GANHOU!", nome_player1), 40, 267, 58, WHITE);
        break;

    case 6:
        DrawText(TextFormat("JOGADOR %s, GANHOU!", nome_player2), 40, 267, 58, WHITE);
        break;

    case 8:
        DrawText(TextFormat("   O JOGADOR, %s\n\n\n\n ABANDONOU O JOGO!", nome_player2), 200, 244, 48, RED);
        break;

    default:
        break;
    }

    desenharBotaoTxt(&botoes[0]);
    // DrawText(TextFormat("Posição do mouse: (%.2f,%.2f) - FPS: %d", posicao_mouse.x, posicao_mouse.y, GetFPS()), 1, 1, 20, RED);

    if (sub_menu == 0 && conexao_server == 1)
    {
        desenharBotaoTxt(&botoes[1]);
        desenharBotaoTxt(&botoes[2]);
        desenhaTextBox(&caixa_texto[0]);
        desenhaTextBox(&caixa_texto[1]);
    }

    if (sub_menu == 0 && erros[0] < 220)
    {
        DrawText(TextFormat("ERRO, NOME VAZIO!"), 25, 450, 28, RED);
    }

    if (sub_menu == 0 && erros[1] < 220)
    {
        DrawText(TextFormat("ERRO, NOME VAZIO ou CÓDIGO INCOMPLETO!"), 25, 450, 28, RED);
    }

    if (sub_menu == 0 && erros[2] < 220)
    {
        DrawText(TextFormat("ESSA SALA JA ESTA OCUPADA OU AINDA NÃO FOI CRIADA!"), 25, 490, 28, RED);
    }

    if (sub_menu == 2)
    {
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
    }

    resaltaBotoes();

    EndTextureMode();
    desenhoRedimensionado(target); // Chama a função que desenha redimensionadamente
    return;
}

void incluir_menu11(int conexao_server)
{
    DrawText(TextFormat("JOGO MULTIPLAYER:"), 306, 3, 37, WHITE);
    DrawText(TextFormat("JOGO MULTIPLAYER:"), 308, 5, 37, BLACK);

    if (conexao_server == 0)
    {
        DrawText(TextFormat("CONETANDO AO SERVIDOR DO JOGO..."), 120, 260, 42, WHITE);
    }
    else if (conexao_server == 1)
    {
        DrawText(TextFormat("CONECTADO AO SERVIDOR!"), 12, 570, 23, WHITE);
    }
    else
    {
        DrawText(TextFormat("ERRO AO CONECTAR AO SERVIDOR DO JOGO"), 37, 260, 40, RED);
        DrawText(TextFormat("TENTE NOVAMENTE MAIS TARDE!"), 137, 330, 40, WHITE);
    }
    return;
}

void incluir_menu13(long int contador_tempo[2], int quantidades_cartas[3], char *nome_player1, char *nome_player2, int vez_jogar, int tipo_jogo)
{
    DrawText(TextFormat("%02d:%02d", (contador_tempo[1] / 3600), (contador_tempo[1] / 60 % 60)), 15, 8, 30, WHITE);
    DrawRectangleLinesEx((Rectangle){3, 4, 99, 36}, 4, WHITE);

    DrawText(TextFormat("Pilha: %d", quantidades_cartas[2] * 2), 15, 45, 30, WHITE);
    DrawRectangleLinesEx((Rectangle){3, 41, 136, 36}, 4, WHITE);

    DrawText(TextFormat("%s", nome_player1), 320, 505, 33, NOSSO_AZUL);
    DrawRectangleLinesEx((Rectangle){320, 540, 125, 55}, 4, NOSSO_AMARELO);
    DrawText(TextFormat("%d", quantidades_cartas[1]), 358, 548, 45, NOSSO_AMARELO);

    DrawText(TextFormat("%s", nome_player2), 530, 40, 33, NOSSO_AZUL);
    DrawRectangleLinesEx((Rectangle){562, 75, 125, 55}, 4, NOSSO_AMARELO);
    DrawText(TextFormat("%d", quantidades_cartas[0]), 600, 83, 45, NOSSO_AMARELO);

    if (vez_jogar == 1 && tipo_jogo == 1)
    {
        DrawText(TextFormat("Vez de Jogar: %s", nome_player1), 320, 5, 30, WHITE);
    }
    else if (vez_jogar == 1 && tipo_jogo == 2)
    {
        DrawText(TextFormat("Vez de Jogar: %s", nome_player2), 320, 5, 30, WHITE);
    }
    else if (vez_jogar == -1 && tipo_jogo == 1)
    {
        DrawText(TextFormat("Vez de Jogar: %s", nome_player2), 320, 5, 30, WHITE);
    }
    else if (vez_jogar == -1 && tipo_jogo == 2)
    {
        DrawText(TextFormat("Vez de Jogar: %s", nome_player1), 320, 5, 30, WHITE);
    }

    return;
}

void desenhaJogoMultiplayerLinux(RenderTexture2D *target, Botao *botao, Texture2D fundo)
{

    BeginTextureMode(*target);       // Tudo que for desenhado dessa função até EndTextureMode será automaticamente escalado
    ClearBackground(BLUE);           // Fundo da tela
    DrawTexture(fundo, 0, 0, WHITE); // Desenha o fundo

    desenharBotaoTxt(botao);

    DrawText(TextFormat("A funcionalidade do jogo multiplayer está \n\ndisponivel apenas para usuários Windows!"), 40, 225, 44, WHITE);

    resaltaBotoes();

    EndTextureMode();
    desenhoRedimensionado(target); // Chama a função que desenha redimensionadamente
    return;
}
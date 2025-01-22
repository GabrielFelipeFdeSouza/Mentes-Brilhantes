// FUNÇÕES DE DESENHO PARA A TELA DE GERENCIAMENTO DE CARTAS

#include "main.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include "structs-gerais.h"
#include <string.h>
#include "desenho-gerenciador-cartas.h"
#include "desenho-geral.h"
#include "funcoes-controle-geral.h"
#include "cores.h"

extern Vector2 posicao_mouse; // Chamada da variavel global posicao_mouse

void desenhoGerenciador(RenderTexture2D *target, Botao botoes[], int quantidade_botoes, Texture2D fundo, int submenu_tela, Texture2D seta, Texture2D frente_carta, int carta_atual, int total_cartas, Carta carta, Texture2D *img_carta, int exportou, int *retornos_funcoes, RadioButton botoes_radio[], int quantidade_botoes_radio, TextBox caixa_texto[], Seletor *caixas, TextBox caixa_texto_pesquisar[])
{

    BeginTextureMode(*target); // Tudo que for desenhado dessa função até EndTextureMode será automaticamente escalado
    ClearBackground(RAYWHITE); // Fundo da tela

    DrawTexture(fundo, 0, 0, WHITE); // Desenha o fundo

    DrawRectangleLinesEx((Rectangle){0, 275, 311, 325}, 3, BLACK); // Desenha um retangulo preto vazado para controles

    DrawTexture(seta, 910, 255, WHITE);                                 // Desenha a seta da direita
    DrawTextureEx(seta, (Vector2){400, 255 + 72}, 180.0f, 1.0f, WHITE); // Desenha a seta da esquerda

    desenhaCarta(500, 100, &frente_carta, &carta, img_carta); // Chama a função para desenhar a carta na posição x,y

    DrawRectangleLinesEx((Rectangle){320, 15, 160, 55}, 5, WHITE); // Desenha um retangulo branco para numero de cartas
    DrawText(TextFormat("%d / %d", carta_atual, total_cartas), 333, 25, 35, WHITE);

    if (submenu_tela == 4 && botoes_radio[5].estado != true)
    {
        DrawText(TextFormat("de"), 142, 288, 27, BLACK);
    } // Desenha o "de" para caixas de valores

    switch (submenu_tela)
    {
    case 1:
        incluir_adicionar(botoes_radio, quantidade_botoes_radio, 1, caixa_texto, caixas);
        break;
    case 3:
        incluir_editar(botoes_radio, quantidade_botoes_radio, 1, caixa_texto, caixas);
        break;
    case 4:
        incluir_pesquisar(botoes_radio, quantidade_botoes_radio, 1, caixa_texto_pesquisar, caixas);
        break;
    case 5:
        desenharBotaoTxt(&botoes[10], 1);
        incluir_listar();
        break;
    case 6:
        incluir_exportar(exportou);
        break;

    default:
        break;
    }

    for (int t = 0; t < quantidade_botoes; t++)
    {

        if (t == 7 || t == 8 || t == 9)
        {
            if (submenu_tela == 1)
            {
                desenharBotaoTxt(botoes[7]);
            }
            if (submenu_tela == 3)
            {
                desenharBotaoTxt(botoes[8]);
            }
            if (submenu_tela == 4)
            {
                desenharBotaoTxt(botoes[9]);
            }
        }
        else
        {
            desenharBotaoTxt(botoes[t]);
        }

    } // Desenha todos os botões - Nulos e normais

    if (retornos_funcoes[0])
    {
        DrawText(TextFormat("Erro ao excluir carta, há apenas uma!"), 506, 27, 25, BLACK);
        DrawText(TextFormat("Erro ao excluir carta, há apenas uma!"), 508, 29, 25, RED);
    }

    if (retornos_funcoes[1] == 1)
    {
        DrawText(TextFormat("Erro ao adicionar a carta,"), 570, 25, 25, BLACK);
        DrawText(TextFormat("Erro ao adicionar a carta,"), 572, 27, 25, RED);
        DrawText(TextFormat("parametros vazios / errados!"), 555, 53, 25, BLACK);
        DrawText(TextFormat("parametros vazios / errados!"), 557, 55, 25, RED);
    }

    if (retornos_funcoes[1] == 2)
    {
        DrawText(TextFormat("Erro ao adicionar a carta,"), 570, 25, 25, BLACK);
        DrawText(TextFormat("Erro ao adicionar a carta,"), 572, 27, 25, RED);
        DrawText(TextFormat("reveja os parametros hexadecimal!"), 512, 53, 25, BLACK);
        DrawText(TextFormat("reveja os parametros hexadecimal!"), 514, 55, 25, RED);
    }

    if (retornos_funcoes[1] == 3)
    {
        DrawText(TextFormat("Erro ao adicionar a carta,"), 570, 25, 25, BLACK);
        DrawText(TextFormat("Erro ao adicionar a carta,"), 572, 27, 25, RED);
        DrawText(TextFormat("já existe um supertrunfo no baralho!"), 496, 53, 25, BLACK);
        DrawText(TextFormat("já existe um supertrunfo no baralho!"), 498, 55, 25, RED);
    }

    if (retornos_funcoes[2] == 1)
    {
        DrawText(TextFormat("Erro ao adicionar a carta,"), 570, 25, 25, BLACK);
        DrawText(TextFormat("Erro ao adicionar a carta,"), 572, 27, 25, RED);
        DrawText(TextFormat("parametros errados!"), 615, 53, 25, BLACK);
        DrawText(TextFormat("parametros errados!"), 617, 55, 25, RED);
    }

    if (retornos_funcoes[2] == 2)
    {
        DrawText(TextFormat("Erro ao editar a carta,"), 594, 25, 25, BLACK);
        DrawText(TextFormat("Erro ao editar a carta,"), 596, 27, 25, RED);
        DrawText(TextFormat("reveja os parametros hexadecimal!"), 512, 53, 25, BLACK);
        DrawText(TextFormat("reveja os parametros hexadecimal!"), 514, 55, 25, RED);
    }

    if (retornos_funcoes[2] == 3)
    {
        DrawText(TextFormat("Erro ao editar a carta,"), 570, 25, 25, BLACK);
        DrawText(TextFormat("Erro ao editar a carta,"), 572, 27, 25, RED);
        DrawText(TextFormat("já existe um supertrunfo no baralho!"), 496, 53, 25, BLACK);
        DrawText(TextFormat("já existe um supertrunfo no baralho!"), 498, 55, 25, RED);
    }

    // DrawText(TextFormat("Posição do mouse: (%.2f,%.2f)", posicao_mouse.x, posicao_mouse.y), 450, 570, 20, BLUE);

    resaltaBotoes();

    EndTextureMode();

    desenhoRedimensionado(target); // Chama a função que desenha redimensionadamente

    return;
}

void incluir_listar()
{

    DrawRectangleLinesEx((Rectangle){4, 295, 302, 116}, 4, NOSSO_AMARELO);
    DrawText("QUANTIDADE DE", 8, 300, 35, NOSSO_CIANO);
    DrawText("QUANTIDADE DE", 10, 302, 35, NOSSO_AZUL);
    DrawText("CARTAS:", 79, 337, 35, NOSSO_CIANO);
    DrawText("CARTAS:", 81, 339, 35, NOSSO_AZUL);
    DrawText(TextFormat("%d", quantidade_cartas), 142, 373, 35, NOSSO_AZUL);
    DrawText(TextFormat("%d", quantidade_cartas), 140, 371, 35, NOSSO_AMARELO);

    return;
} // Função que desenha a listagem de cartas

void incluir_exportar(int exportou)
{

    DrawRectangleLinesEx((Rectangle){4, 280, 302, 182}, 4, NOSSO_AMARELO);

    if (exportou == 1)
    {
        DrawText(TextFormat("Cartas"), 94, 293, 35, NOSSO_AMARELO);
        DrawText(TextFormat("Exportadas"), 63, 331, 35, NOSSO_AMARELO);
        DrawText(TextFormat("Na raiz do game"), 30, 373, 32, NOSSO_AZUL);
        DrawText(TextFormat("-Cartas.csv-"), 42, 411, 35, NOSSO_AZUL);
    }
    else
    {
        DrawText(TextFormat("Erro ao"), 100, 300, 35, NOSSO_AMARELO);
        DrawText(TextFormat("Exportar!"), 70, 338, 35, NOSSO_AMARELO);
    }

    return;
} // Função que desenha a listagem de cartas

void incluir_adicionar(RadioButton botoes_radio[], int quantidade_botoes_radio, int grupo_selecionado, TextBox *caixa_texto, Seletor *caixas)
{

    desenhaRadioButton(botoes_radio, quantidade_botoes_radio, grupo_selecionado);
    desenhaSeletor(caixas, 1, grupo_selecionado);
    resaltaRadioButton(botoes_radio, quantidade_botoes_radio, grupo_selecionado);
    checaRadioButton(botoes_radio, quantidade_botoes_radio, grupo_selecionado);
    checaSeletor(caixas, 1, grupo_selecionado);
    for (int i = 0; i < 6; i++)
    {
        desenhaTextBox(&caixa_texto[i]);
    }

    return;
}

void incluir_editar(RadioButton botoes_radio[], int quantidade_botoes_radio, int grupo_selecionado, TextBox *caixa_texto, Seletor *caixas)
{

    desenhaRadioButton(botoes_radio, quantidade_botoes_radio, grupo_selecionado);
    desenhaSeletor(caixas, 1, grupo_selecionado);
    resaltaRadioButton(botoes_radio, quantidade_botoes_radio, grupo_selecionado);
    checaRadioButton(botoes_radio, quantidade_botoes_radio, grupo_selecionado);
    checaSeletor(caixas, 1, grupo_selecionado);

    for (int i = 0; i < 6; i++)
    {
        desenhaTextBox(&caixa_texto[i]);
    }

    return;
}

void incluir_pesquisar(RadioButton botoes_radio[], int quantidade_botoes_radio, int grupo_selecionado, TextBox *caixa_texto_pesquisar, Seletor *caixas)
{

    desenhaRadioButton(botoes_radio, quantidade_botoes_radio, grupo_selecionado);
    desenhaSeletor(caixas, 1, grupo_selecionado);
    resaltaRadioButton(botoes_radio, quantidade_botoes_radio, grupo_selecionado);
    checaRadioButton(botoes_radio, quantidade_botoes_radio, grupo_selecionado);
    checaSeletor(caixas, 1, grupo_selecionado);

    for (int i = 0; i < 5; i++)
    {
        desenhaTextBox(&caixa_texto_pesquisar[i]);
    }

    return;
}
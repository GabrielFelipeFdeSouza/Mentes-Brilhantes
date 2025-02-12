/*
-->FUNÇÕES MENU<--
Basicamente nesse arquivo, o menu principal do jogo é controlado, ele é bem simples
apenas contendo os controles dos botões que redirecionam para os menus e também o
controle do som geral, podendo habilita-lo ou não.
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
#include "desenho-geral.h"
#include "funcoes-menu.h"
#include "cores.h"
#include "desenho-menu.h"
#include "funcoes-controle-geral.h"

// Função de declaração do menu:
void menu(RenderTexture2D *target, Music *musica, Sound sons[])
{

    //---------------------------------
    // VARIAVEIS
    //---------------------------------

    // Definindo os botões do menu:
    Botao botoes_menu[5]; // Declara todos os botões da tela de menu
    botoes_menu[0].colisao = criarBotao(&botoes_menu[0], 42, 525, NOSSO_AZUL, "SAIR", 33, NOSSO_CINZA);
    botoes_menu[1].colisao = criarBotao(&botoes_menu[1], 42, 450, NOSSO_AZUL, "Créditos", 33, NOSSO_CINZA);
    botoes_menu[2].colisao = criarBotao(&botoes_menu[2], 42, 375, NOSSO_AZUL, "Gerenciar cartas", 33, NOSSO_CINZA);
    botoes_menu[3].colisao = criarBotao(&botoes_menu[3], 42, 300, NOSSO_AZUL, "Singleplayer", 33, NOSSO_CINZA);
    botoes_menu[4].colisao = criarBotao(&botoes_menu[4], 42, 225, NOSSO_AZUL, "Multiplayer", 33, NOSSO_CINZA);

    BotaoNulo botao_menu_som[1]; //Declarando o botão de som da tela
    botao_menu_som[0].colisao = (Rectangle){916, 525, 50, 50};
    botao_menu_som[0].cor_botao = NOSSO_AZUL;

    // Carregando as imagens:
    Texture2D fundoss = LoadTexture("img/fundo-menu.png");      // Carrega a imagem btn com som
    Texture2D fundo = ResizeTexture(fundoss, 1000, 600);        // Carrega a imagem btn com som
    Texture2D btn_c_som_cru = LoadTexture("img/c-som.png");     // Carrega a imagem btn com som
    Texture2D btn_s_som_cru = LoadTexture("img/s-som.png");     // Carrega a imagem btn sem som
    Texture2D btn_c_som = ResizeTexture(btn_c_som_cru, 50, 50); // Redimensiona a imagem
    Texture2D btn_s_som = ResizeTexture(btn_s_som_cru, 50, 50); // Redimensiona a imagem
    Texture2D img_btn_som = btn_c_som;

    // Condição de tela:
    while (tela == 0 || tela == 2)
    {

        // ESCALA:
        scaleX = (float)GetScreenWidth() / COMPRIMENTO_TELA;
        scaleY = (float)GetScreenHeight() / ALTURA_TELA;
        scale = (scaleX < scaleY) ? scaleX : scaleY;

        // CONTROLES GERAIS:
        checarSaida();                                                             // Chama a função que verifica se o usuário saiu
        checarTelaCheia();                                                         // Chama função que verifica as condições de tela cheia
        leMouse();                                                                 // Chama a função global de leitura de mouse
        desenhoMenu(target, botoes_menu, 5, botao_menu_som, &img_btn_som, &fundo); // Chama a função de desenho objetos do menu
        controleSons(0, *musica, sons[0]);                                         // Função de controle geral sons - mantem musica tocando

        //---------------------------------
        // CONTROLES RESALTA BOTOES
        //---------------------------------

        botoes_resaltar = 0; // Zerando para reuso

        for (int s = 0; s < 5; s++)
        {
            if (CheckCollisionPointRec(posicao_mouse, botoes_menu[s].colisao) && !coresIguais(botoes_menu[s].cor_botao, GREEN))
            {
                controleSons(1, *musica, sons[0]);
                botoes_resaltar = 1;
                break;
            }
            else if (!coresIguais(botoes_menu[s].cor_botao, GREEN))
            {
                botoes_resaltar = 0;
            }
        } // Percorre os botoes com texto para resaltar

        if (!botoes_resaltar)
        {
            if (CheckCollisionPointRec(posicao_mouse, botao_menu_som[0].colisao) && !coresIguais(botao_menu_som[0].cor_botao, GREEN))
            {
                controleSons(1, *musica, sons[0]);
                botao_menu_som[0].cor_botao = NOSSO_CIANO;
                botoes_resaltar = 1;
            }
            else if (!coresIguais(botao_menu_som[0].cor_botao, GREEN))
            {
                botao_menu_som[0].cor_botao = NOSSO_AZUL;
                botoes_resaltar = 0;
            }
        } //Resalta o botão de som

        //---------------------------------
        // CONTROLE BOTOES
        //---------------------------------

        if (checarClique(&botao_menu_som[0].colisao))
        {
            if (esta_mudo == false)
            {
                esta_mudo = true;
                controleSons(2, *musica, sons[1]); // Tira o som da musica
            }
            else
            {
                esta_mudo = false;
                controleSons(3, *musica, sons[1]); // Recoloca o som da musica
            }
        } // Controle do som

        if (checarClique(&botoes_menu[0].colisao) && estado_tela != 7)
        {
            estado_tela = 7;
            controleSons(1, *musica, sons[1]); // Função de controle geral sons - tocar som clicou
            botoes_menu[0].cor_botao = GREEN;
            trocar_tela = true;
        } // Sair

        if (checarClique(&botoes_menu[1].colisao) && estado_tela != 4)
        {
            estado_tela = 4;
            controleSons(1, *musica, sons[1]); // Função de controle geral sons - tocar som clicou
            botoes_menu[1].cor_botao = GREEN;
            trocar_tela = true;
        } // Creditos

        if (checarClique(&botoes_menu[2].colisao) && estado_tela != 1)
        {
            estado_tela = 1;
            controleSons(1, *musica, sons[1]); // Função de controle geral sons - tocar som clicou
            botoes_menu[2].cor_botao = GREEN;
            trocar_tela = true;
        } // Gerenciador Cartas

        if (checarClique(&botoes_menu[3].colisao) && estado_tela != 3)
        {
            estado_tela = 3;
            controleSons(1, *musica, sons[1]); // Função de controle geral sons - tocar som clicou
            botoes_menu[3].cor_botao = GREEN;
            trocar_tela = true;
        } // Singleplayer

        if (checarClique(&botoes_menu[4].colisao) && estado_tela != 5)
        {
            estado_tela = 5;
            controleSons(1, *musica, sons[1]); // Função de controle geral sons - tocar som clicou
            botoes_menu[4].cor_botao = GREEN;
            trocar_tela = true;
        } // Multiplayer

        //---------------------------------
        // CONTROLE TELAS
        //---------------------------------

        switch (estado_tela)
        {
        case 1:
            if (!IsSoundPlaying(sons[1]) && trocar_tela == true)
            {
                trocar_tela = false;
                UnloadTexture(btn_c_som);
                UnloadTexture(btn_s_som);
                UnloadTexture(btn_c_som_cru);
                UnloadTexture(btn_s_som_cru);
                UnloadTexture(img_btn_som);
                UnloadTexture(fundo);
                UnloadTexture(fundoss);
                tela = 1;
            } // Espera tocar para sair se o usuário deseja sair
            break;

        case 3:
            if (!IsSoundPlaying(sons[1]) && trocar_tela == true)
            {
                trocar_tela = false;
                UnloadTexture(btn_c_som);
                UnloadTexture(btn_s_som);
                UnloadTexture(btn_c_som_cru);
                UnloadTexture(btn_s_som_cru);
                UnloadTexture(img_btn_som);
                UnloadTexture(fundo);
                UnloadTexture(fundoss);
                tela = 3;
            } // Espera tocar para sair se o usuário deseja sair

            break;

        case 4:
            if (!IsSoundPlaying(sons[1]) && trocar_tela == true)
            {
                trocar_tela = false;
                UnloadTexture(btn_c_som);
                UnloadTexture(btn_s_som);
                UnloadTexture(btn_c_som_cru);
                UnloadTexture(btn_s_som_cru);
                UnloadTexture(img_btn_som);
                UnloadTexture(fundo);
                UnloadTexture(fundoss);
                tela = 4;
            } // Espera tocar para sair se o usuário deseja sair

            break;

        case 5:
            if (!IsSoundPlaying(sons[1]) && trocar_tela == true)
            {
                trocar_tela = false;
                UnloadTexture(btn_c_som);
                UnloadTexture(btn_s_som);
                UnloadTexture(btn_c_som_cru);
                UnloadTexture(btn_s_som_cru);
                UnloadTexture(img_btn_som);
                UnloadTexture(fundo);
                UnloadTexture(fundoss);
                tela = 5;
            } // Espera tocar para sair se o usuário deseja sair

            break;

        case 7:
            if (!IsSoundPlaying(sons[1]) && trocar_tela == true)
            {
                trocar_tela = false;
                UnloadTexture(btn_c_som);
                UnloadTexture(btn_s_som);
                UnloadTexture(btn_c_som_cru);
                UnloadTexture(btn_s_som_cru);
                UnloadTexture(img_btn_som);
                UnloadTexture(fundo);
                UnloadTexture(fundoss);
                tela = 10;
            } // Espera tocar para sair se o usuário deseja sair
            break;

        default:
            break;
        }

        // Contola IMG do som:

        if (esta_mudo == false)
        {
            img_btn_som = btn_c_som;
        }
        else
        {
            img_btn_som = btn_s_som;
        }

    } // Fim loop da tela de menu

    return;
}
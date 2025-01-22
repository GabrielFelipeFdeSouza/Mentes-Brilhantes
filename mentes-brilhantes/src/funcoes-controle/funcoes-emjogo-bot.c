/*
-->FUNÇÕES EM JOGO BOT (SINGLEPLAYER)<--
Aqui é onde é realizado o controle geral do menu de jogo singleplayer,
inicializando as variasveis, cuidando dos contadores de tempo e sistemas de
tela/botoes, além da logica basica dos submenus da tela.*/

//---------------------------------
// INCLUDES
//---------------------------------

#include "main.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include "structs-gerais.h"
#include <string.h>
#include "funcoes-emjogo-bot.h"
#include "funcoes-controle-geral.h"
#include "desenho-geral.h"
#include "cores.h"
#include <math.h>
#include <stdbool.h>
#include "desenho-game-bot.h"
#include <time.h>
#include "funcoes-adicionais-emjogo.h"

//---------------------------------
// FUNÇAO PRINCIPAL
//---------------------------------

void jogarSingleplayer(RenderTexture2D *target, Music *musica, Sound sons[])
{

    //---------------------------------
    // VARIAVEIS LOCAIS
    //---------------------------------

    int submenu_tela = 0; // Variavel do submenus do jogo - ajuda para correta lógica das telas - começa em configurações da partida
    Botao botoes[2];
    int dificuldade;                       // Variavel usada para fazer o sistema de gameplay do jogo
    int quantidades_cartas[3] = {0, 0, 0}; // Quantidade de cartas do bot, jogador e empates_seguidos nessa ordem
    // int quantidade_empates_seguidos = 0;
    long int contador_tempo[4] = {179, 0, 0, 211}; // Contadores de tempo baseado em FPS
    int id_imagem = -1;                            // Usado para carregar a imagem da carta
    int id_imagem_bot = -1;                        // Usado para carregar a imagem da carta
    Texture2D img_carta;
    Texture2D img_carta_bot;
    int vezJogar = 1;     // Começa jogando o player
    int btn_clicado = -1; // Botao clicado por ultimo do jogador
    bool clicado_btn = false;
    
    //---------------------------------
    // INICIALIZANDO OS VETORES E AS IMAGENS
    //---------------------------------

    // Incializando os vetores de cartas do bot e do jogador:
    Carta *cartas_bot = NULL;
    Carta *cartas_jogador = NULL;
    Carta *pilha_empate = NULL;
    cartas_jogador = (Carta *)malloc(sizeof(Carta));
    cartas_bot = (Carta *)malloc(sizeof(Carta));
    pilha_empate = (Carta *)malloc(sizeof(Carta));
    Carta carta;     // Carta usada para ser desenhada na tela
    Carta carta_bot; // Carta usada para ser desenhada na tela

    botoes[0].colisao = criarBotao(&botoes[0], 906, 552, NOSSO_AZUL, "MENU", 26, NOSSO_CINZA);
    botoes[1].colisao = criarBotao(&botoes[1], 65, 265, NOSSO_AZUL, "INICIAR JOGO", 26, NOSSO_CINZA);

    RadioButton botoes_radio[3];
    botoes_radio[0] = (RadioButton){0, "Fácil", {75, 160}, 12, NOSSO_BEGE, true, 1};
    botoes_radio[1] = (RadioButton){1, "Médio", {75, 195}, 12, NOSSO_BEGE, false, 1};
    botoes_radio[2] = (RadioButton){2, "Difícil", {75, 230}, 12, NOSSO_BEGE, false, 1};

    // Carregando as imagens:
    Texture2D fundo = LoadTexture("img/fundo-jogo.png");          // Carrega a imagem do fundo desse menu
    Texture2D fundo_carta = LoadTexture("img/fundo-carta.png");   // Carrega a imagem do fundo desse menu
    Texture2D frente_carta = LoadTexture("img/frente_carta.png"); // Carrega a imagem do frame frontal da carta

    //---------------------------------
    // LOOP GERAL
    //---------------------------------

    while (tela == 3)
    {

        //---------------------------------
        // CONTROLES GERAIS
        //---------------------------------

        // ESCALA:
        scaleX = (float)GetScreenWidth() / COMPRIMENTO_TELA;
        scaleY = (float)GetScreenHeight() / ALTURA_TELA;
        scale = (scaleX < scaleY) ? scaleX : scaleY;

        checarSaida();     // Chama a função que verifica se o usuário saiu
        checarTelaCheia(); // Chama função que verifica as condições de tela cheia
        leMouse();
        controleSons(0, *musica, sons[0]);
        desenhaJogoSingleplayer(target, botoes, fundo, botoes_radio, submenu_tela, contador_tempo, &img_carta, &carta, &frente_carta, quantidades_cartas, vezJogar, &img_carta_bot, &carta_bot, fundo_carta, btn_clicado);

        //---------------------------------
        // CONTROLES RESALTA BOTOES
        //---------------------------------

        botoes_resaltar = 0; // Zerando para reuso

        if (CheckCollisionPointRec(posicao_mouse, botoes[0].colisao) && !coresIguais(botoes[0].cor_botao, GREEN))
        {
            botoes_resaltar = 1;
        }
        else if (!coresIguais(botoes[0].cor_botao, GREEN))
        {
            botoes_resaltar = 0;
        }

        if (submenu_tela == 0 && !botoes_resaltar)
        {
            if (CheckCollisionPointRec(posicao_mouse, botoes[1].colisao) && !coresIguais(botoes[1].cor_botao, GREEN))
            {
                botoes_resaltar = 1;
            }
            else if (!coresIguais(botoes[1].cor_botao, GREEN))
            {
                botoes_resaltar = 0;
            }
        }

        if (submenu_tela == 2 && !botoes_resaltar)
        {
            if (vezJogar == 1)
            {
                for (int s = 0; s < 4; s++)
                {
                    if (CheckCollisionPointRec(posicao_mouse, (Rectangle){15 + 21, 130 + 244 + (s * 45), 244, 35}))
                    {
                        botoes_resaltar = 1;
                        break;
                    }
                }
            }
            else
            {
                for (int s = 0; s < 4; s++)
                {
                    if (CheckCollisionPointRec(posicao_mouse, (Rectangle){15 + 21, 130 + 244 + (s * 45), 244, 35}))
                    {
                        botoes_resaltar = 2;
                        break;
                    }
                }
            }
        }

        /*if (!botoes_resaltar)
        {
            if (CheckCollisionPointRec(posicao_mouse, botao_menu_som[0].colisao) && !coresIguais(botao_menu_som[0].cor_botao, GREEN))
            {
                botao_menu_som[0].cor_botao = NOSSO_CIANO;
                botoes_resaltar = 1;
            }
            else if (!coresIguais(botao_menu_som[0].cor_botao, GREEN))
            {
                botao_menu_som[0].cor_botao = NOSSO_AZUL;
                botoes_resaltar = 0;
            }
        }*/

        //---------------------------------
        // CONTROLES DO JOGO
        //---------------------------------

        if (submenu_tela == 0)
        {
            if (checarClique(&botoes[1].colisao) && estado_tela != 2)
            {
                controleSons(1, *musica, sons[1]); // Função de controle geral sons - tocar som clicou
                botoes[1].cor_botao = GREEN;

                for (int u = 0; u < 3; u++)
                {
                    if (botoes_radio[u].estado)
                    {
                        dificuldade = u;
                        break;
                    }
                }

                submenu_tela = 1;
                iniciar_jogo_bot(&cartas_bot, &cartas_jogador, quantidades_cartas);

            } // Iniciar Jogo
        }

        if (submenu_tela == 1)
        {
            contador_tempo[0]--;
            if (contador_tempo[0] <= 0)
            {
                submenu_tela = 2;
            }
        } // Contador para incio do jogo

        if (submenu_tela == 2)
        {
            contador_tempo[1]++; // Cronometro global

            // Alteração das cartas e imagens desenhadas:
            carta = cartas_jogador[0];
            if (id_imagem != carta.id)
            {
                id_imagem = carta.id;
                UnloadTexture(img_carta);
                img_carta = LoadTexture(carta.imagem);
            } // Usado para carregar a textura de uma carta apenas na troca de carta

            carta_bot = cartas_bot[0];
            if (id_imagem_bot != carta_bot.id)
            {
                id_imagem_bot = carta_bot.id;
                UnloadTexture(img_carta_bot);
                img_carta_bot = LoadTexture(carta_bot.imagem);
            } // Usado para carregar a textura de uma carta apenas na troca de carta

            // Cliques do jogador e do bot ao jogar:

            if (vezJogar == 1 && btn_clicado == -1 && contador_tempo[3] > 210)
            {
                btn_clicado = btnsCartasClicados(15, 130);
                if (btn_clicado != -1)
                {
                    clicado_btn = true;
                    contador_tempo[3] = 0;
                }
            } // Vez do jogador de jogar

            if (vezJogar == 0 && btn_clicado == -1 && contador_tempo[3] > 410)
            {
                btn_clicado = iaBot(cartas_bot, dificuldade);
                if (btn_clicado != -1)
                {
                    clicado_btn = true;
                    contador_tempo[3] = 0;
                }

            } // Vez do bot de jogar

            // Interpretador de cliques e ia do bot:

            if (vezJogar == 1 && clicado_btn == true && contador_tempo[3] > 209)
            {
                clicado(&btn_clicado, &cartas_bot, &cartas_jogador, &pilha_empate, quantidades_cartas, 1);
                clicado_btn = false;
                contador_tempo[2] = 0;
                checaVitoria(quantidades_cartas, &submenu_tela);
                vezJogar = 0;
            }

            if (vezJogar == 0 && clicado_btn == true && contador_tempo[3] > 209)
            {
                clicado(&btn_clicado, &cartas_bot, &cartas_jogador, &pilha_empate, quantidades_cartas, 1);
                clicado_btn = false;
                contador_tempo[2] = 0;
                checaVitoria(quantidades_cartas, &submenu_tela);
                vezJogar = 1;
            }

            // Contador de tempo secundário das ações:

            if (contador_tempo[3] < 420)
            {
                contador_tempo[3]++;
            }

        } // Em jogo

        //---------------------------------
        // CONTROLES BOTOES
        //---------------------------------

        if (checarClique(&botoes[0].colisao) && estado_tela != 2)
        {
            estado_tela = 2;
            controleSons(1, *musica, sons[1]); // Função de controle geral sons - tocar som clicou
            botoes[0].cor_botao = GREEN;
            trocar_tela = true;
        } // Voltar Menu

        //---------------------------------
        // CONTROLES TELAS
        //---------------------------------

        switch (estado_tela)
        {
        case 2:
            if (!IsSoundPlaying(sons[1]) && trocar_tela == true)
            {
                trocar_tela = false;
                UnloadTexture(fundo);
                free(cartas_bot);
                free(cartas_jogador);
                tela = 2;
            } // Espera tocar para sair se o usuário deseja sair
            break;

        default:
            break;
        }
    }

    return;
}
// FUNÇÕES PARA A TELA DE EM JOGO COM MULTIPLAYER - SEM SER PARTE DE DESENHO

//---------------------------------
// INCLUDES
//---------------------------------

#include "main.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include "structs-gerais.h"
#include <string.h>
#include "funcoes-emjogo-multiplayer.h"
#include "funcoes-controle-geral.h"
#include "desenho-geral.h"
#include "cores.h"
#include <math.h>
#include <stdbool.h>
#include "desenho-game-multiplayer.h"
#include <time.h>
#include "funcoes-adicionais-emjogo.h"
#include "funcoes-rede.h"
#include "escrever-arquivos.h"

#ifdef _WIN32

//---------------------------------
// FUNÇAO PRINCIPAL
//---------------------------------

void jogarMultiplayer(RenderTexture2D *target, Music *musica, Sound sons[])
{

    //---------------------------------
    // VARIAVEIS LOCAIS
    //---------------------------------

    int submenu_tela = 0; // Variavel do submenus do jogo - ajuda para correta lógica das telas - começa em configurações da partida
    Botao botoes[3];
    int conexao_server = 0;              // Variavel usada para conectar ao servidor
    int quantidades_cartas[3] = {0, 0, 0}; // Quantidade de cartas dos jogadores e empates_seguidos nessa ordem
    //  int quantidade_empates_seguidos = 0;
    long int contador_tempo[7] = {179, 0, 0, 211, 0, 0, 179}; // Contadores de tempo baseado em FPS
    int erros[3] = {220, 220, 220};                           // Usado para os erros dos menus
    int id_imagem = -1;                                       // Usado para carregar a imagem da carta
    int id_imagem_player2 = -1;                               // Usado para carregar a imagem da carta
    Texture2D img_carta;
    Texture2D img_carta_player2;
    int vezJogar = 1;     // Começa jogando o player
    int btn_clicado = -1; // Botao clicado por ultimo do jogador
    bool clicado_btn = false;
    int cartas_escolhidas[32];
    int comandos[2] = {0, 0};
    int id_sala = 0;
    char nome_jogador1[50];
    char nome_jogador2[50];
    char nome_jogadornullo[50];
    int tipo_entrada = 0;
    int tocou_saida = 0; //Sinalizador do tocar som da saida de usuário

    //---------------------------------
    // INICIALIZANDO OS VETORES E AS IMAGENS
    //---------------------------------

    botoes[0].colisao = criarBotao(&botoes[0], 906, 552, NOSSO_AZUL, "MENU", 26, NOSSO_CINZA);
    botoes[1].colisao = criarBotao(&botoes[1], 40, 265, NOSSO_AZUL, "CRIAR NOVA SALA", 30, NOSSO_CINZA);
    botoes[2].colisao = criarBotao(&botoes[2], 631, 265, NOSSO_AZUL, "ENTRAR NUMA SALA", 30, NOSSO_CINZA);
    
    TextBox caixa_texto[2];
    caixa_texto[0] = (TextBox){{627, 200, 340, 46}, NOSSO_CREME, "", "Código:", NOSSO_AZUL, true, true, 0, 0, 0};
    caixa_texto[1] = (TextBox){{310, 95, 340, 46}, NOSSO_CREME, "", "Nome Player:", NOSSO_AZUL, true, true, 0, 0, 0};

    // Carregando as imagens:
    Texture2D fundo = LoadTexture("img/fundo-jogo.png"); // Carrega a imagem do fundo desse menu

    // Incializando os vetores de cartas do bot e do jogador:
    Carta *cartas_jogador1 = NULL;
    Carta *cartas_jogador2 = NULL;
    Carta *pilha_empate = NULL;
    cartas_jogador1 = (Carta *)malloc(sizeof(Carta));
    cartas_jogador2 = (Carta *)malloc(sizeof(Carta));
    pilha_empate = (Carta *)malloc(sizeof(Carta));
    Carta carta1; // Carta usada para ser desenhada na tela
    Carta carta2; // Carta usada para ser desenhada na tela

    // botoes[1].colisao = criarBotao(&botoes[1], 65, 265, NOSSO_AZUL, "INICIAR JOGO", 26, NOSSO_CINZA);

    Texture2D fundo_carta = LoadTexture("img/fundo-carta.png");   // Carrega a imagem do fundo desse menu
    Texture2D frente_carta = LoadTexture("img/frente_carta.png"); // Carrega a imagem do frame frontal da carta

    //---------------------------------
    // LOOP GERAL
    //---------------------------------

    strcpy(nome_jogadornullo, "nulo");

    while (tela == 5)
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
        desenhaJogoMultiplayer(target, botoes, fundo, submenu_tela, conexao_server, caixa_texto, erros, id_sala, contador_tempo, quantidades_cartas, fundo_carta, frente_carta, carta1, carta2, &img_carta, &img_carta_player2, btn_clicado, nome_jogador1, nome_jogador2, vezJogar, tipo_entrada);

        //---------------------------------
        // CONTROLES RESALTA BOTOES
        //---------------------------------

        botoes_resaltar = 0; // Zerando para reuso

        if(submenu_tela == 8 && !tocou_saida){
            controleSons(1, *musica, sons[2]);
            tocou_saida = 1;
        }

        if (submenu_tela == 6 && !tocou_saida)
        {
            controleSons(1, *musica, sons[4]);
            tocou_saida = 1;
        }

        if (submenu_tela == 5 && !tocou_saida)
        {
            controleSons(1, *musica, sons[3]);
            tocou_saida = 1;
        }

        if (submenu_tela == 0 && conexao_server == 1)
        {
            for (int t = 0; t < 3; t++)
            {
                if (CheckCollisionPointRec(posicao_mouse, botoes[t].colisao) && !coresIguais(botoes[t].cor_botao, GREEN))
                {
                    controleSons(1, *musica, sons[0]);
                    botoes_resaltar = 1;
                    break;
                }
                else if (!coresIguais(botoes[t].cor_botao, GREEN))
                {
                    botoes_resaltar = 0;
                }
            }
        }

        if ((submenu_tela == 1 || submenu_tela == 2 || submenu_tela == 3 || submenu_tela == 5 || submenu_tela == 6 || submenu_tela == 8) && !botoes_resaltar)
        {
            if (CheckCollisionPointRec(posicao_mouse, botoes[0].colisao) && !coresIguais(botoes[0].cor_botao, GREEN))
            {
                controleSons(1, *musica, sons[0]);
                botoes_resaltar = 1;
            }
            else if (!coresIguais(botoes[0].cor_botao, GREEN))
            {
                botoes_resaltar = 0;
            }
        }

        if (submenu_tela == 2 && !botoes_resaltar)
        {

            if ((vezJogar == 1 && tipo_entrada == 1) || (vezJogar == -1 && tipo_entrada == 2))
            {
                for (int s = 0; s < 4; s++)
                {
                    if (CheckCollisionPointRec(posicao_mouse, (Rectangle){15 + 21, 130 + 244 + (s * 45), 244, 35}))
                    {
                        controleSons(1, *musica, sons[0]);
                        botoes_resaltar = 1;
                        break;
                    }
                }
            }
            else if ((vezJogar == -1 && tipo_entrada == 1) || (vezJogar == 1 && tipo_entrada == 2))
            {
                for (int s = 0; s < 4; s++)
                {
                    if (CheckCollisionPointRec(posicao_mouse, (Rectangle){15 + 21, 130 + 244 + (s * 45), 244, 35}))
                    {
                        controleSons(1, *musica, sons[0]);
                        botoes_resaltar = 2;
                        break;
                    }
                }
            }
        }

        //---------------------------------
        // CONTROLES DO JOGO
        //---------------------------------

        if (submenu_tela == 0 && conexao_server == 0)
        {
            escreverLog("Conectando ao servidor do jogo...");

            if (conectar_server())
            {
                escreverLog("Conexao ao servidor bem-sucedida.");
                conexao_server = 1;
            }
            else
            {
                escreverLog("Falha na conexao ao servidor.");
                conexao_server = -1;
            }
        } // Menu inicial, tenta conexão ao server do jogo

        if (submenu_tela == 0 && conexao_server == 1)
        {
            // CONTROLE CAIXAS DE TEXTO:

            for (int r = 0; r < 2; r++)
            {
                if (strcmp(caixa_texto[r].texto, "") == 0)
                {
                    caixa_texto[r].placeholder = true;
                }
                else
                {
                    caixa_texto[r].placeholder = false;
                }
            }

            for (int n = 0; n < 2; n++)
            {
                if (checarClique(&caixa_texto[n].caixa))
                {
                    caixa_texto[0].subcaixa = 0;
                    caixa_texto[1].subcaixa = 0;
                    caixa_texto[n].subcaixa = 1;
                    break;
                }
            }

            if (caixa_texto[0].subcaixa)
            {
                leTeclado(caixa_texto[0].texto, &caixa_texto[0].tamanho, caixa_texto[0].subgrupo, 8); // Chama a funçaõ que le caracteres do teclado
            }
            if (caixa_texto[1].subcaixa)
            {
                leTeclado(caixa_texto[1].texto, &caixa_texto[1].tamanho, caixa_texto[1].subgrupo, 30); // Chama a funçaõ que le caracteres do teclado
            }

            // CONTROLE BOTÕES E FUNÇÕES:

            if (checarClique(&botoes[1].colisao) && estado_tela != 2)
            {
                controleSons(1, *musica, sons[1]); // Função de controle geral sons - tocar som clicou
                botoes[1].cor_botao = GREEN;
                if (caixa_texto[1].tamanho >= 1)
                {
                    strcpy(nome_jogador1, caixa_texto[1].texto);
                    criarNovaSala(&cartas_jogador1, &cartas_jogador2, quantidades_cartas, cartas_escolhidas);
                    id_sala = aleatorizarSala();
                    id_master_saida = id_sala;
                    comandos[1] = 16;
                    enviarDados(id_sala, cartas_escolhidas, nome_jogador1, comandos);
                    submenu_tela = 1;
                    tipo_entrada = 1;
                }
                else
                {
                    erros[0] = 0;
                }
            } // Criar Nova sala

            if (checarClique(&botoes[2].colisao) && estado_tela != 2)
            {
                controleSons(1, *musica, sons[1]); // Função de controle geral sons - tocar som clicou
                botoes[2].cor_botao = GREEN;
                if ((caixa_texto[0].tamanho >= 8) && (caixa_texto[1].tamanho >= 1))
                {
                    id_sala = atoi(caixa_texto[0].texto);
                    id_master_saida = id_sala;
                    if (verificarSalaVazia(id_sala))
                    {
                        strcpy(nome_jogador1, caixa_texto[1].texto);
                        ReceberDadosIniciais(nome_jogador2, cartas_escolhidas, id_sala);
                        EntrarSala(&cartas_jogador1, &cartas_jogador2, quantidades_cartas, cartas_escolhidas);
                        comandos[0] = 1;
                        comandos[1] = 15;
                        enviarDados(id_sala, cartas_escolhidas, nome_jogador1, comandos);
                        submenu_tela = 3;
                        tipo_entrada = 2;
                    }
                    else
                    {
                        erros[2] = 0;
                    }
                }
                else
                {
                    erros[1] = 0;
                    erros[0] = 221;
                }
            } // Entrar numa sala

        } // Se conectado aos server permite novas salas / entrar em salas

        if (submenu_tela == 1)
        {
            if (contador_tempo[4] > 20)
            {
                contador_tempo[4] = 0;
                lerServidor1(id_sala, comandos, nome_jogador2);
                if (comandos[0] == 1 && comandos[1] == 15)
                {
                    submenu_tela = 3;
                }
            }
            contador_tempo[4]++;
        } // Sala criada, aguardando player2 conectar

        if (submenu_tela == 3)
        {
            if (contador_tempo[6] < 1)
            {
                submenu_tela = 2;
            }
            contador_tempo[6]--;
        }

        if (submenu_tela == 2)
        {
            if (contador_tempo[5] > 30)
            {
                contador_tempo[5] = 0;
                lerServidor2(id_sala, &submenu_tela);
            }
            contador_tempo[5]++;

            if (contador_tempo[3] < 411)
            {
                contador_tempo[3]++;
            }

            contador_tempo[1]++; // Cronometro global

            if (tipo_entrada == 1)
            {
                // Alteração das cartas e imagens desenhadas:
                carta1 = cartas_jogador1[0];
                if (id_imagem != carta1.id)
                {
                    id_imagem = carta1.id;
                    UnloadTexture(img_carta);
                    img_carta = LoadTexture(carta1.imagem);
                } // Usado para carregar a textura de uma carta apenas na troca de carta

                carta2 = cartas_jogador2[0];
                if (id_imagem_player2 != carta2.id)
                {
                    id_imagem_player2 = carta2.id;
                    UnloadTexture(img_carta_player2);
                    img_carta_player2 = LoadTexture(carta2.imagem);
                } // Usado para carregar a textura de uma carta apenas na troca de carta

                // Cliques do jogador e do bot ao jogar:

                if (vezJogar == 1 && btn_clicado == -1 && contador_tempo[3] > 210)
                {
                    btn_clicado = btnsCartasClicados(15, 130);
                    if (btn_clicado != -1)
                    {
                        clicado_btn = true;
                        contador_tempo[3] = 0;
                        comandos[0] = btn_clicado;
                        comandos[1] = -1;
                        enviarDados(id_sala, cartas_escolhidas, nome_jogadornullo, comandos);
                    }
                } // Vez do jogador1 de jogar

                if (vezJogar == -1 && btn_clicado == -1 && contador_tempo[3] > 210)
                {
                    if (contador_tempo[4] > 30)
                    {
                        contador_tempo[4] = 0;
                        lerServidor1(id_sala, comandos, nome_jogadornullo);
                        if (comandos[1] == 1)
                        {
                            contador_tempo[3] = 0;
                            clicado_btn = true;
                            btn_clicado = comandos[0];
                        }
                    }
                    contador_tempo[4]++;
                } // Vez do jogador2 de jogar

                // Interpretador de cliques:

                if (vezJogar == 1 && clicado_btn == true && contador_tempo[3] > 209)
                {
                    clicado(&btn_clicado, &cartas_jogador2, &cartas_jogador1, &pilha_empate, quantidades_cartas,tipo_entrada);
                    clicado_btn = false;
                    contador_tempo[2] = 0;
                    checaVitoria(quantidades_cartas, &submenu_tela);
                    vezJogar = -1;
                }

                if (vezJogar == -1 && clicado_btn == true && contador_tempo[3] > 209)
                {
                    clicado(&btn_clicado, &cartas_jogador2, &cartas_jogador1, &pilha_empate, quantidades_cartas, tipo_entrada);
                    clicado_btn = false;
                    contador_tempo[2] = 0;
                    checaVitoria(quantidades_cartas, &submenu_tela);
                    vezJogar = 1;
                }
            } // Entrada nova sala

            if (tipo_entrada == 2)
            {
                // Alteração das cartas e imagens desenhadas:
                carta1 = cartas_jogador1[0];
                if (id_imagem != carta1.id)
                {
                    id_imagem = carta1.id;
                    UnloadTexture(img_carta);
                    img_carta = LoadTexture(carta1.imagem);
                } // Usado para carregar a textura de uma carta apenas na troca de carta

                carta2 = cartas_jogador2[0];
                if (id_imagem_player2 != carta2.id)
                {
                    id_imagem_player2 = carta2.id;
                    UnloadTexture(img_carta_player2);
                    img_carta_player2 = LoadTexture(carta2.imagem);
                } // Usado para carregar a textura de uma carta apenas na troca de carta

                // Cliques do jogador e do bot ao jogar:

                if (vezJogar == -1 && btn_clicado == -1 && contador_tempo[3] > 210)
                {
                    btn_clicado = btnsCartasClicados(15, 130);
                    if (btn_clicado != -1)
                    {
                        clicado_btn = true;
                        contador_tempo[3] = 0;
                        comandos[0] = btn_clicado;
                        comandos[1] = 1;
                        enviarDados(id_sala, cartas_escolhidas, nome_jogadornullo, comandos);
                    }
                } // Vez do jogador de jogar

                if (vezJogar == 1 && btn_clicado == -1 && contador_tempo[3] > 210)
                {
                    if (contador_tempo[4] > 30)
                    {
                        contador_tempo[4] = 0;
                        lerServidor1(id_sala, comandos, nome_jogadornullo);
                        if (comandos[1] == -1)
                        {
                            contador_tempo[3] = 0;
                            clicado_btn = true;
                            btn_clicado = comandos[0];
                        }
                    }
                    contador_tempo[4]++;
                } // Vez do bot de jogar

                // Interpretador de cliques:

                if (vezJogar == -1 && clicado_btn == true && contador_tempo[3] > 209)
                {
                    clicado(&btn_clicado, &cartas_jogador2, &cartas_jogador1, &pilha_empate, quantidades_cartas, tipo_entrada);
                    clicado_btn = false;
                    contador_tempo[2] = 0;
                    checaVitoria(quantidades_cartas, &submenu_tela);
                    vezJogar = 1;
                }

                if (vezJogar == 1 && clicado_btn == true && contador_tempo[3] > 209)
                {
                    clicado(&btn_clicado, &cartas_jogador2, &cartas_jogador1, &pilha_empate, quantidades_cartas, tipo_entrada);
                    clicado_btn = false;
                    contador_tempo[2] = 0;
                    checaVitoria(quantidades_cartas, &submenu_tela);
                    vezJogar = -1;
                }
            } // Entrada sala existente

        } // Em jogo

        //---------------------------------
        // CONTROLES ERROS
        //---------------------------------

        for (int s = 0; s < 3; s++)
        {
            if (erros[s] < 221)
            {
                erros[s]++;
            }
        }

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
                if (id_sala != 0)
                {
                    encerrar_secao(id_sala, cartas_escolhidas, nome_jogador1, comandos);
                }
                trocar_tela = false;
                UnloadTexture(fundo);
                UnloadTexture(frente_carta);
                UnloadTexture(fundo_carta);
                UnloadTexture(img_carta);
                UnloadTexture(img_carta_player2);
                free(pilha_empate);
                free(cartas_jogador2);
                free(cartas_jogador1);
                tela = 2;
            } // Espera tocar para sair se o usuário deseja sair
            break;

        default:
            break;
        }

        if (!IsSoundPlaying(sons[1]))
        {
            for (int u = 0; u < 3; u++)
            {
                if (coresIguais(botoes[u].cor_botao, GREEN))
                    botoes[u].cor_botao = NOSSO_AZUL;
            }
        } // Muda apos clique a cor de fundo do botão
    }

    return;
}

#else

void jogarMultiplayer(RenderTexture2D *target, Music *musica, Sound sons[])
{

    //---------------------------------
    // VARIAVEIS LOCAIS
    //---------------------------------

    Botao botao;

    //---------------------------------
    // INICIALIZANDO OS VETORES E AS IMAGENS
    //---------------------------------

    botao.colisao = criarBotao(&botao, 906, 552, NOSSO_AZUL, "MENU", 26, NOSSO_CINZA);

    // Carregando as imagens:
    Texture2D fundo = LoadTexture("img/fundo-jogo.png"); // Carrega a imagem do fundo desse menu

    //---------------------------------
    // LOOP GERAL
    //---------------------------------

    while (tela == 5)
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
        desenhaJogoMultiplayerLinux(target, &botao, fundo);

        //---------------------------------
        // CONTROLES RESALTA BOTOES
        //---------------------------------

        botoes_resaltar = 0; // Zerando para reuso

        if (CheckCollisionPointRec(posicao_mouse, botao.colisao) && !coresIguais(botao.cor_botao, GREEN))
        {
            botoes_resaltar = 1;
        }
        else if (!coresIguais(botao.cor_botao, GREEN))
        {
            botoes_resaltar = 0;
        }

        //---------------------------------
        // CONTROLES BOTOES
        //---------------------------------

        if (checarClique(&botao.colisao) && estado_tela != 2)
        {
            estado_tela = 2;
            controleSons(1, *musica, sons[1]); // Função de controle geral sons - tocar som clicou
            botao.cor_botao = GREEN;
            trocar_tela = true;
        } // Voltar Menu

        //---------------------------------
        // CONTROLES TELAS
        //---------------------------------

        switch (estado_tela)
        {
        case 2:
            if (!IsSoundPlaying(sons[1]) && trocar_tela == true){
                trocar_tela = false;
                UnloadTexture(fundo);
                tela = 2;
            } // Espera tocar para sair se o usuário deseja sair
            break;

        default:
            break;
        }

    }
    return;
}

#endif
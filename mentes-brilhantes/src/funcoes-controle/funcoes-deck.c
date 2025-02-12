/*
-->FUNÇÕES DECK<--
Aqui é que o deck é totalmente controlado, desde as funções auxiliares dele
até seu desenho especifico, entre outros detalhes, esse é o coração do
gerenciador de cartas.
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
#include "funcoes-deck.h"
#include "funcoes-controle-geral.h"
#include "desenho-gerenciador-cartas.h"
#include "desenho-geral.h"
#include "cores.h"
#include "adicionar-cartas.h"
#include "pesquisa-cartas.h"
#include "excluir-cartas.h"
#include "editar-cartas.h"
#include "escrever-arquivos.h"
#include <math.h>
#include <stdbool.h>

// Função do gerenciador de cartas:
void gerenciarCartas(RenderTexture2D *target, Music *musica, Sound sons[])
{

    //---------------------------------
    // VARIAVEIS LOCAIS
    //---------------------------------

    int total_cartas;                      // Usada para passar a quantidade de cartas e posicionador correto, usado muito no pesquisar
    int submenu_tela = 5;                  // Variavel do submenus do gerenciador - inicio no listar
    int carta_atual = 1;                   // Variavel que representa a carta atual do jogador
    Carta carta;                           // Struct da carta que sera desenhada para o usuario
    Carta *cartas_desenho = NULL;          // Vetor de cartas a serem desenhadas, usada muito durante o pesquisar, que acaba filtrando as cartas
    int id_anterior = -1;                  // Id usado para selecionar a cartas pelas setas
    int exportou;                          // Usado para export das cartas no csv [0 - Não solicitado, 1 - exportado corretamente, 2 - erro]
    int contador_frames[4] = {0, 0, 0, 0}; // Usado para dar os avisos e eventos ao usuário e animações
    int retornos_funcoes[3] = {0, 0, 0};   // Usado no processamento do retorno das funções
    bool exclusor = false;                 // usada para ver se a carta foi excluida, então troca sua imagem

    Texture2D img_carta; // Usada na imagem do rosto atual

    // Definindo os botões do gerenciador:
    Botao botoes_gerenciador[11]; // Declara todos os botões da tela do gerenciador
    botoes_gerenciador[0].colisao = criarBotao(&botoes_gerenciador[0], 906, 552, NOSSO_AZUL, "MENU", 26, NOSSO_CINZA);
    botoes_gerenciador[1].tamanho_fonte_texto = criarBotaoTxtRedimensionavel(&botoes_gerenciador[1], 4, 3, 303, 53, NOSSO_AZUL, "ADICIONAR CARTA", NOSSO_CINZA);
    botoes_gerenciador[2].tamanho_fonte_texto = criarBotaoTxtRedimensionavel(&botoes_gerenciador[2], 4, 58, 303, 53, NOSSO_AZUL, "EXCLUIR CARTA", NOSSO_CINZA);
    botoes_gerenciador[3].tamanho_fonte_texto = criarBotaoTxtRedimensionavel(&botoes_gerenciador[3], 4, 111, 303, 53, NOSSO_AZUL, "EDITAR CARTA", NOSSO_CINZA);
    botoes_gerenciador[4].tamanho_fonte_texto = criarBotaoTxtRedimensionavel(&botoes_gerenciador[4], 4, 164, 303, 53, NOSSO_AZUL, "PESQUISAR CARTAS", NOSSO_CINZA);
    botoes_gerenciador[5].tamanho_fonte_texto = criarBotaoTxtRedimensionavel(&botoes_gerenciador[5], 4, 217, 151, 53, NOSSO_AZUL, "LISTAR", NOSSO_CINZA);
    botoes_gerenciador[6].tamanho_fonte_texto = criarBotaoTxtRedimensionavel(&botoes_gerenciador[6], 156, 217, 151, 53, NOSSO_AZUL, "EXPORT", NOSSO_CINZA);
    botoes_gerenciador[7].colisao = criarBotao(&botoes_gerenciador[7], 80, 545, NOSSO_AZUL, "ADICIONAR", 23, NOSSO_CINZA);
    botoes_gerenciador[8].colisao = criarBotao(&botoes_gerenciador[8], 100, 545, NOSSO_AZUL, "EDITAR", 23, NOSSO_CINZA);
    botoes_gerenciador[9].colisao = criarBotao(&botoes_gerenciador[9], 78, 545, NOSSO_AZUL, "PESQUISAR", 23, NOSSO_CINZA);
    botoes_gerenciador[10].colisao = criarBotao(&botoes_gerenciador[10], 42, 545, NOSSO_AZUL, "RESETAR CARTAS", 23, NOSSO_CINZA);

    // Definindo os botões invisiveis do gerenciador (Setas):
    BotaoNulo botoes_nulos_gerenciador[2]; // Declara os botões invisiveis do gerenciado
    botoes_nulos_gerenciador[0].colisao = (Rectangle){913, 263, 67, 56};
    botoes_nulos_gerenciador[0].cor_botao = NOSSO_AZUL;
    botoes_nulos_gerenciador[1].colisao = (Rectangle){329, 263, 67, 56};
    botoes_nulos_gerenciador[1].cor_botao = NOSSO_AZUL;

    // Definindo os botoes de radio usado nos submenus do gerenciado:
    RadioButton botoes_radio[6];
    botoes_radio[0] = (RadioButton){0, "Nome", {25, 338}, 10, NOSSO_BEGE, true, 1};
    botoes_radio[1] = (RadioButton){1, "Curiosidade", {25, 368}, 10, NOSSO_BEGE, false, 1};
    botoes_radio[2] = (RadioButton){2, "Criatividade", {25, 398}, 10, NOSSO_BEGE, false, 1};
    botoes_radio[3] = (RadioButton){3, "Inovação", {25, 428}, 10, NOSSO_BEGE, false, 1};
    botoes_radio[4] = (RadioButton){4, "Idade", {25, 458}, 10, NOSSO_BEGE, false, 1};
    botoes_radio[5] = (RadioButton){5, "Numero e letra", {25, 488}, 10, NOSSO_BEGE, false, 1};

    // Definindo a caixa de super-trunfo que é usada nos submenus do gerenciador:
    Seletor caixa;
    caixa = (Seletor){0, "Super Trunfo", {15, 510, 20, 20}, NOSSO_BEGE, false, 1};

    // Definindo as caixas de texto usadas para os campos de entrada do gerenciador:
    TextBox caixa_texto[6];
    caixa_texto[0] = (TextBox){{8, 283, 292, 37}, NOSSO_CREME, "", "Nome:", NOSSO_AZUL, true, true, 0, 0, 1};
    caixa_texto[1] = (TextBox){{8, 283, 292, 37}, NOSSO_CREME, "", "Curiosidade:", NOSSO_AZUL, true, true, 0, 2, 1};
    caixa_texto[2] = (TextBox){{8, 283, 292, 37}, NOSSO_CREME, "", "Criatividade:", NOSSO_AZUL, true, true, 0, 2, 1};
    caixa_texto[3] = (TextBox){{8, 283, 292, 37}, NOSSO_CREME, "", "Inovação:", NOSSO_AZUL, true, true, 0, 2, 1};
    caixa_texto[4] = (TextBox){{8, 283, 292, 37}, NOSSO_CREME, "", "Idade:", NOSSO_AZUL, true, true, 0, 2, 1};
    caixa_texto[5] = (TextBox){{8, 283, 292, 37}, NOSSO_CREME, "", "Numero e letra:", NOSSO_AZUL, true, true, 0, 0, 1};

    // Definindo as caixas de texto usada na pesquisa do gerenciador:
    TextBox caixa_texto_pesquisar[5];
    caixa_texto_pesquisar[0] = (TextBox){{8, 283, 292, 37}, NOSSO_CREME, "", "Nome:", NOSSO_AZUL, true, true, 0, 0, 1};
    caixa_texto_pesquisar[1] = (TextBox){{8, 283, 130, 37}, NOSSO_CREME, "", "Inicial:", NOSSO_AZUL, true, true, 0, 2, 1};
    caixa_texto_pesquisar[2] = (TextBox){{175, 283, 130, 37}, NOSSO_CREME, "", "Final:", NOSSO_AZUL, true, true, 0, 2, 0};
    caixa_texto_pesquisar[3] = (TextBox){{8, 283, 130, 37}, NOSSO_CREME, "", "Numero:", NOSSO_AZUL, true, true, 0, 0, 1};
    caixa_texto_pesquisar[4] = (TextBox){{175, 283, 130, 37}, NOSSO_CREME, "", "Letra:", NOSSO_AZUL, true, true, 0, 0, 0};

    // Carregando as imagens:
    Texture2D fundo = LoadTexture("img/fundo-gerenciador.png");   // Carrega a imagem do fundo desse menu
    Texture2D setass = LoadTexture("img/seta.png");               // Carega a img da seta
    Texture2D seta = ResizeTexture(setass, 72, 72);               // Redimensiona a seta
    Texture2D frente_carta = LoadTexture("img/frente_carta.png"); // Carrega a imagem do frame frontal da carta

    cartas_desenho = cartas; // Por padrão as cartas a serem desenhadas começam sendo o vetor de cartas global

    //---------------------------------
    // LOOP GERAL
    //---------------------------------

    while (tela == 1)
    {
        //---------------------------------
        // CONTROLES GERAIS
        //---------------------------------

        // ESCALA DA TELA:
        scaleX = (float)GetScreenWidth() / COMPRIMENTO_TELA;
        scaleY = (float)GetScreenHeight() / ALTURA_TELA;
        scale = (scaleX < scaleY) ? scaleX : scaleY;

        // FUNÇOES AUXILIARES GERAIS:
        checarSaida();                                                                                                                                                                                                                             // Verifica a saida do usuario do programa
        checarTelaCheia();                                                                                                                                                                                                                         // Verifica se o usuario deu togle em telacheia
        leMouse();                                                                                                                                                                                                                                 // Função que le as cordenadas da posição atual do mouse
        desenhoGerenciador(target, botoes_gerenciador, 9, &fundo, &submenu_tela, &seta, &frente_carta, &carta_atual, &total_cartas, &carta, &img_carta, &exportou, retornos_funcoes, botoes_radio, 6, caixa_texto, &caixa, caixa_texto_pesquisar); // Chama a função de desenho objetos do gerenciador
        controleSons(0, *musica, sons[0]);

        //---------------------------------
        // CONTROLES RESALTA BOTOES
        //---------------------------------

        botoes_resaltar = 0; // Zerando para reuso

        for (int s = 0; s < 7; s++)
        {
            if (CheckCollisionPointRec(posicao_mouse, botoes_gerenciador[s].colisao) && !coresIguais(botoes_gerenciador[s].cor_botao, GREEN))
            {
                controleSons(1, *musica, sons[0]);
                botoes_resaltar = 1;
                break;
            }
            else if (!coresIguais(botoes_gerenciador[s].cor_botao, GREEN))
            {
                botoes_resaltar = 0;
            }
        } // Percorre os botoes com texto para resaltar

        if (submenu_tela == 5 && !botoes_resaltar)
        {
            if (CheckCollisionPointRec(posicao_mouse, botoes_gerenciador[10].colisao) && !coresIguais(botoes_gerenciador[10].cor_botao, GREEN))
            {
                controleSons(1, *musica, sons[0]);
                botoes_resaltar = 1;
            }
            else if (!coresIguais(botoes_gerenciador[10].cor_botao, GREEN))
            {
                botoes_resaltar = 0;
            }
        } // No submenu 5, resalta o botão 10

        if (submenu_tela == 3 && !botoes_resaltar)
        {
            if (CheckCollisionPointRec(posicao_mouse, botoes_gerenciador[8].colisao) && !coresIguais(botoes_gerenciador[8].cor_botao, GREEN))
            {
                controleSons(1, *musica, sons[0]);
                botoes_resaltar = 1;
            }
            else if (!coresIguais(botoes_gerenciador[8].cor_botao, GREEN))
            {
                botoes_resaltar = 0;
            }
        } // No submenu 3, resalta o botão 8

        if (submenu_tela == 1 && !botoes_resaltar)
        {
            if (CheckCollisionPointRec(posicao_mouse, botoes_gerenciador[7].colisao) && !coresIguais(botoes_gerenciador[7].cor_botao, GREEN))
            {
                controleSons(1, *musica, sons[0]);
                botoes_resaltar = 1;
            }
            else if (!coresIguais(botoes_gerenciador[7].cor_botao, GREEN))
            {
                botoes_resaltar = 0;
            }
        } // No submenu 1, resalta o botão 7

        if (submenu_tela == 4 && !botoes_resaltar)
        {
            if (CheckCollisionPointRec(posicao_mouse, botoes_gerenciador[9].colisao) && !coresIguais(botoes_gerenciador[9].cor_botao, GREEN))
            {
                controleSons(1, *musica, sons[0]);
                botoes_resaltar = 1;
            }
            else if (!coresIguais(botoes_gerenciador[9].cor_botao, GREEN))
            {
                botoes_resaltar = 0;
            }
        } // No submenu 4, resalta o botão 9

        for (int v = 0; v < 2; v++)
        {
            if (botoes_resaltar == 1)
            {
                break;
            }

            if (CheckCollisionPointRec(posicao_mouse, botoes_nulos_gerenciador[v].colisao))
            {
                controleSons(1, *musica, sons[0]);
                botoes_resaltar = 1;
                break;
            }
            else if (!coresIguais(botoes_nulos_gerenciador[v].cor_botao, GREEN))
            {
                botoes_resaltar = 0;
            }
        } // Percorre os botoes sem texto para resaltar

        //---------------------------------
        // CONTROLES DAS CARTAS DESENHADAS
        //---------------------------------

        // CASO ONDE É O PESQUISAR:
        if (submenu_tela == 4)
        {
            carta = cartas_desenho[carta_atual - 1]; // Copia os dados da carta que será desenhada

            if (id_anterior != cartas_desenho[carta_atual - 1].id || exclusor)
            {
                exclusor = false;
                id_anterior = cartas_desenho[carta_atual - 1].id;
                UnloadTexture(img_carta);
                img_carta = LoadTexture(cartas_desenho[carta_atual - 1].imagem);
            } // Usado para carregar a textura de uma carta apenas na troca de carta / exclusão da atual
        }

        // CASO ONDE NÃO É O PESQUISAR:
        if (submenu_tela != 4)
        {
            total_cartas = quantidade_cartas; // O total de cartas é a quantidade global

            carta = cartas[carta_atual - 1]; // Copia os dados da carta que será desenhada

            if (id_anterior != cartas[carta_atual - 1].id || exclusor)
            {
                exclusor = false;
                id_anterior = cartas[carta_atual - 1].id;
                UnloadTexture(img_carta);
                img_carta = LoadTexture(cartas[carta_atual - 1].imagem);
            } // Usado para carregar a textura de uma carta apenas na troca de carta / exclusão da atual
            cartas_desenho = cartas; // As cartas a serem desenhadas recebe o vetor cartas global
        }

        //---------------------------------
        // CONTROLES DOS SUBMENUS
        //---------------------------------

        // PESQUISAR:
        if (submenu_tela == 4)
        {
            for (int u = 0; u < 5; u++)
            {
                if (strcmp(caixa_texto_pesquisar[u].texto, "") == 0)
                {
                    caixa_texto_pesquisar[u].placeholder = true;
                }
                else
                {
                    caixa_texto_pesquisar[u].placeholder = false;
                }
            } // Operando os placeholders das caixas de texto

            if (botoes_radio[0].estado)
            {
                for (int v = 0; v < 6; v++)
                {
                    caixa_texto_pesquisar[v].habilitado = false;
                }
                caixa_texto_pesquisar[0].habilitado = true;

                leTeclado(caixa_texto_pesquisar[0].texto, &caixa_texto_pesquisar[0].tamanho, caixa_texto_pesquisar[0].subgrupo, 20); // Chama a funçaõ que le caracteres do teclado
            } // Habilita a leitura do teclado para a caixa de texto do pesquisar

            for (int k = 1; k < 5; k++)
            {

                for (int n = 1; n < 3; n++)
                {
                    if (checarClique(&caixa_texto_pesquisar[n].caixa))
                    {
                        caixa_texto_pesquisar[1].subcaixa = 0;
                        caixa_texto_pesquisar[2].subcaixa = 0;
                        caixa_texto_pesquisar[n].subcaixa = 1;
                        break;
                    } // Ativa a caixa de texto que foi clicado por ultimo
                } // Percorre todas as caixas de texto desse tipo

                if (botoes_radio[k].estado)
                {
                    for (int v = 0; v < 6; v++)
                    {
                        caixa_texto_pesquisar[v].habilitado = false;
                    }
                    caixa_texto_pesquisar[1].habilitado = true;
                    caixa_texto_pesquisar[2].habilitado = true;
                    if (caixa_texto_pesquisar[1].subcaixa)
                    {
                        leTeclado(caixa_texto_pesquisar[1].texto, &caixa_texto_pesquisar[1].tamanho, caixa_texto_pesquisar[2].subgrupo, 8); // Chama a funçaõ que le caracteres do teclado
                    }
                    if (caixa_texto_pesquisar[2].subcaixa)
                    {
                        leTeclado(caixa_texto_pesquisar[2].texto, &caixa_texto_pesquisar[2].tamanho, caixa_texto_pesquisar[2].subgrupo, 8); // Chama a funçaõ que le caracteres do teclado
                    }
                } // Se o botao de radio estiver ativo, faz a ativação da leitura da caixa relativa
            } // Habilita a leitura das caixas com range de cada uma das variaveis numéricas, baseado em qual esta ativa pelo subcaixa

            if (botoes_radio[5].estado)
            {
                for (int v = 0; v < 6; v++)
                {
                    caixa_texto_pesquisar[v].habilitado = false;
                }
                caixa_texto_pesquisar[3].habilitado = true;
                caixa_texto_pesquisar[4].habilitado = true;

                for (int n = 3; n < 5; n++)
                {
                    if (checarClique(&caixa_texto_pesquisar[n].caixa))
                    {
                        caixa_texto_pesquisar[3].subcaixa = 0;
                        caixa_texto_pesquisar[4].subcaixa = 0;
                        caixa_texto_pesquisar[n].subcaixa = 1;
                        break;
                    } // Ativa a caixa de texto que foi clicado por ultimo
                } // Percorre as caixas de texto desse tipo

                if (caixa_texto_pesquisar[3].subcaixa)
                {
                    leTeclado(caixa_texto_pesquisar[3].texto, &caixa_texto_pesquisar[3].tamanho, caixa_texto_pesquisar[3].subgrupo, 8); // Chama a funçaõ que le caracteres do teclado
                }
                if (caixa_texto_pesquisar[4].subcaixa)
                {
                    leTeclado(caixa_texto_pesquisar[4].texto, &caixa_texto_pesquisar[4].tamanho, caixa_texto_pesquisar[4].subgrupo, 8); // Chama a funçaõ que le caracteres do teclado
                } // Habilita a leitura do teclado para as caixas de texto do hexadecimal seguindo a mesma logica do de cima
            } // Habilita as caixas de texto do tipo do hexadecimal

            if (checarClique(&botoes_gerenciador[9].colisao) && estado_tela != 2)
            {
                controleSons(1, *musica, sons[1]); // Função de controle geral sons - tocar som clicou
                botoes_gerenciador[9].cor_botao = GREEN;

                total_cartas = pesquisarCarta(caixa_texto_pesquisar, caixa.estado, botoes_radio, &cartas_desenho); // Chama a função de processamento do pesquisar
                carta_atual = 1;                                                                                   // Seta a carta atual para 1 para voltar a primeira posição da exibição das cartas

                if (total_cartas == -1)
                {
                    submenu_tela = 5;
                } // Se o retorno do pesquisar for -1 chama a listagem de cartas, por causa de parametros vazios

                if (total_cartas == 0)
                {
                    total_cartas = 1;
                    cartas_desenho = realloc(cartas_desenho, total_cartas * sizeof(Carta));
                    if (cartas_desenho == NULL)
                    {
                        perror("GAME: Erro ao realocar memória");
                        exit(1);
                    }
                    cartas_desenho[total_cartas - 1].id = 999;
                    cartas_desenho[total_cartas - 1].super_trunfo = false;
                    strcpy(cartas_desenho[total_cartas - 1].hexadecimal, "9Z");
                    strcpy(cartas_desenho[total_cartas - 1].imagem, "./img/rostos/erro.png");
                    strcpy(cartas_desenho[total_cartas - 1].nome, "No-Name");
                    cartas_desenho[total_cartas - 1].curiosidade = 0;
                    cartas_desenho[total_cartas - 1].criatividade = 0;
                    cartas_desenho[total_cartas - 1].inovacao = 0;
                    cartas_desenho[total_cartas - 1].idade = 0;
                } // Caso de não haver corespondencias no pesquisar, mostra uma carta base, com a msg relacionada

                if (caixa.estado)
                {
                    caixa.estado = false;
                } // Limpa o campo super-trunfo pós o uso

                for (int s = 0; s < 5; s++)
                {
                    strcpy(caixa_texto_pesquisar[s].texto, "");
                    caixa_texto_pesquisar[s].tamanho = 0;
                } // Limpa as caixas de texto do pesquisar

            } // Se clicar em pesquisar, processa as informações

        } // FIM SUBMENU PESQUISAR

        // LISTAR:
        if (submenu_tela == 5)
        {
            if (checarClique(&botoes_gerenciador[10].colisao) && estado_tela != 2)
            {
                controleSons(1, *musica, sons[1]); // Função de controle geral sons - tocar som clicou
                botoes_gerenciador[10].cor_botao = GREEN;
                resetarCartas();
            } // Verifica cliques no botão de resetar cartas, se sim, processa os dados
        } // LISTAR

        // EDITAR:
        if (submenu_tela == 3)
        {

            for (int u = 0; u < 6; u++)
            {
                if (strcmp(caixa_texto[u].texto, "") == 0)
                {
                    caixa_texto[u].placeholder = true;
                }
                else
                {
                    caixa_texto[u].placeholder = false;
                }
            } // Operando os placeholders das caixas de texto

            for (int j = 0; j < 6; j++)
            {
                if (botoes_radio[j].estado)
                {

                    for (int v = 0; v < 6; v++)
                    {
                        caixa_texto[v].habilitado = false;
                    }
                    caixa_texto[j].habilitado = true;

                    leTeclado(caixa_texto[j].texto, &caixa_texto[j].tamanho, caixa_texto[j].subgrupo, 20); // Chama a funçaõ que le caracteres do teclado, permitindo leitura para a caixa ativa

                    break;
                }
            } // Faz a ativação da caixa de txt correspondente ao botão de radio ativado

            if (checarClique(&botoes_gerenciador[8].colisao) && estado_tela != 2)
            {
                controleSons(1, *musica, sons[1]); // Função de controle geral sons - tocar som clicou
                botoes_gerenciador[8].cor_botao = GREEN;

                retornos_funcoes[2] = editarCarta(caixa_texto, carta_atual - 1, caixa.estado); // Chama a função que copia os parametros para o vetor
                if (caixa.estado)
                {
                    caixa.estado = false;
                } // Limpa a caixa de super-trunfo após o uso

                if (retornos_funcoes[2] == 0)
                {
                    submenu_tela = 5;
                } // Se a funçaõ processar ok, chama o listar
            } // Se clicar em adicionar, enquanto estiver no menu editar, processa as informações no editar
        }

        if (retornos_funcoes[2] == 1 || retornos_funcoes[2] == 2 || retornos_funcoes[2] == 3)
        {
            submenu_tela = 5;
            if (contador_frames[3] > 185)
            {
                retornos_funcoes[2] = 0;
                contador_frames[3] = 0;
            }
            else
            {
                contador_frames[3]++;
            } // Dara o aviso de erro de adicionar ao usuário por 185 Frames
        } // Trata o retorno do editar se campos forem vazios - EDITAR
        // FIM SUBMENU EDITAR

        // ADICIONAR:
        if (submenu_tela == 1)
        {

            for (int u = 0; u < 6; u++)
            {
                if (strcmp(caixa_texto[u].texto, "") == 0)
                {
                    caixa_texto[u].placeholder = true;
                }
                else
                {
                    caixa_texto[u].placeholder = false;
                }
            } // Operando os placeholders

            for (int j = 0; j < 6; j++)
            {
                if (botoes_radio[j].estado)
                {

                    for (int v = 0; v < 6; v++)
                    {
                        caixa_texto[v].habilitado = false;
                    }
                    caixa_texto[j].habilitado = true;

                    leTeclado(caixa_texto[j].texto, &caixa_texto[j].tamanho, caixa_texto[j].subgrupo, 20); // Chama a funçaõ que le caracteres do teclado

                    break;
                }
            } // Faz a ativação da caixa de txt correspondente ao botão de radio ativado

            if (checarClique(&botoes_gerenciador[7].colisao) && estado_tela != 2)
            {
                controleSons(1, *musica, sons[1]); // Função de controle geral sons - tocar som clicou
                botoes_gerenciador[7].cor_botao = GREEN;

                cartas = (Carta *)realloc(cartas, (quantidade_cartas + 1) * sizeof(Carta));
                if (cartas == NULL)
                {
                    perror("GAME: Erro ao realocar memória");
                    exit(1);
                }
                retornos_funcoes[1] = adicionarCarta(caixa_texto, caixa.estado); // Chama a função que copia os parametros para o vetor
                if (caixa.estado)
                {
                    caixa.estado = false;
                } // Desabilita a caixa que é supertrunfo após uso

                if (retornos_funcoes[1] == 0)
                {
                    submenu_tela = 5;
                } // Se ocorrer tudo ok, chama o adicionar

            } // Se clicar em adicionar, enquanto estiver no menu adicionar, processa
        }

        if (retornos_funcoes[1] == 1 || retornos_funcoes[1] == 2 || retornos_funcoes[1] == 3)
        {
            submenu_tela = 5;
            if (contador_frames[2] > 185)
            {
                retornos_funcoes[1] = 0;
                contador_frames[2] = 0;
            }
            else
            {
                contador_frames[2]++;
            } // Dara o aviso de erro de adicionar ao usuário por 185 Frames
        } // Trata o retorno do adicionar se campos forem vazios - ADICIONAR
        // FIM SUBMENU ADICIONAR

        // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
        // CONTROLE DOS BOTOES GERAIS:
        // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

        if (checarClique(&botoes_nulos_gerenciador[0].colisao) && estado_tela != 2)
        {
            carta_atual++;
        } // Clique seta direita

        if (checarClique(&botoes_nulos_gerenciador[1].colisao) && estado_tela != 2)
        {
            carta_atual--;
        } // Clique seta esquerda

        if (carta_atual > total_cartas)
        {
            carta_atual = 1;
        } // Se maior que ultima volta para a 1

        if (carta_atual < 1)
        {
            carta_atual = total_cartas;
        } // Se menor que 1 volta para a ultima

        // CHECAGEM DE CLIQUE DOS BOTÕES:

        if (checarClique(&botoes_gerenciador[0].colisao) && estado_tela != 2)
        {
            estado_tela = 2;
            controleSons(1, *musica, sons[1]); // Função de controle geral sons - tocar som clicou
            botoes_gerenciador[0].cor_botao = GREEN;
            trocar_tela = true;
        } // Voltar Menu

        if (checarClique(&botoes_gerenciador[1].colisao) && estado_tela != 2)
        {
            controleSons(1, *musica, sons[1]); // Função de controle geral sons - tocar som clicou
            botoes_gerenciador[1].cor_botao = GREEN;
            submenu_tela = 1;

            for (int j = 0; j < 6; j++)
            {
                botoes_radio[j].estado = false;
            }
            botoes_radio[0].estado = true;

            for (int s = 0; s < 6; s++)
            {
                strcpy(caixa_texto[s].texto, "");
                caixa_texto[s].tamanho = 0;
            } // Limpa as caixas de texto
        } // Submenu - ADICIONAR

        if (checarClique(&botoes_gerenciador[3].colisao) && estado_tela != 2)
        {
            controleSons(1, *musica, sons[1]); // Função de controle geral sons - tocar som clicou
            botoes_gerenciador[3].cor_botao = GREEN;
            submenu_tela = 3;

            for (int j = 0; j < 6; j++)
            {
                botoes_radio[j].estado = false;
            }
            botoes_radio[0].estado = true;

            for (int s = 0; s < 6; s++)
            {
                strcpy(caixa_texto[s].texto, "");
                caixa_texto[s].tamanho = 0;
            } // Limpa as caixas de texto ao serem usadas

        } // Submenu - EDITAR

        if (checarClique(&botoes_gerenciador[4].colisao) && estado_tela != 2)
        {
            controleSons(1, *musica, sons[1]); // Função de controle geral sons - tocar som clicou
            botoes_gerenciador[4].cor_botao = GREEN;
            submenu_tela = 4;

            for (int j = 0; j < 6; j++)
            {
                botoes_radio[j].estado = false;
            }
            botoes_radio[0].estado = true;

            for (int s = 0; s < 6; s++)
            {
                strcpy(caixa_texto[s].texto, "");
                caixa_texto[s].tamanho = 0;
            } // Limpa as caixas de texto ao serem usadas

        } // Submenu - PESQUISAR

        if (checarClique(&botoes_gerenciador[2].colisao) && estado_tela != 2 && submenu_tela != 4)
        {
            controleSons(1, *musica, sons[1]); // Função de controle geral sons - tocar som clicou
            botoes_gerenciador[2].cor_botao = GREEN;
            if (quantidade_cartas > 1)
            {
                excluirCarta(carta_atual - 1); // Chama a funçaõ de excluir cartas para o id da carta atual
                quantidade_cartas--;           // Reduz o tamanho das cartas globais
                exclusor = true;               // Seta o exclusor, que é usado no pós processamento das funções
            }
            else
            {
                printf("\nGAME: IMPOSSIVEL EXCLUIR A CARTA, SOBROU APENAS 1 NO ARQUIVO BIN!\n");
                retornos_funcoes[0] = 1;
            }
        } // Submenu - EXCLUIR

        if (checarClique(&botoes_gerenciador[5].colisao) && estado_tela != 2)
        {
            controleSons(1, *musica, sons[1]); // Função de controle geral sons - tocar som clicou
            botoes_gerenciador[5].cor_botao = GREEN;
            submenu_tela = 5;
            carta_atual = 1;
        } // Submenu - LISTAR

        if (checarClique(&botoes_gerenciador[6].colisao) && estado_tela != 2)
        {
            controleSons(1, *musica, sons[1]); // Função de controle geral sons - tocar som clicou
            botoes_gerenciador[6].cor_botao = GREEN;
            submenu_tela = 6;
            exportou = exportarCsv(); // Chama a função de exportar cartas
        } // Submenu - EXPORTAR

        //---------------------------------------------------
        // CONTROLE DAS TELAS ADICIONAIS:
        //---------------------------------------------------

        if (retornos_funcoes[0])
        {
            if (contador_frames[1] > 150)
            {
                retornos_funcoes[0] = 0;
                contador_frames[1] = 0;
            }
            else
            {
                contador_frames[1]++;
            } // Dara o aviso de erro de exclusão ao usuário por 150 Frames
        }

        if (submenu_tela == 6)
        {
            if (contador_frames[0] > 220)
            {
                submenu_tela = 5;
                contador_frames[0] = 0;
                exportou = 0;
            }
            else
            {
                contador_frames[0]++;
            } // Dara o aviso de exportou ao usuário por 220 Frames
        }

        switch (estado_tela)
        {
        case 2:
            if (!IsSoundPlaying(sons[1]) && trocar_tela == true)
            {
                trocar_tela = false;
                UnloadTexture(fundo);
                UnloadTexture(img_carta);
                UnloadTexture(setass);
                UnloadTexture(seta);
                UnloadTexture(frente_carta);
                tela = 2;
            } // Espera tocar para sair se o usuário deseja sair
            break;

        default:
            break;
        }

        if (!IsSoundPlaying(sons[1]))
        {
            for (int u = 0; u < 11; u++)
            {
                if (coresIguais(botoes_gerenciador[u].cor_botao, GREEN))
                    botoes_gerenciador[u].cor_botao = NOSSO_AZUL;
            }
        } // Muda apos clique a cor de fundo do botão

    } // FIM LOOP GERAL

    return;
}